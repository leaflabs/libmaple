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
 * @file   wirish/boards/mini_stm32/board.cpp
 * @author Daniel Serpell <daniel.serpell@gmail.com>
 * @brief  Board file for mini STM32F103C8T6 board from www.lctech-inc.com.
 *
 * Board is available from:
 * http://www.lctech-inc.com/Hardware/Detail.aspx?id=0172e854-77b0-43d5-b300-68e570c914fd
 *
 * Based on maple-mini configuration.
 */

#include <board/board.h>

#include <libmaple/gpio.h>
#include <libmaple/timer.h>

#include <wirish/wirish_debug.h>
#include <wirish/wirish_types.h>

/* Only enable SWD debugging to maximize utilizable pins. */
void boardInit(void) {
    afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);
}

extern const stm32_pin_info PIN_MAP[BOARD_NR_GPIO_PINS] = {

    /* P8 */

    /* 1  3.3V */
    /* 2  VddA */
    {GPIOA, TIMER2, ADC1,  0, 1,    0}, /*  3  PA0    D0 */
    {GPIOA, TIMER2, ADC1,  1, 2,    1}, /*  4  PA1    D1 */
    {GPIOA, TIMER2, ADC1,  2, 3,    2}, /*  5  PA2    D2 */
    {GPIOA, TIMER2, ADC1,  3, 4,    3}, /*  6  PA3    D3 */
    {GPIOA,   NULL, ADC1,  4, 0,    4}, /*  7  PA4    D4 */
    {GPIOA,   NULL, ADC1,  5, 0,    5}, /*  8  PA5    D5 */
    {GPIOA, TIMER3, ADC1,  6, 1,    6}, /*  9  PA6    D6 */
    {GPIOA, TIMER3, ADC1,  7, 2,    7}, /* 10  PA7    D7 */
    {GPIOB, TIMER3, ADC1,  0, 3,    8}, /* 11  PB0    D8 */
    {GPIOB, TIMER3, ADC1,  1, 4,    9}, /* 12  PB1    D9 */
    {GPIOB,   NULL, NULL,  2, 0, ADCx}, /* 13  PB2   D10 */
    {GPIOB,   NULL, NULL, 10, 0, ADCx}, /* 14  PB10  D11 */
    {GPIOB,   NULL, NULL, 12, 0, ADCx}, /* 15  PB12  D12 */
    {GPIOB,   NULL, NULL, 11, 0, ADCx}, /* 16  PB11  D13 */
    {GPIOB,   NULL, NULL, 14, 0, ADCx}, /* 17  PB14  D14 */
    {GPIOB,   NULL, NULL, 13, 0, ADCx}, /* 18  PB13  D15 */
    {GPIOA, TIMER1, NULL,  8, 1, ADCx}, /* 19  PA8   D16 */
    {GPIOB,   NULL, NULL, 15, 0, ADCx}, /* 20  PB15  D17 */
    {GPIOA, TIMER1, NULL, 10, 3, ADCx}, /* 21  PA10  D18 */
    {GPIOA, TIMER1, NULL,  9, 2, ADCx}, /* 22  PA9   D19 */
    /* 23  GND */
    /* 24  GND */

    /* P9 */

    /* 1  3.3V */
    /* 2  3.3V */
    /* 3  NRST */
    /* 4  OSC_OUT */
    /* 5  OSC_IN  */
    {GPIOC,   NULL, NULL, 15, 0, ADCx}, /*  6  PC15  D20 */
    {GPIOC,   NULL, NULL, 14, 0, ADCx}, /*  7  PC14  D21 */
    {GPIOC,   NULL, NULL, 13, 0, ADCx}, /*  8  PC13  D22 */
    /* 9  VBat */
    {GPIOB, TIMER4, NULL,  9, 4, ADCx}, /* 10  PB9   D23 */
    {GPIOB, TIMER4, NULL,  8, 3, ADCx}, /* 11  PB8   D24 */
    /* 12  BOOT0 */
    {GPIOB, TIMER4, NULL,  7, 2, ADCx}, /* 13  PB7   D25 */
    {GPIOB, TIMER4, NULL,  6, 1, ADCx}, /* 14  PB6   D26 */
    {GPIOB,   NULL, NULL,  5, 0, ADCx}, /* 15  PB5   D27 */
    {GPIOB,   NULL, NULL,  4, 0, ADCx}, /* 16  PB4   D28  JNTRST */
    {GPIOB,   NULL, NULL,  3, 0, ADCx}, /* 17  PB3   D29  JTDO */
    {GPIOA,   NULL, NULL, 15, 0, ADCx}, /* 18  PA15  D30  JTDI */
    {GPIOA,   NULL, NULL, 14, 0, ADCx}, /* 19  PA14  D31 SWCLK */
    {GPIOA,   NULL, NULL, 13, 0, ADCx}, /* 20  PA13  D32 SWDIO */
    {GPIOA,   NULL, NULL, 12, 0, ADCx}, /* 21  PA12  D33  USB+ */
    {GPIOA, TIMER1, NULL, 11, 4, ADCx}  /* 22  PA11  D34  USB- */
    /* 23  GND */
    /* 24  GND */

    /* UART CONNECTOR */
    /* 1  5V IN/OUT */
    //{GPIOA, TIMER1, NULL,  9, 2, ADCx}, /*  2/PA9   TX */
    //{GPIOA, TIMER1, NULL, 10, 3, ADCx}, /*  3/PA10  RX */
    /* 4  GND */

    /* JTAG CONNECTOR */
    /* 1  3.3V OUT */
    //{GPIOB,   NULL, NULL,  4, 0, ADCx}, /*  3/PB4  */
    //{GPIOA,   NULL, NULL, 15, 0, ADCx}, /*  5/PA15 */
    //{GPIOA,   NULL, NULL, 13, 0, ADCx}, /*  7/PA13 */
    //{GPIOA,   NULL, NULL, 14, 0, ADCx}, /*  9/PA14 */
    /* 11 ?? */
    //{GPIOB,   NULL, NULL,  3, 0, ADCx}, /* 13/PB3  */

};

extern const uint8 boardPWMPins[BOARD_NR_PWM_PINS] __FLASH__ = {
    0, 1, 2, 3, 6, 7, 8, 9, 16, 18, 19, 23, 24, 25, 26, 34
};

extern const uint8 boardADCPins[BOARD_NR_ADC_PINS] __FLASH__ = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

#define USB_DP 33
#define USB_DM 34

#define OSC32_IN  21
#define OSC32_OUT 20

extern const uint8 boardUsedPins[BOARD_NR_USED_PINS] __FLASH__ = {
    OSC32_IN, OSC32_OUT, USB_DP, USB_DM
};
