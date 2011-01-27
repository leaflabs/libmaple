/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 LeafLabs, LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

#include "libmaple.h"
#include "bkp.h"
#include "pwr.h"
#include "rcc.h"
#include "util.h"

/* Data register memory layout is not contiguous.  It's split up from
   1--NR_LOW_DRS, beginning at BKP_LOW_OFFSET, through
   (NR_LOW_DRS+1)--NR_DRS, beginning at BKP_HIGH_OFFSET. */
#define NR_LOW_DRS 10
#define BKP_LOW_OFFSET  0x4    /* start offset for data registers 1--10 */
#define BKP_HIGH_OFFSET 0x40   /* start offset for data registers 11--42 */

inline volatile uint16* reg_addr(uint8 reg) {
    if (1 <= reg) {
        if (reg <= NR_LOW_DRS) {
            return (volatile uint16*)(BKP_BASE + BKP_LOW_OFFSET +
                                      (reg - 1) * 4);
        } else if (reg <= NR_BKP_REGS) {
            return (volatile uint16*)(BKP_BASE + BKP_HIGH_OFFSET +
                                      (reg - NR_LOW_DRS - 1) * 4);
        }
    }
    return 0;
}

void bkp_init(void) {
    /* Set PWREN (28) and BKPEN (27) bits */
    __set_bits(RCC_APB1ENR, BIT(28) | BIT(27));
}

void bkp_disable(void) {
    __clear_bits(RCC_APB1ENR, BIT(28) | BIT(27));
}

void bkp_enable_writes(void) {
    /* Set the DBP bit in PWR_CR */
    __write(BITBAND_PERI(PWR_CR, PWR_CR_DBP), 1);
}

void bkp_disable_writes(void) {
    __write(BITBAND_PERI(PWR_CR, PWR_CR_DBP), 0);
}

uint16 bkp_read(uint8 reg) {
    volatile uint16* addr = reg_addr(reg);
    if (addr != 0) {
        return *addr;
    }
    ASSERT(0);                  /* nonexistent register */
    return 0;
}

void bkp_write(uint8 reg, uint16 val) {
    volatile uint16* addr = reg_addr(reg);
    if (addr != 0) {
        *addr = val;
    }
    ASSERT(0);                  /* nonexistent register */
}
