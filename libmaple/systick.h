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
 * @file systick.h
 *
 * @brief Various system timer definitions
 */

#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "libmaple.h"

#define SYSTICK_CSR             0xE000E010  // Control and status register
#define SYSTICK_CNT             0xE000E018  // Current value register

#define SYSTICK_CSR_COUNTFLAG   BIT(16)

#ifdef __cplusplus
extern "C"{
#endif

void systick_init(uint32 reload_val);
void systick_disable();
void systick_resume();

static inline uint32 systick_get_count(void) {
    return __read(SYSTICK_CNT);
}

static inline uint32 systick_check_underflow(void) {
    return (__read(SYSTICK_CSR) & SYSTICK_CSR_COUNTFLAG);
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif

