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
 *  Created: 12/18/09 02:37:24
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file systick.c
 *
 *  @brief System timer interrupt handler and initialization routines
 */

#include "libmaple.h"
#include "systick.h"

#define MILLIS_INC 1

volatile uint32_t systick_timer_millis = 0;

void systick_init(void) {
    /* Set the reload counter to tick every 1ms  */
    REG_SET_MASK(SYSTICK_RELOAD, MAPLE_RELOAD_VAL);
//    SYSTICK_RELOAD = MAPLE_RELOAD_VAL;

    /* Clock the system timer with the core clock
     * and turn it on, interrrupt every 1ms to keep track of millis()*/
    REG_SET(SYSTICK_CSR, SYSTICK_SRC_HCLK |
                         SYSTICK_ENABLE   |
                         SYSTICK_TICKINT);
//    SYSTICK_CSR = SYSTICK_SRC_HCLK |
//                  SYSTICK_ENABLE   |
//                  SYSTICK_TICKINT;
}

void SysTickHandler(void) {
    systick_timer_millis++;
}


