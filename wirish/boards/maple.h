/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 LeafLabs, LLC.
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
 * @file   maple.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  Private include file for Maple in boards.h
 */

#include "wirish_types.h"

#ifndef _BOARD_MAPLE_H_
#define _BOARD_MAPLE_H_

#define CYCLES_PER_MICROSECOND  72
#define SYSTICK_RELOAD_VAL      71999 /* takes a cycle to reload */

#define BOARD_BUTTON_PIN        38
#define BOARD_LED_PIN           13

/* Number of USARTs/UARTs whose pins are broken out to headers */
#define NR_USARTS               3

/* Default USART pin numbers (not considering AFIO remap) */
#define BOARD_USART1_TX_PIN     7
#define BOARD_USART1_RX_PIN     8
#define BOARD_USART2_TX_PIN     1
#define BOARD_USART2_RX_PIN     0
#define BOARD_USART3_TX_PIN     29
#define BOARD_USART3_RX_PIN     30

/* Total number of GPIO pins that are broken out to headers and
   intended for general use. */
#define NR_GPIO_PINS            39

#endif
