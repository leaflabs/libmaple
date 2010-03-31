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
 *  Created: 12/18/09 02:37:37
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file systick.h
 *
 *  @brief Various system timer definitions
 */

#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "libmaple.h"

/* To the ARM technical manual... there's nearly nothing on the systick
 * timer in the stm32 manual */

#define SYSTICK_CSR       0xE000E010  // Control and status register
#define SYSTICK_RELOAD    0xE000E014  // Reload value register
#define SYSTICK_CNT       0xE000E018  // Current value register
#define SYSTICK_CALIB     0xE000E01C  // Calibration value register

#define SYSTICK_SRC_HCLK  BIT(2)    // Use core clock
#define SYSTICK_TICKINT   BIT(1)    // Interrupt on systick countdown
#define SYSTICK_ENABLE    BIT(0)    // Turn on the counter

/* We use the systick timer to tick once
 * every millisecond */
#define MAPLE_RELOAD_VAL     72000

#ifdef __cplusplus
extern "C"{
#endif

void systick_init(void);

static inline uint32_t systick_get_count(void) {
    return (uint32_t)*(volatile uint32*)SYSTICK_CNT;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif

