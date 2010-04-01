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
 *  Created: 12/18/09 02:41:55
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file wiring_analog.c
 *
 *  @brief 
 */

#include "libmaple.h"
#include "wiring.h"
#include "io.h"

extern const PinMapping PIN_MAP[NR_MAPLE_PINS];

/* Assumes that the ADC has been initialized and
 * that the pin is set to ANALOG_INPUT */
uint32 analogRead(uint8 pin) {
    if (pin >= NR_ANALOG_PINS)
        return 0;

    return adc_read(PIN_MAP[pin].adc);
}
