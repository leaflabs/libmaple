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
 *  @file ext_interrupts.c
 *
 *  @brief Wiring-like interface for external interrupts
 */

#include "wirish.h"
#include "exti.h"
#include "ext_interrupts.h"

/**
 *  @brief Attach an interrupt handler to be triggered on a given
 *  transition on the pin. Runs in interrupt context
 *
 *  @param pin Maple pin number
 *  @param handler Function to run upon external interrupt trigger.
 *  @param mode Type of transition to trigger on, eg falling, rising, etc.
 *
 *  @sideeffect Registers a handler
 */
void attachInterrupt(uint8 pin, voidFuncPtr handler, uint32 mode) {
    uint8 outMode;

    /* Parameter checking */
    if (pin >= NR_GPIO_PINS) {
        return;
    }

    if (!handler) {
        return;
    }

    switch (mode) {
    case RISING:
        outMode = EXTI_RISING;
        break;
    case FALLING:
        outMode = EXTI_FALLING;
        break;
    case CHANGE:
        outMode = EXTI_RISING_FALLING;
        break;
    default:
        return;
    }

    exti_attach_interrupt(PIN_MAP[pin].exti_port,
                          PIN_MAP[pin].pin,
                          handler,
                          mode);

    return;
}

/**
 * @brief Disable an external interrupt
 * @param pin maple pin number
 * @sideeffect unregisters external interrupt handler
 */
void detachInterrupt(uint8 pin) {
    if (!(pin < NR_GPIO_PINS)) {
        return;
    }

    exti_detach_interrupt(PIN_MAP[pin].pin);
}

