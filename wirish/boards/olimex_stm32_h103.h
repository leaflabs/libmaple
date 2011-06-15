/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 LeafLabs, LLC.
 * Copyright (c) 2011 David Kiliani.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file   olimex_stm32_h103.h
 * @author David Kiliani <mail@davidkiliani.de>
 * @brief  Private include file for Olimex STM32_H103 in boards.h
 */

#ifndef _BOARD_OLIMEX_STM32_H103_H_
#define _BOARD_OLIMEX_STM32_H103_H_

#define CYCLES_PER_MICROSECOND  72
#define SYSTICK_RELOAD_VAL      71999 /* takes a cycle to reload */

#define BOARD_BUTTON_PIN        23
#define BOARD_LED_PIN           7

/* Number of USARTs/UARTs whose pins are broken out to headers */
#define BOARD_NR_USARTS         3

/* Default USART pin numbers (not considering AFIO remap) */
#define BOARD_USART1_TX_PIN     3
#define BOARD_USART1_RX_PIN     4
#define BOARD_USART2_TX_PIN     24
#define BOARD_USART2_RX_PIN     27
#define BOARD_USART3_TX_PIN     31
#define BOARD_USART3_RX_PIN     32

/* Number of SPI ports */
#define BOARD_NR_SPI            2

/* Default SPI pin numbers (not considering AFIO remap) */
#define BOARD_SPI1_NSS_PIN      28
#define BOARD_SPI1_MOSI_PIN     19
#define BOARD_SPI1_MISO_PIN     11
#define BOARD_SPI1_SCK_PIN      15
#define BOARD_SPI2_NSS_PIN      34
#define BOARD_SPI2_MOSI_PIN     36
#define BOARD_SPI2_MISO_PIN     35
#define BOARD_SPI2_SCK_PIN      33

/* Total number of GPIO pins that are broken out to headers and
 * intended for general use. */
#define BOARD_NR_GPIO_PINS      46

/* Number of pins capable of PWM output */
#define BOARD_NR_PWM_PINS       16

/* Number of pins capable of ADC conversion */
#define BOARD_NR_ADC_PINS       16

/* Number of pins already connected to external hardware.  For Maple,
 * these are just BOARD_LED_PIN and BOARD_BUTTON_PIN. */
#define BOARD_NR_USED_PINS       7

/* Debug port pins */
#define BOARD_JTMS_SWDIO_PIN    41
#define BOARD_JTCK_SWCLK_PIN    42
#define BOARD_JTDI_PIN          43
#define BOARD_JTDO_PIN          44
#define BOARD_NJTRST_PIN        45

/* USB configuration */
#define BOARD_USB_DISC_DEV      GPIOC
#define BOARD_USB_DISC_BIT      11

#endif
