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
 *  Created: 12/18/09 02:39:27
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file util.h
 *
 *  @brief Various macros and utility procedures.
 */

/* Generally "useful" utility procedures  */
#ifndef _UTIL_H_
#define _UTIL_H_
#include <inttypes.h>

#define MAPLE_DEBUG 1

#define BIT(shift)                     (1 << (shift))
#define BIT_MASK_SHIFT(mask, shift)    ((mask) << (shift))

/* Return bits m to n of x  */
#define GET_BITS(x, m, n) ((((uint32_t)x) << (31 - (n))) >> ((31 - (n)) + (m)))

/* Bit-banding macros  */
#define BITBAND_SRAM_REF   0x20000000
#define BITBAND_SRAM_BASE  0x22000000
#define BITBAND_SRAM(a,b) ((BITBAND_SRAM_BASE + (a-BITBAND_SRAM_REF)*32 + (b*4)))  // Convert SRAM address
#define BITBAND_PERI_REF   0x40000000
#define BITBAND_PERI_BASE  0x42000000
#define BITBAND_PERI(a,b) ((BITBAND_PERI_BASE + (a-BITBAND_PERI_REF)*32 + (b*4)))  // Convert PERI address

#define COUNTFLAG *((volatile unsigned char*) (BITBAND_PERI(SYSTICK_CSR,2)))

#define REG_SET(reg, val)               (*(volatile uint32_t*)(reg)  = (val))
#define REG_SET_BIT(reg, bit)           (*(volatile uint32_t*)(reg) |= BIT(bit))
#define REG_CLEAR_BIT(reg, bit)         (*(volatile uint32_t*)(reg) &= ~BIT(bit))
#define REG_SET_MASK(reg, mask)         (*(volatile uint32_t*)(reg) |= (uint32_t)(mask))
#define REG_CLEAR_MASK(reg, mask)       (*(volatile uint32_t*)(reg) &= (uint32_t)~(mask))

#define REG_GET(reg)                    *(volatile uint32_t*)(reg)


#ifdef __cplusplus
extern "C"{
#endif

void _fail(const char*, int, const char*);

#ifdef __cplusplus
} // extern "C"
#endif


/* Assert for sanity checks, undefine MAPLE_DEBUG to compile
 * out these checks */
#if MAPLE_DEBUG
#define ASSERT(exp)         \
    if (exp)              \
        {}                  \
    else                    \
        _fail(__FILE__, __LINE__, #exp)
#else
#define ASSERT(exp) (void)((0))
#endif

#endif

