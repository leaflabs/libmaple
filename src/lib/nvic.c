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
 *  Created: 12/18/09 02:36:19
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file nvic.c
 *
 *  @brief Nested interrupt controller routines
 */

#include "libmaple.h"
#include "nvic.h"
#include "systick.h"

void nvic_disable_interrupts(void) {
    /* Turn off all interrupts  */
    REG_SET(NVIC_ICER0, 0xFFFFFFFF);
    REG_SET(NVIC_ICER1, 0xFFFFFFFF);

    /* Turn off systick exception  */
    REG_CLEAR_BIT(SYSTICK_CSR, 0);
}


void nvic_set_vector_table(uint32_t *addr, uint32_t offset) {
//    SCB->VTOR = NVIC_VectTab | (Offset & (u32)0x1FFFFF80);
}


/**
 *  @brief turn on interrupt number n
 *  @param[in] n interrupt number
 */
void nvic_enable_interrupt(uint32 n) {
    if (n >= NVIC_NR_INTERRUPTS) {
        return;
    }

    if (n < 32) {
        REG_SET_BIT(NVIC_ISER0, n);
    } else {
        REG_SET_BIT(NVIC_ISER1, n - 32);
    }
}
