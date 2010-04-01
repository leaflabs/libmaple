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
 *  @file systick.h
 *
 *  @brief Various system timer definitions
 */

#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "libmaple.h"

/* To the ARM technical manual... there's nearly nothing on the systick
 * timer in the stm32 manual */

#define SYSTICK_CSR       0xE000E010  // Control and status register
#define SYSTICK_RELOAD    0xE000E014  // Reload value register
#define SYSTICK_CNT       0xE000E018  // Current value register
#define SYSTICK_CALIB     0xE000E01C  // Calibration value register

#define SYSTICK_SRC_HCLK  BIT(2)    // Use core clock
#define SYSTICK_TICKINT   BIT(1)    // Interrupt on systick countdown
#define SYSTICK_ENABLE    BIT(0)    // Turn on the counter

/* We use the systick timer to tick once
 * every millisecond */
#define MAPLE_RELOAD_VAL     72000

#ifdef __cplusplus
extern "C"{
#endif

void systick_init(void);

static inline uint32 systick_get_count(void) {
    return (uint32)*(volatile uint32*)SYSTICK_CNT;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif

