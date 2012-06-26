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
 * @file   wirish/boards/olimex_stm32_h103/board.cpp
 * @author David Kiliani <mail@davidkiliani.de>
 * @brief  Olimex STM32_H103 board file.
 */

#include <board/board.h>

#include <libmaple/gpio.h>
#include <libmaple/timer.h>

#include <wirish/wirish_types.h>

void boardInit(void) {
}

extern const stm32_pin_info PIN_MAP[BOARD_NR_GPIO_PINS] = {

    /* Header EXT1 */

    {GPIOA, TIMER1, NULL, 11, 4, ADCx}, /* D0/EXT1_1/PA11 (USBDM) */
    {GPIOA, TIMER1, NULL,  8, 1, ADCx}, /* D1/EXT1_2/PA8 */
    {GPIOA,   NULL, NULL, 12, 0, ADCx}, /* D2/EXT1_3/PA12 (USBDP) */
    {GPIOA, TIMER1, NULL,  9, 2, ADCx}, /* D3/EXT1_4/PA9 */

    {GPIOA, TIMER1, NULL, 10, 3, ADCx}, /* D4/EXT1_7/PA10 */
    {GPIOC,   NULL, NULL, 10, 0, ADCx}, /* D5/EXT1_8/PC10 */
    {GPIOC,   NULL, NULL, 11, 0, ADCx}, /* D6/EXT1_9/PC11 (USBpull) */
    {GPIOC,   NULL, NULL, 12, 0, ADCx}, /* D7/EXT1_10/PC12 (LED) */
    {GPIOD,   NULL, NULL,  2, 0, ADCx}, /* D8/EXT1_11/PD2 */
    {GPIOB,   NULL, NULL,  5, 0, ADCx}, /* D9/EXT1_12/PB5 */
    {GPIOB, TIMER4, NULL,  6, 1, ADCx}, /* D10/EXT1_13/PB6 */
    {GPIOA, TIMER3, ADC1,  6, 1,    6}, /* D11/EXT1_14/PA6 */
    {GPIOB, TIMER4, NULL,  7, 2, ADCx}, /* D12/EXT1_15/PB7 */
    {GPIOB, TIMER4, NULL,  8, 3, ADCx}, /* D13/EXT1_16/PB8 */
    {GPIOB, TIMER4, NULL,  9, 4, ADCx}, /* D14/EXT1_17/PB9 */
    {GPIOA,   NULL, ADC1,  5, 0,    5}, /* D15/EXT1_18/PA5 */
    {GPIOC,   NULL, ADC1,  0, 0,   10}, /* D16/EXT1_19/PC0 */
    {GPIOC,   NULL, ADC1,  1, 0,   11}, /* D17/EXT1_20/PC1 */
    {GPIOB, TIMER3, ADC1,  0, 3,    8}, /* D18/EXT1_21/PB0 */
    {GPIOA, TIMER3, ADC1,  7, 2,    7}, /* D19/EXT1_22/PA7 */

    {GPIOC,   NULL, NULL, 13, 0, ADCx}, /* D20/EXT1_24/PC13 */

    {GPIOB, TIMER3, ADC1,  1, 4,    9}, /* D21/EXT1_26/PB1 */

    /* Header EXT2 */

    {GPIOC,   NULL, ADC1,  2, 0,   12}, /* D22/EXT2_2/PC2 */

    {GPIOA, TIMER2, ADC1,  0, 1,    0}, /* D23/EXT2_4/PA0 (BUT) */

    {GPIOA, TIMER2, ADC1,  2, 3,    2}, /* D24/EXT2_7/PA2 */
    {GPIOA, TIMER2, ADC1,  1, 2,    1}, /* D25/EXT2_8/PA1 */
    {GPIOC,   NULL, ADC1,  3, 0,   13}, /* D26/EXT2_9/PC3 */
    {GPIOA, TIMER2, ADC1,  3, 4,    3}, /* D27/EXT2_10/PA3 */
    {GPIOA,   NULL, ADC1,  4, 0,    4}, /* D28/EXT2_11/PA4 */
    {GPIOC,   NULL, ADC1,  4, 0,   14}, /* D29/EXT2_12/PC4 (USB-P) */
    {GPIOC,   NULL, ADC1,  5, 0,   15}, /* D30/EXT2_13/PC5 */
    {GPIOB,   NULL, NULL, 10, 0, ADCx}, /* D31/EXT2_14/PB10 */
    {GPIOB,   NULL, NULL, 11, 0, ADCx}, /* D32/EXT2_15/PB11 */
    {GPIOB,   NULL, NULL, 13, 0, ADCx}, /* D33/EXT2_16/PB13 */
    {GPIOB,   NULL, NULL, 12, 0, ADCx}, /* D34/EXT2_17/PB12 */
    {GPIOB,   NULL, NULL, 14, 0, ADCx}, /* D35/EXT2_18/PB14 */
    {GPIOB,   NULL, NULL, 15, 0, ADCx}, /* D36/EXT2_19/PB15 */
    {GPIOC,   NULL, NULL,  6, 0, ADCx}, /* D37/EXT2_20/PC6 */
    {GPIOC,   NULL, NULL,  7, 0, ADCx}, /* D38/EXT2_21/PC7 */
    {GPIOC,   NULL, NULL,  8, 0, ADCx}, /* D39/EXT2_22/PC8 */

    {GPIOC,   NULL, NULL,  9, 0, ADCx}, /* D40/EXT2_24/PC9 */

    /* JTAG header */

    {GPIOA,   NULL, NULL, 13, 0, ADCx}, /* D41/JTAG7/PA13 */
    {GPIOA,   NULL, NULL, 14, 0, ADCx}, /* D42/JTAG9/PA14 */
    {GPIOA,   NULL, NULL, 15, 0, ADCx}, /* D43/JTAG5/PA15 */
    {GPIOB,   NULL, NULL,  3, 0, ADCx}, /* D44/JTAG13/PB3  */
    {GPIOB,   NULL, NULL,  4, 0, ADCx}, /* D45/JTAG3/PB4  */
};

extern const uint8 boardPWMPins[] __FLASH__ = {
    0, 1, 3, 4, 10, 11, 12, 13, 14, 18, 19, 21, 23, 24, 25, 27
};

extern const uint8 boardADCPins[] __FLASH__ = {
    11, 15, 16, 17, 18, 19, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30
};

extern const uint8 boardUsedPins[] __FLASH__ = {
    BOARD_LED_PIN, BOARD_BUTTON_PIN, BOARD_JTMS_SWDIO_PIN,
    BOARD_JTCK_SWCLK_PIN, BOARD_JTDI_PIN, BOARD_JTDO_PIN, BOARD_NJTRST_PIN
};
