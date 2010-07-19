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


void nvic_set_vector_table(uint32 addr, uint32 offset) {
   __write(SCB_VTOR, (uint32)addr | (offset & 0x1FFFFF80));
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

/**
 *  @brief turn off interrupt number n
 *  @param[in] n interrupt number
 */
void nvic_disable_interrupt(uint32 n) {
    if (n >= NVIC_NR_INTERRUPTS) {
        return;
    }

    if (n < 32) {
        REG_SET_BIT(NVIC_ICER0, n);
    } else {
        REG_SET_BIT(NVIC_ICER1, n - 32);
    }
}



/**
 * @brief Initialice the NVIC at address addr
 * @param addr Address to set the vector table at
 */
void nvic_init(void) {
#ifdef VECT_TAB_FLASH
   nvic_set_vector_table(USER_ADDR_ROM, 0x0);
#elif defined VECT_TAB_RAM
   nvic_set_vector_table(USER_ADDR_RAM, 0x0);
#elif defined VECT_TAB_BASE
   nvic_set_vector_table(((uint32)0x08000000), 0x0);
#else
#error "You must set a base address for the vector table!"
#endif
}
