/* *****************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * ****************************************************************************/

/**
 *  @brief 
 */

#include "wirish.h"
#include "io.h"

#define ADC0     0
#define ADC1     1
#define ADC2     2
#define ADC3     3
#define ADC4     4
#define ADC5     5
#define ADC6     6
#define ADC7     7
#define ADC8     8
#define ADC9     9
#define ADC10    10
#define ADC11    11
#define ADC12    12
#define ADC13    13
#define ADC14    14
#define ADC15    15
#define ADC16    16

const PinMapping PIN_MAP[NR_MAPLE_PINS] = {
    {GPIOA_BASE,  3,        ADC3, TIMER2_CH4_CCR}, // D0/PA3
    {GPIOA_BASE,  2,        ADC2, TIMER2_CH3_CCR}, // D1/PA2
    {GPIOA_BASE,  0,        ADC0, TIMER2_CH1_CCR}, // D2/PA0
    {GPIOA_BASE,  1,        ADC1, TIMER2_CH2_CCR}, // D3/PA1
    {GPIOB_BASE,  5, ADC_INVALID,  TIMER_INVALID}, // D4/PB5
    {GPIOB_BASE,  6, ADC_INVALID, TIMER4_CH1_CCR}, // D5/PB6
    {GPIOA_BASE,  8, ADC_INVALID, TIMER1_CH1_CCR}, // D6/PA8
    {GPIOA_BASE,  9, ADC_INVALID, TIMER1_CH2_CCR}, // D7/PA9
    {GPIOA_BASE, 10, ADC_INVALID, TIMER1_CH3_CCR}, // D8/PA10
    {GPIOB_BASE,  7, ADC_INVALID, TIMER4_CH2_CCR}, // D9/PB7
    {GPIOA_BASE,  4,        ADC4,  TIMER_INVALID}, // D10/PA4
    {GPIOA_BASE,  7,        ADC7, TIMER3_CH2_CCR}, // D11/PA7
    {GPIOA_BASE,  6,        ADC6, TIMER3_CH1_CCR}, // D12/PA6
    {GPIOA_BASE,  5,        ADC5,  TIMER_INVALID}, // D13/PA5
    {GPIOB_BASE,  8, ADC_INVALID, TIMER4_CH3_CCR}, // D14/PB8
    /* Little header  */
    {GPIOC_BASE,  0,       ADC10,  TIMER_INVALID}, // D15/PC0
    {GPIOC_BASE,  1,       ADC11,  TIMER_INVALID}, // D16/PC1
    {GPIOC_BASE,  2,       ADC12,  TIMER_INVALID}, // D17/PC2
    {GPIOC_BASE,  3,       ADC13,  TIMER_INVALID}, // D18/PC3
    {GPIOC_BASE,  4,       ADC14,  TIMER_INVALID}, // D19/PC4
    {GPIOC_BASE,  5,       ADC15,  TIMER_INVALID}, // D20/PC5
    /* External header  */
    {GPIOC_BASE, 13, ADC_INVALID,  TIMER_INVALID}, // D21/PC13
    {GPIOC_BASE, 14, ADC_INVALID,  TIMER_INVALID}, // D22/PC14
    {GPIOC_BASE, 15, ADC_INVALID,  TIMER_INVALID}, // D23/PC15
    {GPIOB_BASE,  9, ADC_INVALID, TIMER4_CH4_CCR}, // D24/PB9
    {GPIOD_BASE,  2, ADC_INVALID,  TIMER_INVALID}, // D25/PD2
    {GPIOC_BASE, 10, ADC_INVALID,  TIMER_INVALID}, // D26/PC10
    {GPIOB_BASE,  0,        ADC8,  TIMER3_CH3_CCR}, // D27/PB0
    {GPIOB_BASE,  1,        ADC9,  TIMER3_CH4_CCR}, // D28/PB1
    {GPIOB_BASE, 10, ADC_INVALID,  TIMER_INVALID}, // D29/PB10
    {GPIOB_BASE, 11, ADC_INVALID,  TIMER_INVALID}, // D30/PB11
    {GPIOB_BASE, 12, ADC_INVALID,  TIMER_INVALID}, // D31/PB12
    {GPIOB_BASE, 13, ADC_INVALID,  TIMER_INVALID}, // D32/PB13
    {GPIOB_BASE, 14, ADC_INVALID,  TIMER_INVALID}, // D33/PB14
    {GPIOB_BASE, 15, ADC_INVALID,  TIMER_INVALID}, // D34/PB15
    {GPIOC_BASE,  6, ADC_INVALID,  TIMER_INVALID}, // D35/PC6
    {GPIOC_BASE,  7, ADC_INVALID,  TIMER_INVALID}, // D36/PC7
    {GPIOC_BASE,  8, ADC_INVALID,  TIMER_INVALID}, // D37/PC8
    {GPIOC_BASE,  9, ADC_INVALID,  TIMER_INVALID}  // D38/PC9
};

void pinMode(uint8 pin, WiringPinMode mode) {
    uint8 outputMode;

    if (pin >= NR_MAPLE_PINS)
        return;

    switch(mode) {
    case OUTPUT:
        outputMode = GPIO_MODE_OUTPUT_PP;
        break;
    case OUTPUT_OPEN_DRAIN:
        outputMode = GPIO_MODE_OUTPUT_OD;
        break;
    case INPUT:
    case INPUT_FLOATING:
        outputMode = GPIO_MODE_INPUT_FLOATING;
        break;
    case INPUT_ANALOG:
        outputMode = GPIO_MODE_INPUT_ANALOG;
        break;
    case INPUT_PULLUP:
        outputMode = GPIO_MODE_INPUT_PU;
        break;
    case INPUT_PULLDOWN:
        outputMode = GPIO_MODE_INPUT_PD;
        break;
    case PWM:
        outputMode = GPIO_MODE_AF_OUTPUT_PP;
        break;
    default:
        ASSERT(0);
        return;
    }

    gpio_set_mode(PIN_MAP[pin].port, PIN_MAP[pin].pin, outputMode);
}


uint32 digitalRead(uint8 pin) {
    if (pin >= NR_MAPLE_PINS)
        return 0;
    return gpio_read_bit(PIN_MAP[pin].port, PIN_MAP[pin].pin);
}

void digitalWrite(uint8 pin, uint8 val) {
    if (pin >= NR_MAPLE_PINS)
        return;

    gpio_write_bit(PIN_MAP[pin].port, PIN_MAP[pin].pin, val);
}
