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
 *  @file io.h
 *
 *  @brief Arduino-compatible digital pin I/O interface.
 */

#ifndef _IO_H
#define _IO_H

#include "gpio.h"
#include "adc.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum WiringPinMode {
    OUTPUT,
    OUTPUT_OPEN_DRAIN,
    INPUT,
    INPUT_ANALOG,
    INPUT_PULLUP,
    INPUT_PULLDOWN,
    INPUT_FLOATING,
    PWM,
    PWM_OPEN_DRAIN,
} WiringPinMode;


/* Set pin to mode
 * pinMode(pin, mode):
 *     pin -> {0-38, D0-D39, A0-16}
 *     mode -> {
 *         INPUT/INPUT_DIGITAL
 *         INPUT_PULLUP
 *         INPUT_PULLDOWN
 *         INPUT_ANALOG
 *         OUTPUT/OUTPUT_PP
 *         OUTPUT_OPEN_DRAIN
 *     }
 */
void pinMode(uint8, uint8);

/*
 * Writes VALUE to digital pin[0-38]
 * digitalWrite(pin, value):
 *     pin -> {0-38, D0-D39, A0-16}
 *     value -> LOW, HIGH;
*/
void digitalWrite(uint8, uint8);

/* Read a digital value from pin, the pin mode must be set to
 * {INPUT, INPUT_PULLUP, INPUT_PULLDOWN}
 * digitalRead(pin)
 *     pin -> {0-38, D0-D39, A0-16}
 */
uint32 digitalRead(uint8);

/* Read an analog value from pin, the pin mode must be set
 * to INPUT_ANALOG
 * analogRead(pin)
 *     pin -> {A0-A16}
 */
uint32 analogRead(uint8);

#ifdef __cplusplus
} // extern "C"
#endif
#endif

