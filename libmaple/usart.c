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
 * @brief USART control routines
 */

#include "libmaple.h"
#include "rcc.h"
#include "nvic.h"
#include "usart.h"

#define USART1_BASE    0x40013800
#define USART2_BASE    0x40004400
#define USART3_BASE    0x40004800
#define UART4_BASE     0x40004C00  // High-density devices only (Maple Native)
#define UART5_BASE     0x40005000  // High-density devices only (Maple Native)

#define USART_UE       BIT(13)
#define USART_M        BIT(12)
#define USART_TE       BIT(3)
#define USART_RE       BIT(2)
#define USART_RXNEIE   BIT(5)  // read data register not empty interrupt enable
#define USART_TC       BIT(6)

/* usart descriptor table  */
struct usart_dev usart_dev_table[] = {
    [USART1] = {
        .base = (usart_port*)USART1_BASE,
        .rcc_dev_num = RCC_USART1,
        .nvic_dev_num = NVIC_USART1
    },
    [USART2] = {
        .base = (usart_port*)USART2_BASE,
        .rcc_dev_num = RCC_USART2,
        .nvic_dev_num = NVIC_USART2
    },
    [USART3] = {
        .base = (usart_port*)USART3_BASE,
        .rcc_dev_num = RCC_USART3,
        .nvic_dev_num = NVIC_USART3
    },
#ifdef STM32_HIGH_DENSITY
    /* TODO test */
    [UART4] = {
        .base = (usart_port*)UART4_BASE,
        .rcc_dev_num = RCC_UART4,
        .nvic_dev_num = NVIC_UART4
    },
    [UART5] = {
        .base = (usart_port*)UART5_BASE,
        .rcc_dev_num = RCC_UART5,
        .nvic_dev_num = NVIC_UART5
    },
#endif
};

/*
 * Usart interrupt handlers.
 */

static inline void usart_irq(int usart_num) {
#ifdef USART_SAFE_INSERT
    /* Ignore old bytes if the user defines USART_SAFE_INSERT. */
    rb_safe_insert(&(usart_dev_table[usart_num].rb),
                   (uint8)((usart_dev_table[usart_num].base)->DR));
#else
    /* By default, push bytes around in the ring buffer. */
    rb_push_insert(&(usart_dev_table[usart_num].rb),
                   (uint8)((usart_dev_table[usart_num].base)->DR));
#endif
}

/* TODO: Check the disassembly for the following functions to make
   sure GCC inlined properly. */

void __irq_usart1(void) {
    usart_irq(USART1);
}

void __irq_usart2(void) {
    usart_irq(USART2);
}

void __irq_usart3(void) {
    usart_irq(USART3);
}

#ifdef STM32_HIGH_DENSITY
void __irq_uart4(void) {
    usart_irq(UART4);
}

void __irq_uart5(void) {
    usart_irq(UART5);
}
#endif

/**
 *  @brief Enable a USART in single buffer transmission mode, multibuffer
 *     receiver mode.
 *  @param usart_num USART to be initialized
 *  @param baud Baud rate to be set at
 */
void usart_init(uint8 usart_num, uint32 baud) {
#ifdef STM32_HIGH_DENSITY
    ASSERT(usart_num <= UART5);
#else
    ASSERT(usart_num <= USART3);
#endif
    usart_port *port;
    ring_buffer *ring_buf;

    uint32 clk_speed;
    uint32 integer_part;
    uint32 fractional_part;
    uint32 tmp;

    port = usart_dev_table[usart_num].base;
    rcc_clk_enable(usart_dev_table[usart_num].rcc_dev_num);
    nvic_irq_enable(usart_dev_table[usart_num].nvic_dev_num);

    /* usart1 is mad fast  */
    clk_speed = (usart_num == USART1) ? 72000000UL : 36000000UL;

    /* Initialize rx ring buffer  */
    rb_init(&usart_dev_table[usart_num].rb,
            sizeof (usart_dev_table[usart_num].rx_buf),
            usart_dev_table[usart_num].rx_buf);

    /* Set baud rate  */
    integer_part = ((25 * clk_speed) / (4 * baud));
    tmp = (integer_part / 100) << 4;

    fractional_part = integer_part - (100 * (tmp >> 4));
    tmp |= (((fractional_part * 16) + 50) / 100) & ((uint8)0x0F);

    port->BRR = (uint16)tmp;

    port->CR1 = USART_TE          |    // transmitter enable
                USART_RE          |    // receiver enable
                USART_RXNEIE;          // receive interrupt enable


    /* Enable the USART and set mode to 8n1 */
    port->CR1 |= USART_UE;
}

/**
 *  @brief Turn off all USARTs.
 */
void usart_disable_all() {
    usart_disable(USART1);
    usart_disable(USART2);
    usart_disable(USART3);
#ifdef STM32_HIGH_DENSITY
    usart_disable(UART4);
    usart_disable(UART5);
#endif
}

/**
 * @brief Turn off a USART.
 * @param USART to be disabled
 */
void usart_disable(uint8 usart_num) {
    usart_port *port = usart_dev_table[usart_num].base;

    /* TC bit must be high before disabling the usart  */
    while((port->CR1 & USART_UE) && !(port->SR & USART_TC))
        ;

    /* Disable UE */
    port->CR1 = 0;

    /* Clean up buffer */
    usart_reset_rx(usart_num);
}


/**
 * @brief Print a null terminated string to the specified USART
 *
 * @param usart_num usart to send on
 * @param str string to send
 */
void usart_putstr(uint8 usart_num, const char* str) {
    char ch;

    while((ch = *(str++)) != '\0') {
        usart_putc(usart_num, ch);
    }
}

/**
 * @brief Print an unsigned integer to the specified usart
 *
 * @param usart_num usart to send on
 * @param val number to print
 */
void usart_putudec(uint8 usart_num, uint32 val) {
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
