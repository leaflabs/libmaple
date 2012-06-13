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
 * are done printing.
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

// USART and DMA configuration
#define USART USART2
#define USART_HWSER Serial2
#define USART_DMA_DEV DMA1
#define USART_RX_DMA_CHANNEL DMA_CH6
#define BAUD 9600

// This will store received USART characters.
#define BUF_SIZE 20
char rx_buf[BUF_SIZE];

// The interrupt handler, rx_dma_irq(), sets this to 1.
volatile uint32 irq_fired = 0;
// Used to store the ISR bits inside rx_dma_irq(). This helps explain
// what's going on inside loop(); see comments below.
volatile uint32 isr = 0;

/*
 * Helper functions
 */

// This is our DMA interrupt handler.
void rx_dma_irq(void) {
    irq_fired = 1;
    isr = dma_get_isr_bits(USART_DMA_DEV, USART_RX_DMA_CHANNEL);
}

// Configure the USART receiver for use with DMA:
// 1. Turn it on.
// 2. Set the "DMA request on RX" bit in USART_CR3 (USART_CR3_DMAR).
void init_usart(void) {
    USART_HWSER.begin(BAUD);
    USART->regs->CR3 = USART_CR3_DMAR;
}

// Configure the DMA controller to serve DMA requests from the USART.
void init_dma_xfer(void) {
    dma_init(USART_DMA_DEV);
    dma_setup_transfer(USART_DMA_DEV, USART_RX_DMA_CHANNEL,
                       &USART->regs->DR, DMA_SIZE_8BITS,
                       rx_buf,           DMA_SIZE_8BITS,
                       (DMA_MINC_MODE | DMA_CIRC_MODE | DMA_TRNS_CMPLT));
    dma_set_num_transfers(USART_DMA_DEV, USART_RX_DMA_CHANNEL,
                          BUF_SIZE - 1);
    dma_attach_interrupt(USART_DMA_DEV, USART_RX_DMA_CHANNEL, rx_dma_irq);
    dma_enable(USART_DMA_DEV, USART_RX_DMA_CHANNEL);
}

/*
 * setup() and loop()
 */

void setup(void) {
    pinMode(BOARD_LED_PIN, OUTPUT);
    rx_buf[BUF_SIZE - 1] = '\0'; // null-terminate rx_buf so we can print it
    init_dma_xfer();
    init_usart();
}

void loop(void) {
    toggleLED();
    delay(100);

    // See if the interrupt handler got called since the last time we
    // checked.
    if (irq_fired) {
        USART_HWSER.println("** IRQ **");
        // Notice how the ISR bits show transfer complete _and_
        // half-complete here, but the ISR bits we print next will be
        // zero. That's because the variable "isr" gets set _inside_
        // rx_dma_irq(). After it exits, libmaple cleans up by
        // clearing the ISR bits. (If it didn't, and we forgot to, the
        // interrupt would repeatedly fire forever.)
        USART_HWSER.print("ISR bits: 0x");
        USART_HWSER.println(isr, HEX);
        irq_fired = 0;
    }

    // Print the ISR (interrupt status register) bits.
    //
    // Notice that the "transfer half-complete" ISR flag gets set when
    // we reach the rx_buf half-way point. This is true even though we
    // don't tell the DMA controller to interrupt us on a
    // half-complete transfer. That is, the ISR bits get set at the
    // right times no matter what; we just don't get interrupted
    // unless we asked. (If an error or other problem occurs, the
    // relevant ISR bits will get set in the same way).
    USART_HWSER.print("[");
    USART_HWSER.print(millis());
    USART_HWSER.print("]\tISR bits: 0x");
    uint8 isr_bits = dma_get_isr_bits(USART_DMA_DEV, USART_RX_DMA_CHANNEL);
    USART_HWSER.print(isr_bits, HEX);

    // Print the contents of rx_buf. If you keep typing after it fills
    // up, the new characters will overwrite the old ones, thanks to
    // DMA_CIRC_MODE.
    USART_HWSER.print("\tCharacter buffer contents: '");
    USART_HWSER.print(rx_buf);
    USART_HWSER.println("'");
    if (isr_bits == 0x7) {
        USART_HWSER.println("** Clearing ISR bits.");
        dma_clear_isr_bits(USART_DMA_DEV, USART_RX_DMA_CHANNEL);
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
