/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011, 2012 LeafLabs, LLC.
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

/**
 * @file   libmaple/stm32f1/timer.c
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  STM32F1 timer support.
 */

/* Notes:
 *
 * - We use STM32F1 density test macros throughout to avoid defining
 *   symbols or linking in code that would use timers that are
 *   unavailable in a given density. For example, TIM5 doesn't exist
 *   on medium-density, and TIM9 doesn't exist on high-density, so we
 *   don't define or use TIM5 when being compiled for medium-density,
 *   and similarly for TIM9 and high-density.
 *
 *   This makes a mess, but helps avoid bloat and ensures backwards
 *   compatibility. Since the mess is manageable and there don't seem
 *   to be any plans on ST's part to add new STM32F1 lines or
 *   densities, we'll live with it.
 */

#include <libmaple/timer.h>
#include "timer_private.h"

/*
 * Devices
 *
 * Defer to the timer_private API.
 */

static DECLARE_ADVANCED_TIMER(timer1, 1);
static DECLARE_GENERAL_TIMER(timer2, 2);
static DECLARE_GENERAL_TIMER(timer3, 3);
static DECLARE_GENERAL_TIMER(timer4, 4);

/** Timer 1 device (advanced) */
timer_dev *TIMER1 = &timer1;
/** Timer 2 device (general-purpose) */
timer_dev *TIMER2 = &timer2;
/** Timer 3 device (general-purpose) */
timer_dev *TIMER3 = &timer3;
/** Timer 4 device (general-purpose) */
timer_dev *TIMER4 = &timer4;

#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
static DECLARE_GENERAL_TIMER(timer5, 5);
static DECLARE_BASIC_TIMER(timer6, 6);
static DECLARE_BASIC_TIMER(timer7, 7);
static DECLARE_ADVANCED_TIMER(timer8, 8);

/** Timer 5 device (general-purpose) */
timer_dev *TIMER5 = &timer5;
/** Timer 6 device (basic) */
timer_dev *TIMER6 = &timer6;
/** Timer 7 device (basic) */
timer_dev *TIMER7 = &timer7;
/** Timer 8 device (advanced) */
timer_dev *TIMER8 = &timer8;
#endif  /* defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY) */

#ifdef STM32_XL_DENSITY
/* TIM9 has UIE, CC1IE, CC2IE, TIE bits in DIER. */
static DECLARE_RESTRICTED_GENERAL_TIMER(timer9, 9, TIMER_DIER_TIE_BIT);
/* TIM10 has UIE, CC1IE. */
static DECLARE_RESTRICTED_GENERAL_TIMER(timer10, 10, TIMER_DIER_CC1IE_BIT);
/* TIM11 has UIE, CC1IE. */
static DECLARE_RESTRICTED_GENERAL_TIMER(timer11, 11, TIMER_DIER_CC1IE_BIT);
/* TIM12 has UIE, CC1IE, CC2IE, TIE. */
static DECLARE_RESTRICTED_GENERAL_TIMER(timer12, 12, TIMER_DIER_TIE_BIT);
/* TIM13 has UIE, CC1IE. */
static DECLARE_RESTRICTED_GENERAL_TIMER(timer13, 13, TIMER_DIER_CC1IE_BIT);
/* TIM14 has UIE, CC1IE. */
static DECLARE_RESTRICTED_GENERAL_TIMER(timer14, 14, TIMER_DIER_CC1IE_BIT);

/** Timer 9 device (general-purpose) */
timer_dev *TIMER9 = &timer9;
/** Timer 10 device (general-purpose) */
timer_dev *TIMER10 = &timer10;
/** Timer 11 device (general-purpose) */
timer_dev *TIMER11 = &timer11;
/** Timer 12 device (general-purpose) */
timer_dev *TIMER12 = &timer12;
/** Timer 13 device (general-purpose) */
timer_dev *TIMER13 = &timer13;
/** Timer 14 device (general-purpose) */
timer_dev *TIMER14 = &timer14;
#endif  /* STM32_XL_DENSITY */

/*
 * Routines
 */

/**
 * @brief Call a function on timer devices.
 * @param fn Function to call on each timer device.
 */
void timer_foreach(void (*fn)(timer_dev*)) {
    fn(TIMER1);
    fn(TIMER2);
    fn(TIMER3);
    fn(TIMER4);
#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
    fn(TIMER5);
    fn(TIMER6);
    fn(TIMER7);
    fn(TIMER8);
#endif
#ifdef STM32_XL_DENSITY
    fn(TIMER9);
    fn(TIMER10);
    fn(TIMER11);
    fn(TIMER12);
    fn(TIMER13);
    fn(TIMER14);
#endif
}

/*
 * IRQ handlers
 *
 * Defer to the timer_private dispatch API.
 *
 * FIXME: The names of these handlers are inaccurate since XL-density
 * devices came out. Update these to match the STM32F2 names, maybe
 * using some weak symbol magic to preserve backwards compatibility if
 * possible.
 */

void __irq_tim1_brk(void) {
    dispatch_adv_brk(TIMER1);
#ifdef STM32_XL_DENSITY
    dispatch_tim_9_12(TIMER9);
#endif
}

void __irq_tim1_up(void) {
    dispatch_adv_up(TIMER1);
#ifdef STM32_XL_DENSITY
    dispatch_tim_10_11_13_14(TIMER10);
#endif
}

void __irq_tim1_trg_com(void) {
    dispatch_adv_trg_com(TIMER1);
#ifdef STM32_XL_DENSITY
    dispatch_tim_10_11_13_14(TIMER11);
#endif
}

void __irq_tim1_cc(void) {
    dispatch_adv_cc(TIMER1);
}

void __irq_tim2(void) {
    dispatch_general(TIMER2);
}

void __irq_tim3(void) {
    dispatch_general(TIMER3);
}

void __irq_tim4(void) {
    dispatch_general(TIMER4);
}

#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
void __irq_tim5(void) {
    dispatch_general(TIMER5);
}

void __irq_tim6(void) {
    dispatch_basic(TIMER6);
}

void __irq_tim7(void) {
    dispatch_basic(TIMER7);
}

void __irq_tim8_brk(void) {
    dispatch_adv_brk(TIMER8);
#ifdef STM32_XL_DENSITY
    dispatch_tim_9_12(TIMER12);
#endif
}

void __irq_tim8_up(void) {
    dispatch_adv_up(TIMER8);
#ifdef STM32_XL_DENSITY
    dispatch_tim_10_11_13_14(TIMER13);
#endif
}

void __irq_tim8_trg_com(void) {
    dispatch_adv_trg_com(TIMER8);
#ifdef STM32_XL_DENSITY
    dispatch_tim_10_11_13_14(TIMER14);
#endif
}

void __irq_tim8_cc(void) {
    dispatch_adv_cc(TIMER8);
}
#endif  /* defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY) */
