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
 * @file   maple_native.cpp
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  Maple Native PIN_MAP and boardInit().
 */

#include "maple_native.h"
#include "native_sram.h"

#ifdef BOARD_maple_native

void boardInit(void) {
    initNativeSRAM();
}

extern const stm32_pin_info PIN_MAP[BOARD_NR_GPIO_PINS] = {

    /* Top header */

    {GPIOB,   NULL, NULL, 10, 0, ADCx}, /* D0/PB10 */
    {GPIOB,   NULL, NULL,  2, 0, ADCx}, /* D1/PB2 */
    {GPIOB,   NULL, NULL, 12, 0, ADCx}, /* D2/PB12 */
    {GPIOB,   NULL, NULL, 13, 0, ADCx}, /* D3/PB13 */
    {GPIOB,   NULL, NULL, 14, 0, ADCx}, /* D4/PB14 */
    {GPIOB,   NULL, NULL, 15, 0, ADCx}, /* D5/PB15 */
    {GPIOC,   NULL, ADC1,  0, 0,   10}, /* D6/PC0 */
    {GPIOC,   NULL, ADC1,  1, 0,   11}, /* D7/PC1 */
    {GPIOC,   NULL, ADC1,  2, 0,   12}, /* D8/PC2 */
    {GPIOC,   NULL, ADC1,  3, 0,   13}, /* D9/PC3 */
    {GPIOC,   NULL, ADC1,  4, 0,   14}, /* D10/PC4 */
    {GPIOC,   NULL, ADC1,  5, 0,   15}, /* D11/PC5 */
    {GPIOC, TIMER8, NULL,  6, 1, ADCx}, /* D12/PC6 */
    {GPIOC, TIMER8, NULL,  7, 2, ADCx}, /* D13/PC7 */
    {GPIOC, TIMER8, NULL,  8, 3, ADCx}, /* D14/PC8 */
    {GPIOC, TIMER8, NULL,  9, 4, ADCx}, /* D15/PC9 */
    {GPIOC,   NULL, NULL, 10, 0, ADCx}, /* D16/PC10 */
    {GPIOC,   NULL, NULL, 11, 0, ADCx}, /* D17/PC11 */
    {GPIOC,   NULL, NULL, 12, 0, ADCx}, /* D18/PC12 */
    {GPIOC,   NULL, NULL, 13, 0, ADCx}, /* D19/PC13 */
    {GPIOC,   NULL, NULL, 14, 0, ADCx}, /* D20/PC14 */
    {GPIOC,   NULL, NULL, 15, 0, ADCx}, /* D21/PC15 */
    {GPIOA, TIMER1, NULL,  8, 1, ADCx}, /* D22/PA8 */
    {GPIOA, TIMER1, NULL,  9, 2, ADCx}, /* D23/PA9 */
    {GPIOA, TIMER1, NULL, 10, 3, ADCx}, /* D24/PA10 */
    {GPIOB, TIMER4, NULL,  9, 4, ADCx}, /* D25/PB9 */

    /* Bottom header */
    /* Note: D{48, 49, 50} are also TIMER2_CH{2, 3, 4}, respectively. */

    {GPIOD,   NULL, NULL,  2, 0, ADCx}, /* D26/PD2 */
    {GPIOD,   NULL, NULL,  3, 0, ADCx}, /* D27/PD3 */
    {GPIOD,   NULL, NULL,  6, 0, ADCx}, /* D28/PD6 */
    {GPIOG,   NULL, NULL, 11, 0, ADCx}, /* D29/PG11 */
    {GPIOG,   NULL, NULL, 12, 0, ADCx}, /* D30/PG12 */
    {GPIOG,   NULL, NULL, 13, 0, ADCx}, /* D31/PG13 */
    {GPIOG,   NULL, NULL, 14, 0, ADCx}, /* D32/PG14 */
    {GPIOG,   NULL, NULL,  8, 0, ADCx}, /* D33/PG8 */
    {GPIOG,   NULL, NULL,  7, 0, ADCx}, /* D34/PG7 */
    {GPIOG,   NULL, NULL,  6, 0, ADCx}, /* D35/PG6 */
    {GPIOB,   NULL, NULL,  5, 0, ADCx}, /* D36/PB5 */
    {GPIOB, TIMER4, NULL,  6, 1, ADCx}, /* D37/PB6 */
    {GPIOB, TIMER4, NULL,  7, 2, ADCx}, /* D38/PB7 */
    {GPIOF,   NULL, ADC3,  6, 0,    4}, /* D39/PF6 */
    {GPIOF,   NULL, ADC3,  7, 0,    5}, /* D40/PF7 */
    {GPIOF,   NULL, ADC3,  8, 0,    6}, /* D41/PF8 */
    {GPIOF,   NULL, ADC3,  9, 0,    7}, /* D42/PF9 */
    {GPIOF,   NULL, ADC3, 10, 0,    8}, /* D43/PF10 */
    {GPIOF,   NULL, NULL, 11, 0, ADCx}, /* D44/PF11 */
    {GPIOB, TIMER3, ADC1,  1, 4,    9}, /* D45/PB1 */
    {GPIOB, TIMER3, ADC1,  0, 3,    8}, /* D46/PB0 */
    {GPIOA, TIMER5, ADC1,  0, 1,    0}, /* D47/PA0 */
    {GPIOA, TIMER5, ADC1,  1, 2,    1}, /* D48/PA1 */
    {GPIOA, TIMER5, ADC1,  2, 3,    2}, /* D49/PA2 */
    {GPIOA, TIMER5, ADC1,  3, 4,    3}, /* D50/PA3 */
    {GPIOA,   NULL, ADC1,  4, 0,    4}, /* D51/PA4 */
    {GPIOA,   NULL, ADC1,  5, 0,    5}, /* D52/PA5 */
    {GPIOA, TIMER3, ADC1,  6, 1,    6}, /* D53/PA6 */
    {GPIOA, TIMER3, ADC1,  7, 2,    7}, /* D54/PA7 */

    /* Right (triple) header */

    {GPIOF,   NULL, NULL,  0, 0, ADCx}, /* D55/PF0 */
    {GPIOD,   NULL, NULL, 11, 0, ADCx}, /* D56/PD11 */
    {GPIOD,   NULL, NULL, 14, 0, ADCx}, /* D57/PD14 */
    {GPIOF,   NULL, NULL,  1, 0, ADCx}, /* D58/PF1 */
    {GPIOD,   NULL, NULL, 12, 0, ADCx}, /* D59/PD12 */
    {GPIOD,   NULL, NULL, 15, 0, ADCx}, /* D60/PD15 */
    {GPIOF,   NULL, NULL,  2, 0, ADCx}, /* D61/PF2 */
    {GPIOD,   NULL, NULL, 13, 0, ADCx}, /* D62/PD13 */
    {GPIOD,   NULL, NULL,  0, 0, ADCx}, /* D63/PD0 */
    {GPIOF,   NULL, NULL,  3, 0, ADCx}, /* D64/PF3 */
    {GPIOE,   NULL, NULL,  3, 0, ADCx}, /* D65/PE3 */
    {GPIOD,   NULL, NULL,  1, 0, ADCx}, /* D66/PD1 */
    {GPIOF,   NULL, NULL,  4, 0, ADCx}, /* D67/PF4 */
    {GPIOE,   NULL, NULL,  4, 0, ADCx}, /* D68/PE4 */
    {GPIOE,   NULL, NULL,  7, 0, ADCx}, /* D69/PE7 */
    {GPIOF,   NULL, NULL,  5, 0, ADCx}, /* D70/PF5 */
    {GPIOE,   NULL, NULL,  5, 0, ADCx}, /* D71/PE5 */
    {GPIOE,   NULL, NULL,  8, 0, ADCx}, /* D72/PE8 */
    {GPIOF,   NULL, NULL, 12, 0, ADCx}, /* D73/PF12 */
    {GPIOE,   NULL, NULL,  6, 0, ADCx}, /* D74/PE6 */
    {GPIOE,   NULL, NULL,  9, 0, ADCx}, /* D75/PE9 */
    {GPIOF,   NULL, NULL, 13, 0, ADCx}, /* D76/PF13 */
    {GPIOE,   NULL, NULL, 10, 0, ADCx}, /* D77/PE10 */
    {GPIOF,   NULL, NULL, 14, 0, ADCx}, /* D78/PF14 */
    {GPIOG,   NULL, NULL,  9, 0, ADCx}, /* D79/PG9 */
    {GPIOE,   NULL, NULL, 11, 0, ADCx}, /* D80/PE11 */
    {GPIOF,   NULL, NULL, 15, 0, ADCx}, /* D81/PF15 */
    {GPIOG,   NULL, NULL, 10, 0, ADCx}, /* D82/PG10 */
    {GPIOE,   NULL, NULL, 12, 0, ADCx}, /* D83/PE12 */
    {GPIOG,   NULL, NULL,  0, 0, ADCx}, /* D84/PG0 */
    {GPIOD,   NULL, NULL,  5, 0, ADCx}, /* D85/PD5 */
    {GPIOE,   NULL, NULL, 13, 0, ADCx}, /* D86/PE13 */
    {GPIOG,   NULL, NULL,  1, 0, ADCx}, /* D87/PG1 */
    {GPIOD,   NULL, NULL,  4, 0, ADCx}, /* D88/PD4 */
    {GPIOE,   NULL, NULL, 14, 0, ADCx}, /* D89/PE14 */
    {GPIOG,   NULL, NULL,  2, 0, ADCx}, /* D90/PG2 */
    {GPIOE,   NULL, NULL,  1, 0, ADCx}, /* D91/PE1 */
    {GPIOE,   NULL, NULL, 15, 0, ADCx}, /* D92/PE15 */
    {GPIOG,   NULL, NULL,  3, 0, ADCx}, /* D93/PG3 */
    {GPIOE,   NULL, NULL,  0, 0, ADCx}, /* D94/PE0 */
    {GPIOD,   NULL, NULL,  8, 0, ADCx}, /* D95/PD8 */
    {GPIOG,   NULL, NULL,  4, 0, ADCx}, /* D96/PG4 */
    {GPIOD,   NULL, NULL,  9, 0, ADCx}, /* D97/PD9 */
    {GPIOG,   NULL, NULL,  5, 0, ADCx}, /* D98/PG5 */
    {GPIOD,   NULL, NULL, 10, 0, ADCx}  /* D99/PD10 */
};

extern const uint8 boardPWMPins[BOARD_NR_PWM_PINS] __FLASH__ = {
    12, 13, 14, 15, 22, 23, 24, 25, 37, 38, 45, 46, 47, 48, 49, 50, 53, 54
};

extern const uint8 boardADCPins[BOARD_NR_ADC_PINS] __FLASH__ = {
    6, 7, 8, 9, 10, 11, 39, 40, 41, 42, 43, 45, 46, 47, 48, 49, 50, 51, 52, 53,
    54
};

/* FIXME! see comment by BOARD_NR_USED_PINS in maple_native.h */
extern const uint8 boardUsedPins[BOARD_NR_USED_PINS] __FLASH__ = {
    BOARD_LED_PIN, BOARD_BUTTON_PIN
};

#endif
