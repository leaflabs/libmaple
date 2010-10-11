/******************************************************************************
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
 *****************************************************************************/

/**
 * @brief System timer interrupt handler and initialization routines
 */

#include "libmaple.h"
#include "systick.h"

#define SYSTICK_RELOAD          0xE000E014  // Reload value register
#define SYSTICK_CNT             0xE000E018  // Current value register
#define SYSTICK_CALIB           0xE000E01C  // Calibration value register

#define SYSTICK_SRC_HCLK        BIT(2)    // Use core clock
#define SYSTICK_TICKINT         BIT(1)    // Interrupt on systick countdown
#define SYSTICK_ENABLE          BIT(0)    // Turn on the counter

volatile uint32 systick_timer_millis = 0;

void systick_init(uint32 reload_val) {
    /* Set the reload counter to tick every 1ms  */
    __write(SYSTICK_RELOAD, reload_val);

    /* Clock the system timer with the core clock and turn it on,
     * interrrupt every 1ms to keep track of millis() */
    __write(SYSTICK_CSR, SYSTICK_SRC_HCLK |
            SYSTICK_ENABLE                |
            SYSTICK_TICKINT);
}

void systick_disable() {
    /* clock the system timer with the core clock, but don't turn it
       on or enable interrupt. */
    __write(SYSTICK_CSR, SYSTICK_SRC_HCLK);
}

void systick_resume() {
    /* re-enable init registers without changing relead_val */
    __write(SYSTICK_CSR, SYSTICK_SRC_HCLK |
            SYSTICK_ENABLE                |
            SYSTICK_TICKINT);
}

void SysTickHandler(void) {
    systick_timer_millis++;
}


