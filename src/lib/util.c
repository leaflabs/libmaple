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
 *  Created: 12/18/09 02:38:44
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
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
    int32_t  slope   = 1;
    int32_t CC      = 0x0000;
    int32_t TOP_CNT = 0x02FF;
    int32_t i       = 0;

    /* Turn off interrupts */
    nvic_disable_interrupts();

    /* Turn off timers  */
    timers_disable();

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

