/**
 * @file dma-advanced.cpp
 * @author Eugene V. aka robodude666
 *
 * Advanced DMA example using ADC sampling and USART transmission.
 * 
 * DMA1 Channel 1 and 6 are setup for ADC and USART_TX respectively.
 * AIN on D3 is used for this exmaple and USART 2.
 * The ADC DMA controller is set up to take ADC_BUF_SIZE samples.
 * During this sampling, a half and complete interrupt is triggered.
 * 
 * For the half complete event, the first half of the buffer is
 * prepared for USART transmission. After the complete interrupt is
 * received, the latter half is prepared. The ADC DMA controller is
 * then disabled, and USART controller is enabled to dump the data.
 * 
 * Once the data has been transferred via USART, the USART DMA
 * controller is disabled and ADC is enabled. The process starts all
 * over again. The LED blink during the transfer process.
 * 
 * This is purely an example of using multiple DMA controllers
 * together. It is not production quality code. For instance,
 * the data is inflated by TX_STR_SIZE times. A lot of CPU time
 * is used in the interrupts to prepare the data. This is for human
 * readability, but a huge waste of RAM/CPU. Sending data in another
 * way is recommended (raw data va SPI/USART, for example).
 * 
 * This code is released into the public domain.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dma.h"
#include "usart.h"
#include "gpio.h"

#include "wirish.h"

#define BAUD 38400

#define USART USART2
#define USART_HWSER Serial2

#define USART_DMA_DEV DMA1
#define USART_TX_DMA_CHANNEL DMA_CH7

#define ADC_DMA_DEV DMA1
#define ADC_DMA_CHANNEL DMA_CH1

// ADC_BUF_SIZE must be an even number
#define TX_STR_SIZE 13
#define ADC_BUF_SIZE 8
#define USART_TX_BUF_SIZE ADC_BUF_SIZE * TX_STR_SIZE
#define HALF_BUF_SIZE (ADC_BUF_SIZE)/2

uint16 adc_buf[ADC_BUF_SIZE];
uint8 tx_buf[USART_TX_BUF_SIZE];

__io bool doing_uart_transfer = false;
__io bool dma_error_occured = false;

void init_adc(void);
void init_usart(void);

void init_dma_adc(void);
void init_dma_usart(void);

void adc_dma_irq(dma_irq_cause irq_cause);
void usart_tx_dma_irq(dma_irq_cause irq_cause);

void setup(void) {

    pinMode(BOARD_LED_PIN, OUTPUT);

    init_dma_adc();
    init_dma_usart();

    init_adc();
    init_usart();
}

void loop(void) {

    if (dma_error_occured) {

        /*
         * An error occured. Do whatever we want here like restart the DMA transfer.
         * For this demo, we'll stop our DMA controllers and 
         * the LED will blink extra fast.
         */

        dma_disable(ADC_DMA_DEV, ADC_DMA_CHANNEL);
        dma_disable(USART_DMA_DEV, USART_TX_DMA_CHANNEL);

        while (1) {
            toggleLED();
            delay(30);
        }
    }

    if (doing_uart_transfer) {

        toggleLED();
        delay(100);
    }

    /*
     * Do whatever you want here!!
     *       PARTY TIME
     */

}

/* Configure ADC for sampling with DMA */
void init_adc(void) {

    adc_set_reg_seqlen(ADC1, 1); // One conversion per sample
    ADC1->regs->SQR3 = 1; // Read from channel 1 (D3)

    // Enable DMA support, start conversion, and continiously sample.
    ADC1->regs->CR2 |= (ADC_CR2_DMA | ADC_CR2_SWSTART | ADC_CR2_CONT);

}

/* Configure USART receiver for use with DMA */
void init_usart(void) {
    USART_HWSER.begin(BAUD);
    USART->regs->CR3 |= USART_CR3_DMAT; // USART DMA Enable Transmitter
}

/* Configure DMA for ADC sampling */
void init_dma_adc(void) {

    dma_init(ADC_DMA_DEV);

    dma_setup_transfer(ADC_DMA_DEV, ADC_DMA_CHANNEL,
                        &ADC1->regs->DR, DMA_SIZE_16BITS,
                        adc_buf,         DMA_SIZE_16BITS,
                        (DMA_MINC_MODE | DMA_TRNS_CMPLT | DMA_HALF_TRNS)
                        );

    dma_set_num_transfers(ADC_DMA_DEV, ADC_DMA_CHANNEL, ADC_BUF_SIZE);

    dma_attach_interrupt(ADC_DMA_DEV, ADC_DMA_CHANNEL, adc_dma_irq);

    dma_enable(ADC_DMA_DEV, ADC_DMA_CHANNEL);
}

/* Configure DMA transmission */
void init_dma_usart(void) {

    dma_init(USART_DMA_DEV);

    dma_setup_transfer(USART_DMA_DEV, USART_TX_DMA_CHANNEL,
                        &USART->regs->DR, DMA_SIZE_8BITS,
                        tx_buf,           DMA_SIZE_8BITS,
                        (DMA_MINC_MODE | DMA_FROM_MEM | DMA_TRNS_CMPLT));

    dma_set_num_transfers(USART_DMA_DEV, USART_TX_DMA_CHANNEL, USART_TX_BUF_SIZE);

    dma_attach_interrupt(USART_DMA_DEV, USART_TX_DMA_CHANNEL, usart_tx_dma_irq);

    // We'll be enabling this one manually when we're ready.
}

/* Our interrupt handler for ADC DMA interrupts */
void adc_dma_irq(dma_irq_cause irq_cause) {

    /* Based on the official STM app note AN2548
     * we'll process the first half of data when it's available for us.
     * Then, once the second half is ready, we'll process the second
     * half.
     *
     * Note: For this particular application, this may not be a good idea
     * since we're doing a lot of expensive sprintf/memcpys
     * but it's an example of how you can use the half complete interrupt.
     */

    uint8 half_buffer = 0;

    if (irq_cause == DMA_TRANSFER_ERROR) {

        /* We aren't expecting this event to occur, as we're
         * not asking for it, but in case we do enable it,
         * this is how we'll handle errors.
         */

        dma_error_occured = true;
        dma_disable(ADC_DMA_DEV, ADC_DMA_CHANNEL); // Disable ourselves to prevent further errors
        // We may want to turn off the ADC here

        return; // Something went wrong, exit early.
    } else if (irq_cause == DMA_TRANSFER_COMPLETE) {

        // Disable the controller since we finished sampling for now
        dma_disable(ADC_DMA_DEV, ADC_DMA_CHANNEL);

        // We may want to stop the ADC for now.

    } else if (irq_cause == DMA_TRANSFER_HALF_COMPLETE) {

        half_buffer = 1;
    }

    static char temp[TX_STR_SIZE];

    /*
    * Not the best way of doing this but it is human readable...
    * If you really wanted to do this, transfer raw bits and parse on
    * receiving end.
    */

    // Fill our usart's dma buffer with new goodies.
    for (uint16 i = (HALF_BUF_SIZE)*half_buffer; i < (HALF_BUF_SIZE*(1+half_buffer)); i++) {

        // TX_STR_SIZE represents size of below string.
        sprintf(temp, "Value: %5d\n", adc_buf[i]);
        uint8 *dest = &tx_buf[i * TX_STR_SIZE];
        memcpy(dest, temp, TX_STR_SIZE);
    }

    // Dump the data to USART
    if (irq_cause == DMA_TRANSFER_COMPLETE) {

        doing_uart_transfer = true;

        dma_set_num_transfers(USART_DMA_DEV, USART_TX_DMA_CHANNEL, USART_TX_BUF_SIZE);
        dma_enable(USART_DMA_DEV, USART_TX_DMA_CHANNEL);
    }
}

/* Our interrupt handler for USART DMA interrupts */
void usart_tx_dma_irq(dma_irq_cause irq_cause) {

    if (irq_cause == DMA_TRANSFER_COMPLETE) {

        // Disable the controller since we finished sampling for now
        doing_uart_transfer = false;
        dma_disable(USART_DMA_DEV, USART_TX_DMA_CHANNEL);
        dma_set_num_transfers(ADC_DMA_DEV, ADC_DMA_CHANNEL, ADC_BUF_SIZE);
        dma_enable(ADC_DMA_DEV, ADC_DMA_CHANNEL);
    }
}

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
