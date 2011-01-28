/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Bryan Newbold.
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
 *****************************************************************************/

/* This file contains board-specific pin mapping tables. To add a new board
 * type, copy the "BOARD_maple" section below and edit it as needed, then
 * update your build toolchain with a new "BOARD" type. This must match the
 * separate MCU type (which determines the ../libmaple configuration).
 */

#ifndef _BOARDS_H_
#define _BOARDS_H_

#include "libmaple.h"
#include "gpio.h"
#include "timers.h"
#include "exti.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Set of all possible digital pin names; not all boards have all these */
enum {
    D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14, D15, D16,
    D17, D18, D19, D20, D21, D22, D23, D24, D25, D26, D27, D28, D29, D30, D31,
    D32, D33, D34, D35, D36, D37, D38, D39, D40, D41, D42, D43, D44, D45, D46,
    D47, D48, D49, D50, D51, D52, D53, D54, D55, D56, D57, D58, D59, D60, D61,
    D62, D63, D64, D65, D66, D67, D68, D69, D70, D71, D72, D73, D74, D75, D76,
    D77, D78, D79, D80, D81, D82, D83, D84, D85, D86, D87, D88, D89, D90, D91,
    D92, D93, D94, D95, D96, D97, D98, D99, D100, D101, D102, D103, D104, D105,
    D106, D107, D108, D109, D110, D111, };

/* Set of all possible analog pin names; not all boards have all these */
enum {
    ADC0, ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7, ADC8, ADC9, ADC10, ADC11,
    ADC12, ADC13, ADC14, ADC15, ADC16, ADC17, ADC18, ADC19, ADC20, };

#define ADC_INVALID       0xFFFFFFFF

/* Types used for the tables below */
typedef struct PinMapping {
    GPIO_Port *port;
    uint32 pin;
    uint32 adc;
    TimerCCR timer_ccr;
    uint32 exti_port;
    timer_dev_num timer_num;
    uint32 timer_chan;
} PinMapping;

/* LeafLabs Maple rev3, rev5 */
#ifdef BOARD_maple

    #define CYCLES_PER_MICROSECOND  72
    #define SYSTICK_RELOAD_VAL      71999 /* takes a cycle to reload */

    #define BOARD_BUTTON_PIN   38
    #define BOARD_LED_PIN      13

    static __attribute__ ((unused)) PinMapping PIN_MAP[NR_GPIO_PINS] = {
        /* D0/PA3 */
        {GPIOA_BASE,  3,        ADC3, TIMER2_CH4_CCR,  EXTI_CONFIG_PORTA, TIMER2, 4},
        /* D1/PA2 */
        {GPIOA_BASE,  2,        ADC2, TIMER2_CH3_CCR,  EXTI_CONFIG_PORTA, TIMER2, 3},
        /* D2/PA0 */
        {GPIOA_BASE,  0,        ADC0, TIMER2_CH1_CCR,  EXTI_CONFIG_PORTA, TIMER2, 1},
        /* D3/PA1 */
        {GPIOA_BASE,  1,        ADC1, TIMER2_CH2_CCR,  EXTI_CONFIG_PORTA, TIMER2, 2},
        /* D4/PB5 */
        {GPIOB_BASE,  5, ADC_INVALID,              0,  EXTI_CONFIG_PORTB, TIMER_INVALID, TIMER_INVALID},
        /* D5/PB6 */
        {GPIOB_BASE,  6, ADC_INVALID, TIMER4_CH1_CCR,  EXTI_CONFIG_PORTB, TIMER4, 1},
        /* D6/PA8 */
        {GPIOA_BASE,  8, ADC_INVALID, TIMER1_CH1_CCR,  EXTI_CONFIG_PORTA, TIMER1, 1},
        /* D7/PA9 */
        {GPIOA_BASE,  9, ADC_INVALID, TIMER1_CH2_CCR,  EXTI_CONFIG_PORTA, TIMER1, 2},
        /* D8/PA10 */
        {GPIOA_BASE, 10, ADC_INVALID, TIMER1_CH3_CCR,  EXTI_CONFIG_PORTA, TIMER1, 3},
        /* D9/PB7 */
        {GPIOB_BASE,  7, ADC_INVALID, TIMER4_CH2_CCR,  EXTI_CONFIG_PORTB, TIMER4, 2},
        /* D10/PA4 */
        {GPIOA_BASE,  4,        ADC4,              0,  EXTI_CONFIG_PORTA, TIMER_INVALID, TIMER_INVALID},
        /* D11/PA7 */
        {GPIOA_BASE,  7,        ADC7, TIMER3_CH2_CCR,  EXTI_CONFIG_PORTA, TIMER3, 2},
        /* D12/PA6 */
        {GPIOA_BASE,  6,        ADC6, TIMER3_CH1_CCR,  EXTI_CONFIG_PORTA, TIMER3, 1},
        /* D13/PA5 */
        {GPIOA_BASE,  5,        ADC5,              0,  EXTI_CONFIG_PORTA, TIMER_INVALID, TIMER_INVALID},
        /* D14/PB8 */
        {GPIOB_BASE,  8, ADC_INVALID, TIMER4_CH3_CCR,  EXTI_CONFIG_PORTB, TIMER4, 3},

        /* Little header */

        /* D15/PC0 */
        {GPIOC_BASE,  0,       ADC10,              0,  EXTI_CONFIG_PORTC, TIMER_INVALID, TIMER_INVALID},
        /* D16/PC1 */
        {GPIOC_BASE,  1,       ADC11,              0,  EXTI_CONFIG_PORTC, TIMER_INVALID, TIMER_INVALID},
        /* D17/PC2 */
        {GPIOC_BASE,  2,       ADC12,              0,  EXTI_CONFIG_PORTC, TIMER_INVALID, TIMER_INVALID},
        /* D18/PC3 */
        {GPIOC_BASE,  3,       ADC13,              0,  EXTI_CONFIG_PORTC, TIMER_INVALID, TIMER_INVALID},
        /* D19/PC4 */
        {GPIOC_BASE,  4,       ADC14,              0,  EXTI_CONFIG_PORTC, TIMER_INVALID, TIMER_INVALID},
        /* D20/PC5 */
        {GPIOC_BASE,  5,       ADC15,              0,  EXTI_CONFIG_PORTC, TIMER_INVALID, TIMER_INVALID},

        /* External header */

        /* D21/PC13 */
        {GPIOC_BASE, 13, ADC_INVALID,              0,  EXTI_CONFIG_PORTC, TIMER_INVALID, TIMER_INVALID},
        /* D22/PC14 */
        {GPIOC_BASE, 14, ADC_INVALID,              0,  EXTI_CONFIG_PORTC, TIMER_INVALID, TIMER_INVALID},
        /* D23/PC15 */
        {GPIOC_BASE, 15, ADC_INVALID,              0,  EXTI_CONFIG_PORTC, TIMER_INVALID, TIMER_INVALID},
        /* D24/PB9 */
        {GPIOB_BASE,  9, ADC_INVALID, TIMER4_CH4_CCR,  EXTI_CONFIG_PORTB, TIMER_INVALID, TIMER_INVALID},
        /* D25/PD2 */
        {GPIOD_BASE,  2, ADC_INVALID,              0,  EXTI_CONFIG_PORTD, TIMER_INVALID, TIMER_INVALID},
        /* D26/PC10 */
        {GPIOC_BASE, 10, ADC_INVALID,              0,  EXTI_CONFIG_PORTC, TIMER_INVALID, TIMER_INVALID},
        /* D27/PB0 */
        {GPIOB_BASE,  0,        ADC8, TIMER3_CH3_CCR,  EXTI_CONFIG_PORTB, TIMER3, 3},
        /* D28/PB1 */
        {GPIOB_BASE,  1,        ADC9, TIMER3_CH4_CCR,  EXTI_CONFIG_PORTB, TIMER3, 4},
        /* D29/PB10 */
        {GPIOB_BASE, 10, ADC_INVALID,              0,  EXTI_CONFIG_PORTB, TIMER_INVALID, TIMER_INVALID},
        /* D30/PB11 */
        {GPIOB_BASE, 11, ADC_INVALID,              0,  EXTI_CONFIG_PORTB, TIMER_INVALID, TIMER_INVALID},
        /* D31/PB12 */
        {GPIOB_BASE, 12, ADC_INVALID,              0,  EXTI_CONFIG_PORTB, TIMER_INVALID, TIMER_INVALID},
        /* D32/PB13 */
        {GPIOB_BASE, 13, ADC_INVALID,              0,  EXTI_CONFIG_PORTB, TIMER_INVALID, TIMER_INVALID},
        /* D33/PB14 */
        {GPIOB_BASE, 14, ADC_INVALID,              0,  EXTI_CONFIG_PORTB, TIMER_INVALID, TIMER_INVALID},
        /* D34/PB15 */
        {GPIOB_BASE, 15, ADC_INVALID,              0,  EXTI_CONFIG_PORTB, TIMER_INVALID, TIMER_INVALID},
        /* D35/PC6 */
        {GPIOC_BASE,  6, ADC_INVALID,              0,  EXTI_CONFIG_PORTC, TIMER_INVALID, TIMER_INVALID},
        /* D36/PC7 */
        {GPIOC_BASE,  7, ADC_INVALID,              0,  EXTI_CONFIG_PORTC, TIMER_INVALID, TIMER_INVALID},
        /* D37/PC8 */
        {GPIOC_BASE,  8, ADC_INVALID,              0,  EXTI_CONFIG_PORTC, TIMER_INVALID, TIMER_INVALID},
        /* PC9 (BUT) */
        {GPIOC_BASE,  9, ADC_INVALID,              0,  EXTI_CONFIG_PORTC, TIMER_INVALID, TIMER_INVALID}
    };

    #define BOARD_INIT do {                           \
        } while(0)

#elif defined(BOARD_maple_native)

    /* LeafLabs Maple Native (prototype) */

    #define CYCLES_PER_MICROSECOND  72
    #define SYSTICK_RELOAD_VAL      71999 /* takes a cycle to reload */

    // TODO:
    static __attribute__ ((unused)) PinMapping PIN_MAP[NR_GPIO_PINS] = {
        /* D0/PA3 */
        {GPIOA_BASE,  3,        ADC3, TIMER2_CH4_CCR},
        /* D1/PA2 */
        {GPIOA_BASE,  2,        ADC2, TIMER2_CH3_CCR},
        /* D2/PA0 */
        {GPIOA_BASE,  0,        ADC0, TIMER2_CH1_CCR},
        /* D3/PA1 */
        {GPIOA_BASE,  1,        ADC1, TIMER2_CH2_CCR},
        /* D4/PB5 */
        {GPIOB_BASE,  5, ADC_INVALID,  TIMER_INVALID},
        /* D5/PB6 */
        {GPIOB_BASE,  6, ADC_INVALID, TIMER4_CH1_CCR},
        /* D6/PA8 */
        {GPIOA_BASE,  8, ADC_INVALID, TIMER1_CH1_CCR},
        /* D7/PA9 */
        {GPIOA_BASE,  9, ADC_INVALID, TIMER1_CH2_CCR},
        /* D8/PA10 */
        {GPIOA_BASE, 10, ADC_INVALID, TIMER1_CH3_CCR},
        /* D9/PB7 */
        {GPIOB_BASE,  7, ADC_INVALID, TIMER4_CH2_CCR},
        /* D10/PA4 */
        {GPIOA_BASE,  4,        ADC4,  TIMER_INVALID},
        /* D11/PA7 */
        {GPIOA_BASE,  7,        ADC7, TIMER3_CH2_CCR},
        /* D12/PA6 */
        {GPIOA_BASE,  6,        ADC6, TIMER3_CH1_CCR},
        /* D13/PA5 */
        {GPIOA_BASE,  5,        ADC5,  TIMER_INVALID},
        /* D14/PB8 */
        {GPIOB_BASE,  8, ADC_INVALID, TIMER4_CH3_CCR},

        /* Little header  */

        /* D15/PC0 */
        {GPIOC_BASE,  0,       ADC10,  TIMER_INVALID},
        /* D16/PC1 */
        {GPIOC_BASE,  1,       ADC11,  TIMER_INVALID},
        /* D17/PC2 */
        {GPIOC_BASE,  2,       ADC12,  TIMER_INVALID},
        /* D18/PC3 */
        {GPIOC_BASE,  3,       ADC13,  TIMER_INVALID},
        /* D19/PC4 */
        {GPIOC_BASE,  4,       ADC14,  TIMER_INVALID},
        /* D20/PC5 */
        {GPIOC_BASE,  5,       ADC15,  TIMER_INVALID},

        /* External header  */

        /* D21/PC13 */
        {GPIOC_BASE, 13, ADC_INVALID,  TIMER_INVALID},
        /* D22/PC14 */
        {GPIOC_BASE, 14, ADC_INVALID,  TIMER_INVALID},
        /* D23/PC15 */
        {GPIOC_BASE, 15, ADC_INVALID,  TIMER_INVALID},
        /* D24/PB9 */
        {GPIOB_BASE,  9, ADC_INVALID, TIMER4_CH4_CCR},
        /* D25/PD2 */
        {GPIOD_BASE,  2, ADC_INVALID,  TIMER_INVALID},
        /* D26/PC10 */
        {GPIOC_BASE, 10, ADC_INVALID,  TIMER_INVALID},
        /* D27/PB0 */
        {GPIOB_BASE,  0,        ADC8,  TIMER3_CH3_CCR},
        /* D28/PB1 */
        {GPIOB_BASE,  1,        ADC9,  TIMER3_CH4_CCR},
        /* D29/PB10 */
        {GPIOB_BASE, 10, ADC_INVALID,  TIMER_INVALID},
        /* D30/PB11 */
        {GPIOB_BASE, 11, ADC_INVALID,  TIMER_INVALID},
        /* D31/PB12 */
        {GPIOB_BASE, 12, ADC_INVALID,  TIMER_INVALID},
        /* D32/PB13 */
        {GPIOB_BASE, 13, ADC_INVALID,  TIMER_INVALID},
        /* D33/PB14 */
        {GPIOB_BASE, 14, ADC_INVALID,  TIMER_INVALID},
        /* D34/PB15 */
        {GPIOB_BASE, 15, ADC_INVALID,  TIMER_INVALID},
        /* D35/PC6 */
        {GPIOC_BASE,  6, ADC_INVALID,  TIMER_INVALID},
        /* D36/PC7 */
        {GPIOC_BASE,  7, ADC_INVALID,  TIMER_INVALID},
        /* D37/PC8 */
        {GPIOC_BASE,  8, ADC_INVALID,  TIMER_INVALID},
        /* PC9 (BUT) */
        {GPIOC_BASE,  9, ADC_INVALID,  TIMER_INVALID}
    };

    static __attribute__((unused)) ExtiInfo PIN_TO_EXTI_CHANNEL[NR_GPIO_PINS] =
    {
        /* D0/PA3 */
        {EXTI3,  EXTI_CONFIG_PORTA},
        /* D1/PA2 */
        {EXTI2,  EXTI_CONFIG_PORTA},
        /* D2/PA0 */
        {EXTI0,  EXTI_CONFIG_PORTA},
        /* D3/PA1 */
        {EXTI1,  EXTI_CONFIG_PORTA},
        /* D4/PB5 */
        {EXTI5,  EXTI_CONFIG_PORTB},
        /* D5/PB6 */
        {EXTI6,  EXTI_CONFIG_PORTB},
        /* D6/PA8 */
        {EXTI8,  EXTI_CONFIG_PORTA},
        /* D7/PA9 */
        {EXTI9,  EXTI_CONFIG_PORTA},
        /* D8/PA10 */
        {EXTI10, EXTI_CONFIG_PORTA},
        /* D9/PB7 */
        {EXTI7,  EXTI_CONFIG_PORTB},
        /* D10/PA4 */
        {EXTI4,  EXTI_CONFIG_PORTA},
        /* D11/PA7 */
        {EXTI7,  EXTI_CONFIG_PORTA},
        /* D12/PA6 */
        {EXTI6,  EXTI_CONFIG_PORTA},
        /* D13/PA5 */
        {EXTI5,  EXTI_CONFIG_PORTA},
    };

#elif defined(BOARD_maple_mini)

    #define CYCLES_PER_MICROSECOND 72
    #define SYSTICK_RELOAD_VAL     71999 /* takes a cycle to reload */

    #define BOARD_BUTTON_PIN 32
    #define BOARD_LED_PIN    33

    static __attribute__ ((unused)) PinMapping PIN_MAP[NR_GPIO_PINS] = {
        /* D0/PB11 */
        {GPIOB_BASE, 11,  ADC_INVALID,              0, EXTI_CONFIG_PORTB, TIMER_INVALID, TIMER_INVALID},
        /* D1/PB10 */
        {GPIOB_BASE, 10,  ADC_INVALID,              0, EXTI_CONFIG_PORTB, TIMER_INVALID, TIMER_INVALID},
        /* D2/PB2 */
        {GPIOB_BASE,  2,  ADC_INVALID,              0, EXTI_CONFIG_PORTB, TIMER_INVALID, TIMER_INVALID},
        /* D3/PB0 */
        {GPIOB_BASE,  0,  ADC8,        TIMER3_CH3_CCR, EXTI_CONFIG_PORTB, TIMER3,        3},
        /* D4/PA7 */
        {GPIOA_BASE,  7,  ADC7,        TIMER3_CH2_CCR, EXTI_CONFIG_PORTA, TIMER3,        2},
        /* D5/PA6 */
        {GPIOA_BASE,  6,  ADC6,        TIMER3_CH1_CCR, EXTI_CONFIG_PORTA, TIMER3,        1},
        /* D6/PA5 */
        {GPIOA_BASE,  5,  ADC5,                    0,  EXTI_CONFIG_PORTA, TIMER_INVALID, TIMER_INVALID},
        /* D7/PA4 */
        {GPIOA_BASE,  4,  ADC4,                    0,  EXTI_CONFIG_PORTA, TIMER_INVALID, TIMER_INVALID},
        /* D8/PA3 */
        {GPIOA_BASE,  3,  ADC3,        TIMER2_CH4_CCR, EXTI_CONFIG_PORTA, TIMER2,        4},
        /* D9/PA2 */
        {GPIOA_BASE,  2,  ADC2,        TIMER2_CH3_CCR, EXTI_CONFIG_PORTA, TIMER2,        3},
        /* D10/PA1 */
        {GPIOA_BASE,  1,  ADC1,        TIMER2_CH2_CCR, EXTI_CONFIG_PORTA, TIMER2,        2},
        /* D11/PA0 */
        {GPIOA_BASE,  0,  ADC0,        TIMER2_CH1_CCR, EXTI_CONFIG_PORTA, TIMER2,        1},
        /* D12/PC15 */
        {GPIOC_BASE, 15,  ADC_INVALID,              0, EXTI_CONFIG_PORTC, TIMER_INVALID, TIMER_INVALID},
        /* D13/PC14 */
        {GPIOC_BASE, 14,  ADC_INVALID,              0, EXTI_CONFIG_PORTC, TIMER_INVALID, TIMER_INVALID},
        /* D14/PC13 */
        {GPIOC_BASE, 13,  ADC_INVALID,              0, EXTI_CONFIG_PORTC, TIMER_INVALID, TIMER_INVALID},
        /* D15/PB7 */
        {GPIOB_BASE,  7,  ADC_INVALID, TIMER4_CH2_CCR, EXTI_CONFIG_PORTB, TIMER4,        1},
        /* D16/PB6 */
        {GPIOB_BASE,  6,  ADC_INVALID, TIMER4_CH1_CCR, EXTI_CONFIG_PORTB, TIMER4,        1},
        /* D17/PB5 */
        {GPIOB_BASE,  5,  ADC_INVALID,              0, EXTI_CONFIG_PORTB, TIMER_INVALID, TIMER_INVALID},
        /* D18/PB4 */
        {GPIOB_BASE,  4,  ADC_INVALID,              0, EXTI_CONFIG_PORTB, TIMER_INVALID, TIMER_INVALID},
        /* D19/PB3 */
        {GPIOB_BASE,  3,  ADC_INVALID,              0, EXTI_CONFIG_PORTB, TIMER_INVALID, TIMER_INVALID},
        /* D20/PA15 */
        {GPIOA_BASE, 15,  ADC_INVALID,              0, EXTI_CONFIG_PORTA, TIMER_INVALID, TIMER_INVALID},
        /* D21/PA14 */
        {GPIOA_BASE, 14,  ADC_INVALID,              0, EXTI_CONFIG_PORTA, TIMER_INVALID, TIMER_INVALID},
        /* D22/PA13 */
        {GPIOA_BASE, 13,  ADC_INVALID,              0, EXTI_CONFIG_PORTA, TIMER_INVALID, TIMER_INVALID},
        /* D23/PA12 */
        {GPIOA_BASE, 12,  ADC_INVALID,              0, EXTI_CONFIG_PORTA, TIMER_INVALID, TIMER_INVALID},
        /* D24/PA11 */
        {GPIOA_BASE, 11,  ADC_INVALID, TIMER1_CH4_CCR, EXTI_CONFIG_PORTA, TIMER1,        4},
        /* D25/PA10 */
        {GPIOA_BASE, 10,  ADC_INVALID, TIMER1_CH3_CCR, EXTI_CONFIG_PORTA, TIMER1,        3},
        /* D26/PA9 */
        {GPIOA_BASE,  9,  ADC_INVALID, TIMER1_CH2_CCR, EXTI_CONFIG_PORTA, TIMER2,        2},
        /* D27/PA8 */
        {GPIOA_BASE,  8,  ADC_INVALID, TIMER1_CH1_CCR, EXTI_CONFIG_PORTB, TIMER1,        1},
        /* D28/PB15 */
        {GPIOB_BASE, 15,  ADC_INVALID,              0, EXTI_CONFIG_PORTB, TIMER_INVALID, TIMER_INVALID},
        /* D29/PB14 */
        {GPIOB_BASE, 14,  ADC_INVALID,              0, EXTI_CONFIG_PORTB, TIMER_INVALID, TIMER_INVALID},
        /* D30/PB13 */
        {GPIOB_BASE, 13,  ADC_INVALID,              0, EXTI_CONFIG_PORTB, TIMER_INVALID, TIMER_INVALID},
        /* D31/PB12 */
        {GPIOB_BASE, 12,  ADC_INVALID,              0, EXTI_CONFIG_PORTB, TIMER_INVALID, TIMER_INVALID},
        /* D32/PB8 */
        {GPIOB_BASE,  8,  ADC_INVALID, TIMER4_CH3_CCR, EXTI_CONFIG_PORTB, TIMER4,        3},
        /* D33/PB1 */
        {GPIOB_BASE,  1,  ADC9,        TIMER3_CH4_CCR, EXTI_CONFIG_PORTB, TIMER3,        4},
    };

    /* since we want the Serial Wire/JTAG pins as GPIOs, disable both
       SW and JTAG debug support */
    /* don't use __clear_bits here! */
    #define BOARD_INIT                                                  \
        do {                                                            \
            *AFIO_MAPR = (*AFIO_MAPR | BIT(26)) & ~(BIT(25) | BIT(24)); \
        } while (0)

#else

#error "Board type has not been selected correctly."

#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif

