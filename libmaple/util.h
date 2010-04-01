/* *****************************************************************************
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
 * ****************************************************************************/

/**
 *  @file util.h
 *
 *  @brief Various macros and utility procedures.
 */

/* Generally "useful" utility procedures  */
#ifndef _UTIL_H_
#define _UTIL_H_

#define MAPLE_DEBUG 1

#define BIT(shift)                     (1 << (shift))
#define BIT_MASK_SHIFT(mask, shift)    ((mask) << (shift))

/* Return bits m to n of x  */
#define GET_BITS(x, m, n) ((((uint32)x) << (31 - (n))) >> ((31 - (n)) + (m)))

/* Bit-banding macros  */
#define BITBAND_SRAM_REF   0x20000000
#define BITBAND_SRAM_BASE  0x22000000
#define BITBAND_SRAM(a,b) ((BITBAND_SRAM_BASE + (a-BITBAND_SRAM_REF)*32 + (b*4)))  // Convert SRAM address
#define BITBAND_PERI_REF   0x40000000
#define BITBAND_PERI_BASE  0x42000000
#define BITBAND_PERI(a,b) ((BITBAND_PERI_BASE + (a-BITBAND_PERI_REF)*32 + (b*4)))  // Convert PERI address

#define COUNTFLAG *((volatile unsigned char*) (BITBAND_PERI(SYSTICK_CSR,2)))

#define REG_SET(reg, val)               (*(volatile uint32*)(reg)  = (val))
#define REG_SET_BIT(reg, bit)           (*(volatile uint32*)(reg) |= BIT(bit))
#define REG_CLEAR_BIT(reg, bit)         (*(volatile uint32*)(reg) &= ~BIT(bit))
#define REG_SET_MASK(reg, mask)         (*(volatile uint32*)(reg) |= (uint32)(mask))
#define REG_CLEAR_MASK(reg, mask)       (*(volatile uint32*)(reg) &= (uint32)~(mask))

#define REG_GET(reg)                    *(volatile uint32*)(reg)

#define __set_bits(addr, mask)          *(volatile uint32*)(addr) |= (uint32)(mask)
#define __clear_bits(addr, mask)        (*(volatile uint32*)(addr) &= (uint32)~(mask))
#define __get_bits(addr, mask)          (*(volatile uint32*)(addr) & (uint32)(mask))

#define __read(reg)                     *(volatile uint32*)(reg)
#define __write(reg, value)             *(volatile uint32*)(reg) = (value)

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

