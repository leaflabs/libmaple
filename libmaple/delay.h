/**
 *  @brief 
 */

#ifndef _DELAY_H_
#define _DELAY_H_

static inline void delay_us(uint32 us) {
    /* So (2^32)/12 micros max, or less than 6 minutes */
    us *= 12;

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

