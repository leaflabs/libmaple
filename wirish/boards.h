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
#include "timer.h"
#include "native_sram.h"

/* Set of all possible pin names; not all boards have all these (note
   that we use the Dx convention since all of the Maple's pins are
   "digital" pins (e.g. can be used with digitalRead() and
   digitalWrite()), but not all of them are connected to ADCs. */
enum {
    D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14, D15, D16,
    D17, D18, D19, D20, D21, D22, D23, D24, D25, D26, D27, D28, D29, D30, D31,
    D32, D33, D34, D35, D36, D37, D38, D39, D40, D41, D42, D43, D44, D45, D46,
    D47, D48, D49, D50, D51, D52, D53, D54, D55, D56, D57, D58, D59, D60, D61,
    D62, D63, D64, D65, D66, D67, D68, D69, D70, D71, D72, D73, D74, D75, D76,
    D77, D78, D79, D80, D81, D82, D83, D84, D85, D86, D87, D88, D89, D90, D91,
    D92, D93, D94, D95, D96, D97, D98, D99, D100, D101, D102, D103, D104, D105,
    D106, D107, D108, D109, D110, D111, };

#define ADC_INVALID       0xFFFFFFFF

/* Pin mapping: pin number -> STM32 info */
typedef struct PinMapping {
    gpio_dev *gpio_device;
    uint32 pin;
    uint32 adc_channel;
    timer_dev* timer_device;
    uint8 timer_chan;
    afio_exti_port ext_port;
} PinMapping;

/* Maps every digital pin to a PinMapping */
extern PinMapping PIN_MAP[];

/* LeafLabs Maple rev3, rev5 */
#ifdef BOARD_maple

    #define CYCLES_PER_MICROSECOND  72
    #define SYSTICK_RELOAD_VAL      71999 /* takes a cycle to reload */

    #define BOARD_BUTTON_PIN        38
    #define BOARD_LED_PIN           13

    /* Total number of GPIO pins that are broken out to headers and
       intended for general use. */
    #define NR_GPIO_PINS            39

    #define BOARD_INIT do {                           \
        } while(0)

#elif defined(BOARD_maple_native)

    /* LeafLabs Maple Native (prototype) */

    #define CYCLES_PER_MICROSECOND  72
    #define SYSTICK_RELOAD_VAL      71999 /* takes a cycle to reload */

    #define BOARD_LED_PIN           D21
    #define BOARD_BUTTON_PIN        D18

    #define NR_GPIO_PINS            100

    #define BOARD_INIT do {                           \
           initNativeSRAM();
        } while(0)

#elif defined(BOARD_maple_mini)

    #define CYCLES_PER_MICROSECOND    72
    #define SYSTICK_RELOAD_VAL     71999 /* takes a cycle to reload */

    #define BOARD_BUTTON_PIN          32
    #define BOARD_LED_PIN             33

    #define NR_GPIO_PINS              34

    /* Since we want the Serial Wire/JTAG pins as GPIOs, disable both
     * SW and JTAG debug support */
    #define BOARD_INIT                                                  \
        do {                                                            \
            afio_mapr_swj_config(AFIO_MAPR_SWJ_NO_JTAG_NO_SW);          \
        } while (0)

#elif defined(BOARD_maple_RET6)

    #define CYCLES_PER_MICROSECOND  72
    #define SYSTICK_RELOAD_VAL      71999 /* takes a cycle to reload */

    #define BOARD_BUTTON_PIN        38
    #define BOARD_LED_PIN           13

    /* Total number of GPIO pins that are broken out to headers and
       intended for general use. */
    #define NR_GPIO_PINS            39

    #define BOARD_INIT do {                           \
        } while(0)

#else

#error "Board type has not been selected correctly."

#endif

#endif
