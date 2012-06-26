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
 * @file   wirish/boards/st_stm3220g_eval/board.cpp
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  STM3220G-EVAL board file.
 */

#include <board/board.h>

#include <libmaple/gpio.h>
#include <libmaple/timer.h>
#include <wirish/wirish_types.h>

/* Board initialization. Unused. */
void boardInit(void) {
}

/* Pin map. Current restrictions:
 * - LEDs and user button only
 * - GPIO devices only (no timers etc. yet)
 */
#define pmap_row(dev, bit) {dev, NULL, NULL, bit, 0, ADCx}
extern const stm32_pin_info PIN_MAP[BOARD_NR_GPIO_PINS] = {
    pmap_row(GPIOG, 6),         /* D0/PG6 (LED1) */
    pmap_row(GPIOG, 8),         /* D1/PG8 (LED2) */
    pmap_row(GPIOI, 9),         /* D2/PI9 (LED3) */
    pmap_row(GPIOC, 7),         /* D4/PC7 (LED4) */
    pmap_row(GPIOG, 15),        /* D5/PG15 (BUT) */
};
#undef pmap_row

/* Special pin arrays. Unused. */
extern const uint8 boardPWMPins[] __FLASH__ = {};
extern const uint8 boardADCPins[] __FLASH__ = {};
extern const uint8 boardUsedPins[] __FLASH__ = {};
