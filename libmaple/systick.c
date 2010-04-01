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
 *  @file systick.c
 *
 *  @brief System timer interrupt handler and initialization routines
 */

#include "libmaple.h"
#include "systick.h"

#define MILLIS_INC 1

volatile uint32 systick_timer_millis = 0;

void systick_init(void) {
    /* Set the reload counter to tick every 1ms  */
    REG_SET_MASK(SYSTICK_RELOAD, MAPLE_RELOAD_VAL);
//    SYSTICK_RELOAD = MAPLE_RELOAD_VAL;

    /* Clock the system timer with the core clock
     * and turn it on, interrrupt every 1ms to keep track of millis()*/
    REG_SET(SYSTICK_CSR, SYSTICK_SRC_HCLK |
                         SYSTICK_ENABLE   |
                         SYSTICK_TICKINT);
//    SYSTICK_CSR = SYSTICK_SRC_HCLK |
//                  SYSTICK_ENABLE   |
//                  SYSTICK_TICKINT;
}

void SysTickHandler(void) {
    systick_timer_millis++;
}


