/**
 * @file examples/test-usart-dma.cpp
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 *
 * Simple test of DMA used with a USART receiver.
 *
 * Configures a USART receiver for use with DMA.  Received bytes are
 * placed into a buffer, with an interrupt firing when the buffer is
 * full.  At that point, the USART transmitter will print the contents
 * of the byte buffer.  The buffer is continually filled and refilled
 * in this manner.
 *
 * This example isn't very robust; don't use it in production.  In
 * particular, since the buffer keeps filling (DMA_CIRC_MODE is set),
 * if you keep sending characters after filling the buffer, you'll
 * overwrite earlier bytes; this may happen before those earlier bytes
 * are done printing. (Typing quickly and seeing how it affects the
 * output is a fun way to make sense of how the interrupts and the
 * main thread of execution interleave.)
 *
 * This code is released into the public domain.
 */

#include <libmaple/dma.h>
#include <libmaple/usart.h>
#include <libmaple/gpio.h>

#include <wirish/wirish.h>

/*
 * Configuration and state
 */

// Serial port and DMA configuration. You can change these to suit
// your purposes.
HardwareSerial *serial = &Serial2;
#define USART_DMA_DEV DMA1
#if STM32_MCU_SERIES == STM32_SERIES_F1
// On STM32F1 microcontrollers (like what's on Maple and Maple Mini),
// dma tubes are channels.
#define USART_RX_DMA_TUBE DMA_CH6
#elif (STM32_MCU_SERIES == STM32_SERIES_F2 || \
       STM32_MCU_SERIES == STM32_SERIES_F4)
// On STM32F2 and STM32F4 microcontrollers (Maple 2 will have an F4),
// dma tubes are streams.
#define USART_RX_DMA_TUBE DMA_S5
#else
#error "unsupported stm32 series"
#endif
// The serial port will make a DMA request each time it receives data.
// This is the dma_request_src we use to tell the DMA tube to handle
// that DMA request.
#define USART_DMA_REQ_SRC DMA_REQ_SRC_USART2_RX
#define BAUD 9600

// This will store the DMA configuration for USART RX.
dma_tube_config tube_config;

// This will store received USART characters.
#define BUF_SIZE 20
char rx_buf[BUF_SIZE];

// The interrupt handler, rx_dma_irq(), sets this to 1.
volatile uint32 irq_fired = 0;
// Used to store DMA interrupt status register (ISR) bits inside
// rx_dma_irq(). This helps explain what's going on inside loop(); see
// comments below.
volatile uint32 isr = 0;

/*
 * Helper functions
 */

// This is our DMA interrupt handler.
void rx_dma_irq(void) {
    irq_fired = 1;
    isr = dma_get_isr_bits(USART_DMA_DEV, USART_RX_DMA_TUBE);
}

// Configure the USART receiver for use with DMA:
// 1. Turn it on.
// 2. Set the "DMA request on RX" bit in USART_CR3 (USART_CR3_DMAR).
void setup_usart(void) {
    serial->begin(BAUD);
    usart_dev *serial_dev = serial->c_dev();
    serial_dev->regs->CR3 = USART_CR3_DMAR;
}

// Set up our dma_tube_config structure. (We could have done this
// above, when we declared tube_config, but having this function makes
// it easier to explain what's going on).
void setup_tube_config(void) {
    // We're receiving from the USART data register. serial->c_dev()
    // returns a pointer to the libmaple usart_dev for that serial
    // port, so this is a pointer to its data register.
    tube_config.tube_src = &serial->c_dev()->regs->DR;
    // We're only interested in the bottom 8 bits of that data register.
    tube_config.tube_src_size = DMA_SIZE_8BITS;
    // We're storing to rx_buf.
    tube_config.tube_dst = rx_buf;
    // rx_buf is a char array, and a "char" takes up 8 bits on STM32.
    tube_config.tube_dst_size = DMA_SIZE_8BITS;
    // Only fill BUF_SIZE - 1 characters, to leave a null byte at the end.
    tube_config.tube_nr_xfers = BUF_SIZE - 1;
    // Flags:
    // - DMA_CFG_DST_INC so we start at the beginning of rx_buf and
    //   fill towards the end.
    // - DMA_CFG_CIRC so we go back to the beginning and start over when
    //   rx_buf fills up.
    // - DMA_CFG_CMPLT_IE to turn on interrupts on transfer completion.
    tube_config.tube_flags = DMA_CFG_DST_INC | DMA_CFG_CIRC | DMA_CFG_CMPLT_IE;
    // Target data: none. It's important to set this to NULL if you
    // don't have any special (microcontroller-specific) configuration
    // in mind, which we don't.
    tube_config.target_data = NULL;
    // DMA request source.
    tube_config.tube_req_src = USART_DMA_REQ_SRC;
}

// Configure the DMA controller to serve DMA requests from the USART.
void setup_dma_xfer(void) {
    // First, turn it on.
    dma_init(USART_DMA_DEV);
    // Next, configure it by calling dma_tube_cfg(), and check to make
    // sure it succeeded. DMA tubes have many restrictions on their
    // configuration, and there are configurations which work on some
    // types of STM32 but not others. libmaple tries hard to make
    // things just work, but checking the return status is important!
    int status = dma_tube_cfg(USART_DMA_DEV, USART_RX_DMA_TUBE, &tube_config);
    ASSERT(status == DMA_TUBE_CFG_SUCCESS);
    // Now we'll perform any other configuration we want. For this
    // example, we attach an interrupt handler.
    dma_attach_interrupt(USART_DMA_DEV, USART_RX_DMA_TUBE, rx_dma_irq);
    // Turn on the DMA tube. It will now begin serving requests.
    dma_enable(USART_DMA_DEV, USART_RX_DMA_TUBE);
}

/*
 * setup() and loop()
 */

void setup(void) {
    pinMode(BOARD_LED_PIN, OUTPUT);
    setup_tube_config();
    setup_dma_xfer();
    setup_usart();
}

void loop(void) {
    toggleLED();
    delay(100);

    // See if the interrupt handler got called since the last time we
    // checked.
    if (irq_fired) {
        serial->println("** IRQ **");
        // Notice how the interrupt status register (ISR) bits show
        // transfer complete _and_ half-complete here, but the ISR
        // bits we print next will be zero. That's because the
        // variable "isr" gets set _inside_ rx_dma_irq(). After it
        // exits, libmaple cleans up by clearing the tube's ISR
        // bits. (If it didn't, and we forgot to, the interrupt would
        // repeatedly fire forever.)
        serial->print("ISR bits: 0x");
        serial->println(isr, HEX);
        irq_fired = 0;
    }

    // Print the ISR bits.
    //
    // Notice that the "transfer half-complete" ISR flag gets set when
    // we reach the rx_buf half-way point. This is true even though we
    // don't tell the DMA controller to interrupt us on a
    // half-complete transfer. That is, the ISR bits get set at the
    // right times no matter what; we just don't get interrupted
    // unless we asked. (If an error or other problem occurs, the
    // relevant ISR bits will get set in the same way).
    serial->print("[");
    serial->print(millis());
    serial->print("]\tISR bits: 0x");
    uint8 isr_bits = dma_get_isr_bits(USART_DMA_DEV, USART_RX_DMA_TUBE);
    serial->print(isr_bits, HEX);

    // Print the contents of rx_buf. If you keep typing after it fills
    // up, the new characters will overwrite the old ones, thanks to
    // DMA_CIRC_MODE.
    serial->print("\tCharacter buffer contents: '");
    serial->print(rx_buf);
    serial->println("'");
    if (isr_bits == 0x7) {
        serial->println("** Clearing ISR bits.");
        dma_clear_isr_bits(USART_DMA_DEV, USART_RX_DMA_TUBE);
    }
}

// ------- init() and main() --------------------------------------------------

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need libmaple may fail.
__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (true) {
        loop();
    }
    return 0;
}
