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
 *  Created: 12/18/09 02:41:24
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file pwm.c
 *
 *  @brief 
 */

#include "wiring.h"
#include "timers.h"
#include "io.h"
#include "pwm.h"

extern const PinMapping PIN_MAP[NR_MAPLE_PINS];

void pwmWrite(uint8_t pin, uint16_t duty_cycle) {
    TimerCCR ccr;

    if (pin >= NR_MAPLE_PINS) {
        return;
    }

    ccr = PIN_MAP[pin].timer_channel;

    if (ccr == TIMER_INVALID)
        return;

    timer_pwm_write_ccr(ccr, duty_cycle);
}


