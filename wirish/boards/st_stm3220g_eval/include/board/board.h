/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2012 LeafLabs, LLC.
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
 * @file   wirish/boards/st_stm3220g_eval/include/board/board.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  STM3220G-EVAL board stub header.
 *
 * This (and the corresponding board.cpp) needs to be fixed and
 * fleshed out. Do it later? Maybe someone who wants support for this
 * board will do it.
 */

#ifndef _BOARD_ST_STM3220G_EVAL_H_
#define _BOARD_ST_STM3220G_EVAL_H_

#define CYCLES_PER_MICROSECOND  120
#define SYSTICK_RELOAD_VAL      119999 /* takes a cycle to reload */

#define BOARD_BUTTON_PIN        5
#define BOARD_LED_PIN           0

#define BOARD_NR_USARTS         0
#define BOARD_NR_SPI            0
#define BOARD_NR_GPIO_PINS      6
#define BOARD_NR_PWM_PINS       0
#define BOARD_NR_ADC_PINS       0
#define BOARD_NR_USED_PINS      6

#endif
