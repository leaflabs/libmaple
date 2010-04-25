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
 *  @file ext_interrupts.h
 *
 *  @brief External interrupt wiring prototypes and types
 */

#ifndef _EXT_INTERRUPTS_H_
#define _EXT_INTERRUPTS_H_

typedef enum ExtInterruptTriggerMode {
    RISING,
    FALLING,
    CHANGE
} ExtInterruptTriggerMode;


enum ExtInterruptError {
    EXT_INTERRUPT_INVALID_PIN =      (-1),
    EXT_INTERRUPT_INVALID_FUNCTION = (-2),
    EXT_INTERRUPT_INVALID_MODE =     (-3),
};

#ifdef __cplusplus
extern "C"{
#endif

int attachInterrupt(uint8 pin, voidFuncPtr, ExtInterruptTriggerMode mode);
int detachInterrupt(uint8 pin);

#ifdef __cplusplus
}
#endif


#endif

