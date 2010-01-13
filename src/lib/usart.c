/* *****************************************************************************
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Created: 12/18/09 02:38:26
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file usart.c
 *
 *  @brief USART control routines
 */

#include "libmaple.h"
#include "stm32f10x_rcc.h"
#include "usart.h"
#include "nvic.h"

#define USART1_BASE         0x40013800
#define USART2_BASE         0x40004400
#define USART3_BASE         0x40004800

#define USART_UE            BIT(13)
#define USART_M             BIT(12)
#define USART_TE            BIT(3)
#define USART_RE            BIT(2)
#define USART_RXNEIE        BIT(5)       // read data register not empty interrupt enable
#define USART_TXE           BIT(7)
#define USART_TC            BIT(6)

#define USART_STOP_BITS_1   BIT_MASK_SHIFT(0b0, 12)
#define USART_STOP_BITS_05  BIT_MASK_SHIFT(0b01, 12)
#define USART_STOP_BITS_2   BIT_MASK_SHIFT(0b02, 12)
#define USART_STOP_BITS_15  BIT_MASK_SHIFT(0b02, 12)

#define USART1_CLK          72000000UL
#define USART2_CLK          36000000UL
#define USART3_CLK          36000000UL

#define USART_RECV_BUF_SIZE 64

/* Ring buffer notes:
 * The buffer is empty when head == tail.
 * The buffer is full when the head is one byte in front of the tail
 * The total buffer size must be a power of two
 * Note, one byte is necessarily left free with this scheme */
typedef struct usart_ring_buf {
    uint32 head;
    uint32 tail;
    uint8 buf[USART_RECV_BUF_SIZE];
} usart_ring_buf;

static usart_ring_buf ring_buf1;
static usart_ring_buf ring_buf2;
static usart_ring_buf ring_buf3;

typedef struct usart_port {
    volatile uint32 SR;       // Status register
    volatile uint32 DR;       // Data register
    volatile uint32 BRR;      // Baud rate register
    volatile uint32 CR1;      // Control register 1
    volatile uint32 CR2;      // Control register 2
    volatile uint32 CR3;      // Control register 3
    volatile uint32 GTPR;     // Guard time and prescaler register
} usart_port;

void USART1_IRQHandler(void) {
    /* Read the data  */
    ring_buf1.buf[ring_buf1.tail++] = (uint8_t)(((usart_port*)(USART1_BASE))->DR);
    ring_buf1.tail %= USART_RECV_BUF_SIZE;
}

/* Don't overrun your buffer, seriously  */
void USART2_IRQHandler(void) {
    /* Read the data  */
    ring_buf2.buf[ring_buf2.tail++] = (uint8_t)(((usart_port*)(USART2_BASE))->DR);
    ring_buf2.tail %= USART_RECV_BUF_SIZE;
}
/* Don't overrun your buffer, seriously  */
void USART3_IRQHandler(void) {
    /* Read the data  */
    ring_buf3.buf[ring_buf3.tail++] = (uint8_t)(((usart_port*)(USART3_BASE))->DR);
    ring_buf3.tail %= USART_RECV_BUF_SIZE;
}

/**
 *  @brief Enable a USART in single buffer transmission mode, multibuffer
 *  receiver mode.
 *
 *  @param usart_num USART to be initialized
 *  @param baud Baud rate to be set at
 *  @param recvBuf buf buffer for receiver
 *  @param len size of recvBuf
 *
 *  @sideeffect Turns on the specified USART
 */
void usart_init(uint8 usart_num, uint32 baud) {
    ASSERT((usart_num <= NR_USARTS) && (usart_num > 0));
    ASSERT(baud && (baud < USART_MAX_BAUD));

    usart_port *port;
    usart_ring_buf *ring_buf;

    uint32 clk_speed;
    uint32 integer_part;
    uint32 fractional_part;
    uint32 tmp;

    switch (usart_num) {
    case 1:
        port = (usart_port*)USART1_BASE;
        ring_buf = &ring_buf1;
        clk_speed = USART1_CLK;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
        REG_SET(NVIC_ISER1, BIT(5));
        break;
    case 2:
        port = (usart_port*)USART2_BASE;
        ring_buf = &ring_buf2;
        clk_speed = USART2_CLK;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
        REG_SET(NVIC_ISER1, BIT(6));
        break;
    case 3:
        port = (usart_port*)USART3_BASE;
        ring_buf = &ring_buf3;
        clk_speed = USART3_CLK;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
        REG_SET(NVIC_ISER1, BIT(7));
        break;
    default:
        /* should never get here  */
        ASSERT(0);
    }

    /* Initialize ring buffer  */
    ring_buf->head = 0;
    ring_buf->tail = 0;

    /* Set baud rate  */
    integer_part = ((25 * clk_speed) / (4 * baud));
    tmp = (integer_part / 100) << 4;

    fractional_part = integer_part - (100 * (tmp >> 4));
    tmp |= (((fractional_part * 16) + 50) / 100) & ((uint8)0x0F);

    port->BRR = (uint16_t)tmp;

    port->CR1 = USART_TE          |    // transmitter enable
                USART_RE          |    // receiver enable
                USART_RXNEIE;          // receive interrupt enable


    /* Enable the USART and set mode to 8n1 */
    port->CR1 |= USART_UE;
}


/**
 *  @brief Turn off a USART.
 *
 *  @param USART to be disabled
 *
 *  @sideeffect Turns off the specified USART
 */
void usart_disable(uint8 usart_num) {
    ASSERT((usart_num <= NR_USARTS) && (usart_num > 0));
    usart_port *port;

    switch (usart_num) {
    case 1:
        port = (usart_port*)USART1_BASE;
        break;
    case 2:
        port = (usart_port*)USART2_BASE;
        break;
    case 3:
        port = (usart_port*)USART3_BASE;
        break;
    default:
        /* should never get here  */
        ASSERT(0);
    }

    /* Is this usart enabled?  */
    if (!(port->SR & USART_UE))
        return;

    /* TC bit must be high before disabling the usart  */
    while ((port->SR & USART_TC) == 0)
        ;

    /* Disable UE */
    port->CR1 = 0;
}


/**
 *  @brief Print a null terminated string to the specified USART
 *
 *  @param[in] usart_num USART to send on
 *  @param[in] str String to send
 */
void usart_putstr(uint8 usart_num, const char* str) {
    ASSERT((usart_num <= NR_USARTS) && (usart_num > 0));
    char ch;

    while((ch = *(str++)) != '\0') {
        usart_putc(usart_num, ch);
    }
}

/**
 *  @brief Print an unsigned integer to the specified usart
 *
 *  @param[in] usart_num usart to send on
 *  @param[in] val number to print
 */
void usart_putudec(uint8 usart_num, uint32 val) {
    ASSERT((usart_num <= NR_USARTS) && (usart_num > 0));
    char digits[12];
    int i;

    i = 0;
    do {
        digits[i++] = val % 10 + '0';
        val /= 10;
    } while (val > 0);
    while (--i >= 0) {
        usart_putc(usart_num, digits[i]);
    }

}


/**
 *  @brief Return one character from the receive buffer. Assumes
 *  that there is data available.
 *
 *  @param[in] usart_num number of the usart to read from
 *
 *  @return character from ring buffer
 *
 *  @sideeffect may update the head pointer of the recv buffer
 */
uint8 usart_getc(uint8 usart_num) {
    uint8 ch;
    usart_ring_buf *rb;

    switch (usart_num) {
    case 1:
        rb = &ring_buf1;
        break;
    case 2:
        rb = &ring_buf2;
        break;
    case 3:
        rb = &ring_buf3;
        break;
    default:
        ASSERT(0);
    }

    /* Make sure there's actually data to be read  */
    ASSERT(rb->head != rb->tail);

    /* Read the data and check for wraparound  */
    ch = rb->buf[rb->head++];
    rb->head %= USART_RECV_BUF_SIZE;

    return ch;
}

uint32 usart_data_available(uint8 usart_num) {
    usart_ring_buf *rb;

    switch (usart_num) {
    case 1:
        rb = &ring_buf1;
        break;
    case 2:
        rb = &ring_buf2;
        break;
    case 3:
        rb = &ring_buf3;
        break;
    default:
        ASSERT(0);
    }

    return rb->tail - rb->head;
}



/**
 *  @brief Output a character out the uart
 *
 *  @param[in] usart_num usart number to output on
 *  @param[in] ch character to send
 *
 */
void usart_putc(uint8 usart_num, uint8 ch) {
    ASSERT((usart_num <= NR_USARTS) && (usart_num > 0));
    usart_port *port;

    switch (usart_num) {
    case 1:
        port = (usart_port*)USART1_BASE;
        break;
    case 2:
        port = (usart_port*)USART2_BASE;
        break;
    case 3:
        port = (usart_port*)USART3_BASE;
        break;
    default:
        /* Should never get here  */
        ASSERT(0);
    }

    if (ch == '\n') {
        usart_putc(usart_num, '\r');
    }

    port->DR = ch;

    /* Wait for transmission to complete  */
    while ((port->SR & USART_TXE) == 0)
        ;
}


