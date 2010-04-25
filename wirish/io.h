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
 *  @file io.h
 *
 *  @brief 
 */

#ifndef _IO_H
#define _IO_H

#include "gpio.h"
#include "adc.h"

#ifdef __cplusplus
extern "C"{
#endif

/* stash these here for now  */
#define D0    0
#define D1    1
#define D2    2
#define D3    3
#define D4    4
#define D5    5
#define D6    6
#define D7    7
#define D8    8
#define D9    9
#define D10  10
#define D11  11
#define D12  12
#define D13  13
#define D14  14
#define D15  15
#define D16  16
#define D16  16
#define D17  17
#define D18  18
#define D19  19
#define D20  20
#define D21  21
#define D22  22
#define D23  23
#define D24  24
#define D25  25
#define D26  26
#define D27  27
#define D28  28
#define D29  29
#define D30  30
#define D31  31
#define D32  32
#define D33  33
#define D34  34
#define D35  35
#define D36  36
#define D37  37
#define D38  38
#define D39  39

typedef enum WiringPinMode {
    OUTPUT,
    OUTPUT_OPEN_DRAIN,
    INPUT,
    INPUT_ANALOG,
    INPUT_PULLUP,
    INPUT_PULLDOWN,
    INPUT_FLOATING,
    PWM
} WiringPinMode;

typedef struct PinMapping {
    GPIO_Port *port;
    uint32 pin;
    uint32 adc;
    TimerCCR timer_channel;
} PinMapping;

#define ADC_INVALID       0xFFFFFFFF
#define TIMER_INVALID     (TimerCCR)0xFFFFFFFF

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
 *     */
uint32 analogRead(uint8);

#ifdef __cplusplus
} // extern "C"
#endif
#endif

