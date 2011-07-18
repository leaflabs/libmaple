/**
 * @file delay.h
 * @brief Delay implementation
 */

#include "libmaple_types.h"
#include "stm32.h"

#ifndef _DELAY_H_
#define _DELAY_H_

/**
 * @brief Delay the given number of microseconds.
 *
 * @param us Number of microseconds to delay.
 */
static inline void delay_us(uint32 us) {
    us *= DELAY_US_MULT;

    /* fudge for function call overhead  */
    us--;
    asm volatile("   mov r0, %[us]          \n\t"
                 "1: subs r0, #1            \n\t"
                 "   bhi 1b                 \n\t"
                 :
                 : [us] "r" (us)
                 : "r0");
}
#endif

