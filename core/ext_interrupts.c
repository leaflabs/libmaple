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
 *  Created: 12/18/09 02:39:48
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file ext_interrupts.c
 *
 *  @brief Wiring-like interface for external interrupts
 */

#include "wiring.h"
#include "exti.h"
#include "ext_interrupts.h"

typedef struct ExtiInfo {
    uint8_t channel;
    uint8_t port;
} ExtiInfo;

static ExtiInfo PIN_TO_EXTI_CHANNEL[NR_MAPLE_PINS] = {
    {EXTI3,  EXTI_CONFIG_PORTA},      // D0/PA3
    {EXTI2,  EXTI_CONFIG_PORTA},      // D1/PA2
    {EXTI0,  EXTI_CONFIG_PORTA},      // D2/PA0
    {EXTI1,  EXTI_CONFIG_PORTA},      // D3/PA1
    {EXTI5,  EXTI_CONFIG_PORTB},      // D4/PB5
    {EXTI6,  EXTI_CONFIG_PORTB},      // D5/PB6
    {EXTI8,  EXTI_CONFIG_PORTA},      // D6/PA8
    {EXTI9,  EXTI_CONFIG_PORTA},      // D7/PA9
    {EXTI10, EXTI_CONFIG_PORTA},      // D8/PA10
    {EXTI7,  EXTI_CONFIG_PORTB},      // D9/PB7
    {EXTI4,  EXTI_CONFIG_PORTA},      // D10/PA4
    {EXTI7,  EXTI_CONFIG_PORTA},      // D11/PA7
    {EXTI6,  EXTI_CONFIG_PORTA},      // D12/PA6
    {EXTI5,  EXTI_CONFIG_PORTA},      // D13/PA5
};


/**
 *  @brief Attach an interrupt handler to be triggered on a given
 *  transition on the pin. Runs in interrupt context
 *
 *  @param[in] pin Maple pin number
 *  @param[in] handler Function to run upon external interrupt trigger.
 *  @param[in] mode Type of transition to trigger on, eg falling, rising, etc.
 *
 *  @sideeffect Registers a handler
 */
int attachInterrupt(uint8_t pin, voidFuncPtr handler, ExtInterruptTriggerMode mode) {
    uint8_t outMode;
    /* Parameter checking  */
    if (pin >= NR_MAPLE_PINS) {
        return EXT_INTERRUPT_INVALID_PIN;
    }

    if (!handler) {
        ASSERT(0);
        return EXT_INTERRUPT_INVALID_FUNCTION;
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
        ASSERT(0);
        return EXT_INTERRUPT_INVALID_MODE;;
    }

    exti_attach_interrupt(PIN_TO_EXTI_CHANNEL[pin].channel,
                          PIN_TO_EXTI_CHANNEL[pin].port,
                          handler, mode);

    return 0;
}

int detachInterrupt(uint8_t pin) {
    if (!(pin < NR_MAPLE_PINS)) {
        return EXT_INTERRUPT_INVALID_PIN;
    }

    exti_detach_interrupt(PIN_TO_EXTI_CHANNEL[pin].channel);
}

