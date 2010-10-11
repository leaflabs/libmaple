/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *****************************************************************************/

/**
 * @file usart.h
 * @brief USART definitions and prototypes
 */

#ifndef _USART_H_
#define _USART_H_

#include "ring_buffer.h"

#ifdef __cplusplus
extern "C"{
#endif

#define USART_TXE           BIT(7)

/* usart device numbers  */
enum {
    USART1,
    USART2,
    USART3,
    UART4,
    UART5,
};

/* peripheral register struct  */
typedef struct usart_port {
    volatile uint32 SR;       // Status register
    volatile uint32 DR;       // Data register
    volatile uint32 BRR;      // Baud rate register
    volatile uint32 CR1;      // Control register 1
    volatile uint32 CR2;      // Control register 2
    volatile uint32 CR3;      // Control register 3
    volatile uint32 GTPR;     // Guard time and prescaler register
} usart_port;

/* usart descriptor  */
struct usart_dev {
    usart_port *base;
    ring_buffer rb;
    uint8 rx_buf[64];
    const uint8 rcc_dev_num;
    const uint8 nvic_dev_num;
};

extern struct usart_dev usart_dev_table[];

/**
 * @brief send one character on a usart
 * @param usart_num usart to send on
 * @param byte byte to send
 */
static inline void usart_putc(uint8 usart_num, uint8 byte) {
    usart_port *port = usart_dev_table[usart_num].base;

    port->DR = byte;

    /* Wait for transmission to complete  */
    while ((port->SR & USART_TXE) == 0)
        ;
}

/**
 * @brief read one character from a usart
 * @param usart_num usart to read from
 * @return byte read
 */
static inline uint8 usart_getc(uint8 usart_num) {
    return rb_remove(&usart_dev_table[usart_num].rb);
}

/**
 * @brief return the amount of data available in the rx buffer
 * @param usart_num which usart to check
 * @return number of bytes in the rx buffer
 */
static inline uint32 usart_data_available(uint8 usart_num) {
    return rb_full_count(&usart_dev_table[usart_num].rb);
}

/**
 * @brief removes the contents of the rx fifo
 * @param usart_num which usart to reset
 */
static inline void usart_reset_rx(uint8 usart_num) {
    rb_reset(&usart_dev_table[usart_num].rb);
}

void usart_init(uint8 usart_num, uint32 baud);
void usart_disable(uint8 usart_num);
void usart_disable_all();
void usart_putstr(uint8 usart_num, const char*);
void usart_putudec(uint8 usart_num, uint32 val);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _USART_H_
