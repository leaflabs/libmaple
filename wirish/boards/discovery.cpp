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
 * @file   discovery.cpp
 * @author Anton Eltchaninov <anton.eltchaninov@gmail.com>
 * @brief  STM32VLDiscovery PIN_MAP and boardInit().
 */

#include "gpio.h"
#include "timer.h"

#include "discovery.h"

#ifdef BOARD_discovery

/* since we want the JTAG pins as GPIOs, disable JTAG debug support */
/* SW-DP Enabled */
void boardInit(void) {
    afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);
}

extern const stm32_pin_info PIN_MAP[BOARD_NR_GPIO_PINS] = {

    {GPIOA, TIMER2, ADC1,  3, 4,    3}, /* D0/PA3 */
    {GPIOA, TIMER2, ADC1,  2, 3,    2}, /* D1/PA2 */
    {GPIOA, TIMER2, ADC1,  0, 1,    0}, /* D2/PA0 (But)*/
    {GPIOA, TIMER2, ADC1,  1, 2,    1}, /* D3/PA1 */
    {GPIOB,   NULL, NULL,  5, 0, ADCx}, /* D4/PB5 */
    {GPIOB, TIMER4, NULL,  6, 1, ADCx}, /* D5/PB6 */
    {GPIOA, TIMER1, NULL,  8, 1, ADCx}, /* D6/PA8 */
    {GPIOA, TIMER1, NULL,  9, 2, ADCx}, /* D7/PA9 */
    {GPIOA, TIMER1, NULL, 10, 3, ADCx}, /* D8/PA10 */
    {GPIOB, TIMER4, NULL,  7, 2, ADCx}, /* D9/PB7 */
    {GPIOA,   NULL, ADC1,  4, 0,    4}, /* D10/PA4 */
    {GPIOA, TIMER3, ADC1,  7, 2,    7}, /* D11/PA7 */
    {GPIOA, TIMER3, ADC1,  6, 1,    6}, /* D12/PA6 */
    {GPIOA,   NULL, ADC1,  5, 0,    5}, /* D13/PA5 */
    {GPIOB, TIMER4, NULL,  8, 3, ADCx}, /* D14/PB8 */
    {GPIOC,   NULL, ADC1,  0, 0,   10}, /* D15/PC0 */
    {GPIOC,   NULL, ADC1,  1, 0,   11}, /* D16/PC1 */
    {GPIOC,   NULL, ADC1,  2, 0,   12}, /* D17/PC2 */
    {GPIOC,   NULL, ADC1,  3, 0,   13}, /* D18/PC3 */
    {GPIOC,   NULL, ADC1,  4, 0,   14}, /* D19/PC4 */
    {GPIOC,   NULL, ADC1,  5, 0,   15}, /* D20/PC5 */
    {GPIOC,   NULL, NULL, 13, 0, ADCx}, /* D21/PC13 */
    {GPIOC,   NULL, NULL, 14, 0, ADCx}, /* D22/PC14 */
    {GPIOC,   NULL, NULL, 15, 0, ADCx}, /* D23/PC15 */
    {GPIOB, TIMER4, NULL,  9, 4, ADCx}, /* D24/PB9 */
    {GPIOD,   NULL, NULL,  2, 0, ADCx}, /* D25/PD2 */
    {GPIOC,   NULL, NULL, 10, 0, ADCx}, /* D26/PC10 */
    {GPIOB, TIMER3, ADC1,  0, 3,    8}, /* D27/PB0 */
    {GPIOB, TIMER3, ADC1,  1, 4,    9}, /* D28/PB1 */
    {GPIOB,   NULL, NULL, 10, 0, ADCx}, /* D29/PB10 */
    {GPIOB,   NULL, NULL, 11, 0, ADCx}, /* D30/PB11 */
    {GPIOB,   NULL, NULL, 12, 0, ADCx}, /* D31/PB12 */
    {GPIOB,   NULL, NULL, 13, 0, ADCx}, /* D32/PB13 */
    {GPIOB,   NULL, NULL, 14, 0, ADCx}, /* D33/PB14 */
    {GPIOB,   NULL, NULL, 15, 0, ADCx}, /* D34/PB15 */
    {GPIOC,   NULL, NULL,  6, 0, ADCx}, /* D35/PC6 */
    {GPIOC,   NULL, NULL,  7, 0, ADCx}, /* D36/PC7 */
    {GPIOC,   NULL, NULL,  8, 0, ADCx}, /* D37/PC8 (Blue led)*/
    {GPIOC,   NULL, NULL,  9, 0, ADCx}, /* D38/PC9 (Green led)*/
    {GPIOA, TIMER1, NULL, 11, 4, ADCx}, /* D39/PA11 */
    {GPIOA,   NULL, NULL, 12, 0, ADCx}, /* D40/PA12 */
    {GPIOA,   NULL, NULL, 15, 0, ADCx}, /* D41/PA15 */
    {GPIOB,   NULL, NULL,  2, 0, ADCx}, /* D42/PB2 */
    {GPIOB,   NULL, NULL,  3, 0, ADCx}, /* D43/PB3 */
    {GPIOB,   NULL, NULL,  4, 0, ADCx}, /* D44/PB4 */
    {GPIOC,   NULL, NULL, 11, 0, ADCx}, /* D45/PC11 */
    {GPIOC,   NULL, NULL, 12, 0, ADCx}  /* D46/PC12 */
};

extern const uint8 boardPWMPins[] __FLASH__ = {
    0, 1, 2, 3, 5, 6, 7, 8, 9, 11, 12, 14, 24, 25, 27, 28, 39
};

extern const uint8 boardADCPins[] __FLASH__ = {
    0, 1, 2, 10, 11, 12, 13, 15, 16, 17, 18, 19, 20, 27, 28
};

extern const uint8 boardUsedPins[] __FLASH__ = {
    BOARD_LED_PIN, BOARD_GREEN_LED_PIN, BOARD_BUTTON_PIN
};


#endif
