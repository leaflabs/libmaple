/* *****************************************************************************
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
 * ****************************************************************************/

/**
 *  @file util.h
 *
 *  @brief Utility procedures for debugging, mostly an error LED fade and
 *  messages dumped over a uart for failed asserts.
 */

#include "libmaple.h"
#include "usart.h"
#include "gpio.h"
#include "nvic.h"
#include "adc.h"
#include "timers.h"

#define ERROR_LED_PORT         GPIOA_BASE
#define ERROR_LED_PIN          5
#define ERROR_USART_NUM        2
#define ERROR_USART_BAUD       9600
#define ERROR_TX_PIN           2
#define ERROR_TX_PORT          GPIOA_BASE

/* Error assert + fade */
void _fail(const char* file, int line, const char* exp) {
    int32  slope   = 1;
    uint32 CC      = 0x0000;
    uint32 TOP_CNT = 0x02FF;
    uint32 i       = 0;

    /* Turn off interrupts */
    nvic_disable_interrupts();

    /* Turn off timers  */
    timer_disable_all();

    /* Turn off ADC */
    adc_disable();

    /* Turn off all usarts  */
    usart_disable(1);
    usart_disable(2);
    usart_disable(3);

    /* Initialize the error usart */
    gpio_set_mode(ERROR_TX_PORT, ERROR_TX_PIN, GPIO_MODE_AF_OUTPUT_PP);
    usart_init(ERROR_USART_NUM, ERROR_USART_BAUD);

    /* Print failed assert message  */
    usart_putstr(ERROR_USART_NUM, "ERROR: FAILED ASSERT(");
    usart_putstr(ERROR_USART_NUM, exp);
    usart_putstr(ERROR_USART_NUM, "): ");
    usart_putstr(ERROR_USART_NUM, file);
    usart_putstr(ERROR_USART_NUM, ": ");
    usart_putudec(ERROR_USART_NUM, line);
    usart_putc(ERROR_USART_NUM, '\n');

    /* Turn on the error LED  */
    gpio_set_mode(ERROR_LED_PORT, ERROR_LED_PIN, GPIO_MODE_OUTPUT_PP);

    /* Turn the USB interrupt back on so the bootloader keeps on functioning  */
    nvic_enable_interrupt(NVIC_INT_USBHP);
    nvic_enable_interrupt(NVIC_INT_USBLP);

    /* Error fade  */
    while (1) {
        if (CC == TOP_CNT)  {
            slope = -1;
        } else if (CC == 0) {
            slope = 1;
        }

        if (i == TOP_CNT)  {
            CC += slope;
            i = 0;
        }

        if (i < CC) {
            gpio_write_bit(ERROR_LED_PORT, ERROR_LED_PIN, 1);
        } else {
            gpio_write_bit(ERROR_LED_PORT, ERROR_LED_PIN, 0);
        }
        i++;
    }
}

