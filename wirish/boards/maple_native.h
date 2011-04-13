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
 * @file   maple_native.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  Private include file for Maple Native in boards.h
 *
 * See maple.h for more information on these definitions.
 */

#include "gpio.h"
#include "timer.h"

#include "wirish_types.h"

#ifndef _BOARD_MAPLE_NATIVE_H_
#define _BOARD_MAPLE_NATIVE_H_

#define CYCLES_PER_MICROSECOND  72
#define SYSTICK_RELOAD_VAL      71999

#define BOARD_LED_PIN           22
#define BOARD_BUTTON_PIN        6

#define BOARD_NR_USARTS         5
#define BOARD_USART1_TX_PIN     26
#define BOARD_USART1_RX_PIN     27
#define BOARD_USART2_TX_PIN     52
#define BOARD_USART2_RX_PIN     53
#define BOARD_USART3_TX_PIN     0
#define BOARD_USART3_RX_PIN     1
#define BOARD_UART4_TX_PIN      19
#define BOARD_UART4_RX_PIN      20
#define BOARD_UART5_TX_PIN      21
#define BOARD_UART5_RX_PIN      29

#define BOARD_NR_GPIO_PINS      101
#define BOARD_NR_PWM_PINS       18
#define BOARD_NR_ADC_PINS       21
/* FIXME! this isn't true at all; almost all of the triple header pins
 * are used by the FSMC by default.  Fix this (and the corresponding
 * boardUsedPins definition in maple_native.cpp) by QA time. */
#define BOARD_NR_USED_PINS      2

#endif
