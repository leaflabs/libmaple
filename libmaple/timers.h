/******************************************************************************
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
 *****************************************************************************/

/**
 * @file timers.h
 *
 * @brief Timer prototypes and various definitions
 */

/* Note to self:
 * The timer clock frequencies are automatically fixed by hardware.
 * There are two cases:
 *     1.  if the APB prescaler is 1, the timer clock frequencies are
 *         set to the same frequency as that of the APB domain to which
 *         the timers are connected.
 *     2.  otherwise, they are set to twice (x2) the frequency of the
 *         APB domain to which the timers are connected.
 * See stm32 manual, 77/995
 *
 * hence, 72 mhz timers
 */

/* Maple Timer channels:
 * Timer        Maple Pin               STM32 Pin     Type
 * TIM1_CH1     D6                      PA8           Advanced
 * TIM1_CH2     D7                      PA9           Advanced
 * TIM1_CH3     D8                      PA10          Advanced
 *
 * TIM2_CH1     D2                      PA0
 * TIM2_CH2     D3                      PA1
 * TIM2_CH3     D1                      PA2
 * TIM2_CH4     D0                      PA3
 *
 * TIM3_CH1     D12                     PA6
 * TIM3_CH2     D11                     PA7
 * TIM3_CH3     EXT7                    PB0
 * TIM3_CH4     EXT8                    PB1
 *
 * TIM4_CH1     EXT5                    PB6
 * TIM4_CH1     EXT9                    PB7
 * TIM4_CH1     EXT15                   PB8
 * TIM4_CH1     EXT4                    PB9
 *
 * Not supported:
 * TIM1_CH4    USBDM, not available     PA11          Advanced
 * TIM1_CH1_N  EXT12                    PB13
 * TIM1_CH2_N  EXT13                    PB14
 * TIM1_CH3_N  EXT14                    PB15
 * */

/* I don't like the Arduino API for dealing with pin modes.
 * How about...
 *
 * pinMode(digitalPin, PWM);
 * pwmWrite(digitalPin) */

#ifndef _TIMERS_H_
#define _TIMERS_H_

#ifdef __cplusplus
extern "C"{
#endif

typedef volatile uint32* TimerCCR;

#define TIMER1_BASE        0x40012C00
#define TIMER2_BASE        0x40000000
#define TIMER3_BASE        0x40000400
#define TIMER4_BASE        0x40000800
#define TIMER5_BASE        0x40000C00   // High-density devices only
#define TIMER6_BASE        0x40001000   // High-density devices only
#define TIMER7_BASE        0x40001400   // High-density devices only
#define TIMER8_BASE        0x40013400   // High-density devices only

#define ARPE               BIT(7)       // Auto-reload preload enable
#define NOT_A_TIMER        0

#define TIMER_CCR(NUM,CHAN)     TIMER ## NUM ## _CH ## CHAN ## _CRR

#define TIMER1_CH1_CCR     TIMER1_BASE + 0x34
#define TIMER1_CH2_CCR     TIMER1_BASE + 0x38
#define TIMER1_CH3_CCR     TIMER1_BASE + 0x3C
#define TIMER1_CH4_CCR     TIMER1_BASE + 0x40

#define TIMER2_CH1_CCR     TIMER2_BASE + 0x34
#define TIMER2_CH2_CCR     TIMER2_BASE + 0x38
#define TIMER2_CH3_CCR     TIMER2_BASE + 0x3C
#define TIMER2_CH4_CCR     TIMER2_BASE + 0x40

#define TIMER3_CH1_CCR     TIMER3_BASE + 0x34
#define TIMER3_CH2_CCR     TIMER3_BASE + 0x38
#define TIMER3_CH3_CCR     TIMER3_BASE + 0x3C
#define TIMER3_CH4_CCR     TIMER3_BASE + 0x40

#define TIMER4_CH1_CCR     TIMER4_BASE + 0x34
#define TIMER4_CH2_CCR     TIMER4_BASE + 0x38
#define TIMER4_CH3_CCR     TIMER4_BASE + 0x3C
#define TIMER4_CH4_CCR     TIMER4_BASE + 0x40

/* Timer5 and Timer8 are in high-density devices only (such as Maple
   Native).  Timer6 and Timer7 in these devices have no output compare
   pins. */

#define TIMER5_CH1_CCR     TIMER5_BASE + 0x34
#define TIMER5_CH2_CCR     TIMER5_BASE + 0x38
#define TIMER5_CH3_CCR     TIMER5_BASE + 0x3C
#define TIMER5_CH4_CCR     TIMER5_BASE + 0x40

#define TIMER8_CH1_CCR     TIMER8_BASE + 0x34
#define TIMER8_CH2_CCR     TIMER8_BASE + 0x38
#define TIMER8_CH3_CCR     TIMER8_BASE + 0x3C
#define TIMER8_CH4_CCR     TIMER8_BASE + 0x40

/**
 * Used to configure the behavior of a timer.
 */
typedef enum TimerMode {
    TIMER_DISABLED, /**< In this mode, the timer stops counting,
                       interrupts are not called, and no state changes
                       are output. */
    TIMER_PWM, /**< This is the default mode for pins after
                  initialization. */
    TIMER_OUTPUTCOMPARE, /**< In this mode, the timer counts from 0 to
                            its reload value repeatedly; every time
                            the counter value reaches one of the
                            channel compare values, the corresponding
                            interrupt is fired. */
} TimerMode;

typedef struct {
    volatile uint16 CR1;
    uint16  RESERVED0;
    volatile uint16 CR2;
    uint16  RESERVED1;
    volatile uint16 SMCR;
    uint16  RESERVED2;
    volatile uint16 DIER;
    uint16  RESERVED3;
    volatile uint16 SR;
    uint16  RESERVED4;
    volatile uint16 EGR;
    uint16  RESERVED5;
    volatile uint16 CCMR1;
    uint16  RESERVED6;
    volatile uint16 CCMR2;
    uint16  RESERVED7;
    volatile uint16 CCER;
    uint16  RESERVED8;
    volatile uint16 CNT;
    uint16  RESERVED9;
    volatile uint16 PSC;
    uint16  RESERVED10;
    volatile uint16 ARR;
    uint16  RESERVED11;
    volatile uint16 RCR;
    uint16  RESERVED12;
    volatile uint16 CCR1;
    uint16  RESERVED13;
    volatile uint16 CCR2;
    uint16  RESERVED14;
    volatile uint16 CCR3;
    uint16  RESERVED15;
    volatile uint16 CCR4;
    uint16  RESERVED16;
    volatile uint16 BDTR;   // Not used in general purpose timers
    uint16  RESERVED17;     // Not used in general purpose timers
    volatile uint16 DCR;
    uint16  RESERVED18;
    volatile uint16 DMAR;
    uint16  RESERVED19;
} timer_port;

/**
 * All possible timer device numbers.
 */
typedef enum {
    TIMER1,
    TIMER2,
    TIMER3,
    TIMER4,
    TIMER5,      // High density only
    TIMER6,      // High density only; no compare
    TIMER7,      // High density only; no compare
    TIMER8,      // High density only
} timer_num_t;

/* timer descriptor */
struct timer_dev {
    timer_port *base;
    const uint8 rcc_dev_num;
    const uint8 nvic_dev_num;
    volatile voidFuncPtr handlers[4];
};

extern struct timer_dev timer_dev_table[];

/**
 * Turn on timer with prescale as the clock divisor.
 *
 * @param timer Timer number.  Valid values are TIMER1, TIMER2,
 * TIMER3, TIMER4, and (on high-density devices) TIMER5, TIMER8.
 *
 * @param prescale value in the range 1--65535 to use as a prescaler
 * for timer counter increment frequency.
 *
 * @see timer_set_prescaler()
 * @see timer_set_mode()
 */
void timer_init(uint8 timer, uint16 prescale);

/**
 * Quickly disable all timers.  Calling this function is faster than,
 * e.g., calling timer_set_mode() for all available timers/channels.
 */
void timer_disable_all(void);

/**
 * Returns the timer's counter value.  Due to function call overhead,
 * this value is likely to be inaccurate if the counter is running
 * with a low prescaler.
 *
 * @param timer the timer whose counter to return.
 */
uint16 timer_get_count(uint8 timer);

/**
 * Sets the counter value for the given timer.
 *
 * @param timer the timer whose counter to set.
 *
 * @param value the new counter value.
 */
void timer_set_count(uint8 timer, uint16 value);

/**
 * Stops the timer's counter from incrementing.  Does not modify the
 * timer's mode or settings.
 *
 * @param timer the timer to pause.
 *
 * @see timer_resume()
 */
void timer_pause(uint8 timer);

/**
 * Starts the counter for the given timer.  Does not modify the
 * timer's mode or settings.  The timer will begin counting on the
 * first rising clock cycle after it has been re-enabled using this
 * function.
 *
 * @param timer the timer to resume.
 *
 * @see timer_pause()
 */
void timer_resume(uint8 timer);

/**
 * Sets the prescaler for the given timer.  The prescaler acts as a
 * clock divider of the STM32 72MHz system clock, in that the timer's
 * counter will subsequently increment with frequency equal to 72MHz /
 * prescale.
 *
 * Note that the timer will continue with its current prescaler until
 * the next time its counter reaches its overflow value, starting a
 * counting cycle.  The new prescale value will be in effect for that
 * subsequent counting cycle.
 *
 * @param timer the timer whose prescaler to set.
 *
 * @param prescale the new prescaler, from 1--65,535.
 */
void timer_set_prescaler(uint8 timer, uint16 prescale);

/**
 * Sets the reload value for the entire timer.
 *
 * After this function returns, the timer's counter will reset to 0
 * after it has reached the value max_reload.
 *
 * @param timer the timer whose reload to set.
 *
 * @param max_reload the new reload value.
 */
void timer_set_reload(uint8 timer, uint16 max_reload);

/**
 * Set the mode of an individual timer channel.
 *
 * @param timer the timer whose channel mode to set.
 *
 * @param channel the channel whose mode to set (1 <= channel <= 4).
 *
 * @param mode the new mode value.  Currently acceptable values
 * include TIMER_DISABLED, TIMER_PWM, and TIMER_OUTPUTCOMPARE.  Note
 * that timer_disable_all() will disable all timers and all channels
 * much more quickly than repeated calls to this function with mode
 * TIMER_DISABLED.
 *
 * @see TimerMode
 *
 * @see timer_disable_all()
 */
void timer_set_mode(uint8 timer, uint8 channel, TimerMode mode);

/**
 * Sets the compare value for a given timer channel.  Useful for
 * scheduling when interrupt handlers will be called.
 *
 * @param timer the timer whose channel compare to set.
 *
 * @param channel the channel whose compare to set (1 <= channel <= 4).
 *
 * @param compare the new compare value.  This new value must be less
 * than or equal to the timer's reload value.
 *
 * @see timer_attach_interrupt()
 *
 * @see timer_detach_interrupt()
 *
 * @see timer_set_reload()
 */
void timer_set_compare_value(uint8 timer, uint8 channel, uint16 compare);

/**
 * Attach an interrupt handler for the given timer and channel.  The
 * handler will be called whenever the timer's counter reaches the
 * compare value for the given timer and channel.
 *
 * @param timer the timer whose channel to register with an interrupt handler.
 *
 * @param channel the channel with which the new handler will be
 * associated.  timer_set_compare_value() can be used to set the value
 * which the timer's counter must reach before handler is called (1 <=
 * channel <= 4).
 *
 * @param handler the interrupt handler to call once the timer reaches
 * the given channel's compare value.
 *
 * @pre The channel's mode must be set to TIMER_OUTPUTCOMPARE, or the
 * interrupt handler will not get called.
 *
 * @see timer_set_compare_value()
 *
 * @see timer_detach_interrupt()
 *
 * @see timer_set_mode()
 */
void timer_attach_interrupt(uint8 timer, uint8 channel, voidFuncPtr handler);

/**
 * Detach the interrupt handler for the given timer channel, if any.
 * After this function returns, any handler attached to the given
 * channel will no longer be called.
 *
 * @param timer the timer whose channel to detach the interrupt
 * handler from.
 *
 * @param channel the channel from which to detach the interrupt handler.
 *
 * @see timer_attach_interrupt()
 */
void timer_detach_interrupt(uint8 timer, uint8 channel);

/**
 * Turn on PWM with duty_cycle.
 *
 * @param channel TIMERx_CHn_CCR, where x goes from 1 to NR_TIMERS,
 * and n goes from 1 to 4.
 *
 * @param duty_cycle 0--65535.  duty_cycle=0 means always off;
 * duty_cycle=65535 means always on.
 *
 * @pre Pin has been set to alternate function output.
 *
 * @pre Timer has been initialized.
 */
static inline void timer_pwm_write_ccr(TimerCCR CCR, uint16 duty_cycle) {
    *CCR = duty_cycle;
}

#ifdef __cplusplus
} // extern "C"
#endif


#endif

