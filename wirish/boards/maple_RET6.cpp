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
 * @file   maple_RET6.cpp
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  Maple RET6 Edition PIN_MAP and boardInit()
 */

#include "maple_RET6.h"

#ifdef BOARD_maple_RET6

void boardInit(void) {
}

stm32_pin_info PIN_MAP[NR_GPIO_PINS] = {
    {GPIOA, TIMER2,  3, 4,    3}, /* D0/PA3 */
    {GPIOA, TIMER2,  2, 3,    2}, /* D1/PA2 */
    {GPIOA, TIMER2,  0, 1,    0}, /* D2/PA0 */
    {GPIOA, TIMER2,  1, 2,    1}, /* D3/PA1 */
    {GPIOB,   NULL,  5, 0, ADCx}, /* D4/PB5 */
    {GPIOB, TIMER4,  6, 1, ADCx}, /* D5/PB6 */
    {GPIOA, TIMER1,  8, 1, ADCx}, /* D6/PA8 */
    {GPIOA, TIMER1,  9, 2, ADCx}, /* D7/PA9 */
    {GPIOA, TIMER1, 10, 3, ADCx}, /* D8/PA10 */
    {GPIOB, TIMER4,  7, 2, ADCx}, /* D9/PB7 */
    {GPIOA,   NULL,  4, 0,    4}, /* D10/PA4 */
    {GPIOA, TIMER3,  7, 2,    7}, /* D11/PA7 */
    {GPIOA, TIMER3,  6, 1,    6}, /* D12/PA6 */
    {GPIOA,   NULL,  5, 0,    5}, /* D13/PA5 (LED) */
    {GPIOB, TIMER4,  8, 3, ADCx}, /* D14/PB8 */

    /* Little header */

    {GPIOC,   NULL,  0, 0,   10}, /* D15/PC0 */
    {GPIOC,   NULL,  1, 0,   11}, /* D16/PC1 */
    {GPIOC,   NULL,  2, 0,   12}, /* D17/PC2 */
    {GPIOC,   NULL,  3, 0,   13}, /* D18/PC3 */
    {GPIOC,   NULL,  4, 0,   14}, /* D19/PC4 */
    {GPIOC,   NULL,  5, 0,   15}, /* D20/PC5 */

    /* External header */

    {GPIOC,   NULL, 13, 0, ADCx}, /* D21/PC13 */
    {GPIOC,   NULL, 14, 0, ADCx}, /* D22/PC14 */
    {GPIOC,   NULL, 15, 0, ADCx}, /* D23/PC15 */
    {GPIOB, TIMER4,  9, 4, ADCx}, /* D24/PB9 */
    {GPIOD,   NULL,  2, 0, ADCx}, /* D25/PD2 */
    {GPIOC,   NULL, 10, 0, ADCx}, /* D26/PC10 */
    {GPIOB, TIMER3,  0, 3,    8}, /* D27/PB0 */
    {GPIOB, TIMER3,  1, 4,    9}, /* D28/PB1 */
    {GPIOB,   NULL, 10, 0, ADCx}, /* D29/PB10 */
    {GPIOB,   NULL, 11, 0, ADCx}, /* D30/PB11 */
    {GPIOB,   NULL, 12, 0, ADCx}, /* D31/PB12 */
    {GPIOB,   NULL, 13, 0, ADCx}, /* D32/PB13 */
    {GPIOB,   NULL, 14, 0, ADCx}, /* D33/PB14 */
    {GPIOB,   NULL, 15, 0, ADCx}, /* D34/PB15 */
    {GPIOC, TIMER8,  6, 1, ADCx}, /* D35/PC6 */
    {GPIOC, TIMER8,  7, 2, ADCx}, /* D36/PC7 */
    {GPIOC, TIMER8,  8, 3, ADCx}, /* D37/PC8 */
    {GPIOC, TIMER8,  9, 4, ADCx}  /* D38/PC9 (BUT) */
};

#endif
