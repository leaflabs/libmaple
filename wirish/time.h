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
 *  @file time.h
 *
 *  @brief 
 */

#ifndef _TIME_H
#define _TIME_H

#ifdef __cplusplus
extern "C"{
#endif
/* Returns time since boot in milliseconds  */
uint32 millis(void);

/* Time in microseconds since boot  */
uint32 micros(void);

/* Delay for ms milliseconds  */
void delay(unsigned long ms);

/* Delay for us microseconds  */
void delayMicroseconds(uint32 us);

#if 0
static inline void delay_us(uint32 us) {
    us *= 12;
    asm volatile("mov  r0, %[us]        \n\t"
                 "subs r0, #2 \n\t"
"1:                                    \n\t"
                  "subs r0, r0, #1           \n\t"
                  "bne 1b"
                 :
                 : [us] "r" (us)
                 : "r0", "cc");

}
#endif
#ifdef __cplusplus
} // extern "C"
#endif


#endif

