/* *****************************************************************************
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Created: 12/18/09 02:40:56
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file io.h
 *
 *  @brief 
 */

#ifndef _IO_H
#define _IO_H

#include <inttypes.h>
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
void pinMode(uint8_t, uint8_t);

/*
 * Writes VALUE to digital pin[0-38]
 * digitalWrite(pin, value):
 *     pin -> {0-38, D0-D39, A0-16}
 *     value -> LOW, HIGH;
*/
void digitalWrite(uint8_t, uint8_t);

/* Read a digital value from pin, the pin mode must be set to
 * {INPUT, INPUT_PULLUP, INPUT_PULLDOWN}
 * digitalRead(pin)
 *     pin -> {0-38, D0-D39, A0-16}
 */
uint32_t digitalRead(uint8_t);

/* Read an analog value from pin, the pin mode must be set
 * to INPUT_ANALOG
 * analogRead(pin)
 *     pin -> {A0-A16}
 *     */
uint32_t analogRead(uint8_t);

#ifdef __cplusplus
} // extern "C"
#endif
#endif

