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

/**
 * Specifies a GPIO pin behavior.
 *
 * Each of the GPIO pins on a Maple board may be configured using
 * pinMode() to behave in a number of ways: as a digital output pin,
 * or as an analog input pin, etc., depending on the particular pin.
 *
 * This enum specifies the complete set of possible configurations;
 * not every pin can have all of these modes.  For example, on the
 * Maple, pin 15 may be configured as INPUT_ANALOG, but not as PWM.
 * See your device's silkscreen and and the GPIO documentation for
 * more information.
 *
 * @see pinMode()
 */
typedef enum WiringPinMode {
    OUTPUT, /**< Basic digital output: when the pin is HIGH, the
               voltage is held at +3.3v (Vcc) and when it is LOW, it
               is pulled down to ground. */

    OUTPUT_OPEN_DRAIN, /**< In open drain mode, the pin indicates
                          "low" by accepting current flow to ground
                          and "high" by providing increased
                          impedance. An example use would be to
                          connect a pin to a bus line (which is pulled
                          up to a positive voltage by a separate
                          supply through a large resistor). When the
                          pin is high, not much current flows through
                          to ground and the line stays at positive
                          voltage; when the pin is low the bus
                          "drains" to ground with a small amount of
                          current constantly flowing through the large
                          resistor from the external supply. In this
                          mode no current is ever actually /sourced/
                          from the pin. */

    INPUT, /**< Basic digital input. The pin voltage is sampled; when
              it is closer to 3.3v (Vcc) the pin status is high, and
              when it is closer to 0v (ground) it is low. If no
              external circuit is pulling the pin voltage to high or
              low, it will tend to randomly oscillate and be very
              sensitive to noise (eg a breath of air across the pin
              will cause the state to flip). */

    INPUT_ANALOG, /**< This is a special mode for when the pin will be
                     used for analog (not digital) reads.  Enables ADC
                     conversion to be performed on the voltage at the
                     pin. */

    INPUT_PULLUP, /**< The state of the pin in this mode is reported
                     the same way as with INPUT, but the pin voltage
                     is gently "pulled up" towards +3.3v. This means
                     the state will be high unless an external device
                     is specifically pulling the pin down to ground,
                     in which case the "gentle" pull up will not
                     affect the state of the input. */

    INPUT_PULLDOWN, /**< The state of the pin in this mode is reported
                       the same way as with INPUT, but the pin voltage
                       is gently "pulled down" towards 0v. This means
                       the state will be low unless an external device
                       is specifically pulling the pin up to 3.3v, in
                       which case the "gentle" pull down will not
                       effect the state of the input. */

    INPUT_FLOATING, /**< Synonym for INPUT. */

    PWM, /**< This is a special mode for when the pin will be used for
            PWM output (a special case of digital output). */

    PWM_OPEN_DRAIN, /**< Like PWM, except that instead of alternating
                       cycles of LOW and HIGH, the voltage on the pin
                       consists of alternating cycles of LOW and
                       floating (disconnected). */
} WiringPinMode;

/**
 * Configure behavior of a GPIO pin.
 *
 * @param pin Pin to configure. One of: 0-38 (pin numbers as labeled
 *            on silkscreen), or D0-D38 (symbols for same)
 * @param mode Mode corresponding to desired pin behavior.
 * @see WiringPinMode
 */
void pinMode(uint8 pin, WiringPinMode mode);

/**
 * Writes a (digital) value to a pin.  The pin must have its
 * mode set to <code>OUTPUT</code> or <code>OUTPUT_OPEN_DRAIN</code>.
 *
 * @param pin Pin to write to. One of: 0-38 (pin numbers as labeled
 *            on silkscreen), or D0-D38 (symbols for same)
 * @param value Either LOW (write a 0) or HIGH (write a 1).
 * @see pinMode()
 */
void digitalWrite(uint8 pin, uint8 value);

/**
 * Read a digital value from a pin.  The pin must have its mode set to
 * one of INPUT, INPUT_PULLUP, and INPUT_PULLDOWN.
 *
 * @param pin Pin to read from. One of: 0-38 (pin numbers as labeled
 *            on silkscreen), or D0-D38 (symbols for same)
 * @return LOW or HIGH.
 * @see pinMode()
 */
uint32 digitalRead(uint8);

/**
 * Read an analog value from pin.  This function blocks during ADC
 * conversion.  The pin must have its mode set to INPUT_ANALOG.
 *
 * @param pin Pin to read from. One of: 0-38 (pin numbers as labeled
 *            on silkscreen), or D0-D38 (symbols for same)
 * @return ADC-converted voltage, in the range 0--4095, inclusive.
 * @see pinMode()
 * @see analogReference()
 */
uint32 analogRead(uint8 pin);

#ifdef __cplusplus
} // extern "C"
#endif
#endif

