#ifndef _SYSTICK_H_
#define _SYSTICK_H_
#include <inttypes.h>
#include "util.h"

/* To the ARM technical manual... there's nearly nothing on the systick
 * timer in the stm32 manual */

#define SYSTICK_CSR       *(volatile int*)0xE000E010  // Control and status register
#define SYSTICK_RELOAD    *(volatile int*)0xE000E014  // Reload value register
#define SYSTICK_CNT       *(volatile int*)0xE000E018  // Current value register
#define SYSTICK_CALIB     *(volatile int*)0xE000E01C  // Calibration value register

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
    return (uint32_t)SYSTICK_CNT;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif

