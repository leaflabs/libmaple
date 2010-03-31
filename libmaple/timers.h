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
 *  Created: 12/18/09 02:38:10
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file timers.h
 *
 *  @brief Timer prototypes and various definitions
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
 * */

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
#include  <inttypes.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef volatile uint32_t* TimerCCR;

#define TIMER1_BASE        0x40012C00
#define TIMER2_BASE        0x40000000
#define TIMER3_BASE        0x40000400
#define TIMER4_BASE        0x40000800

#define ARPE               BIT(7)                // Auto-reload preload enable
#define NOT_A_TIMER        0

#define TIMER1_CH1_CCR     (TimerCCR)(TIMER1_BASE + 0x34)
#define TIMER1_CH2_CCR     (TimerCCR)(TIMER1_BASE + 0x38)
#define TIMER1_CH3_CCR     (TimerCCR)(TIMER1_BASE + 0x3C)
#define TIMER1_CH4_CCR     (TimerCCR)(TIMER1_BASE + 0x40)

#define TIMER2_CH1_CCR     (TimerCCR)(TIMER2_BASE + 0x34)
#define TIMER2_CH2_CCR     (TimerCCR)(TIMER2_BASE + 0x38)
#define TIMER2_CH3_CCR     (TimerCCR)(TIMER2_BASE + 0x3C)
#define TIMER2_CH4_CCR     (TimerCCR)(TIMER2_BASE + 0x40)

#define TIMER3_CH1_CCR     (TimerCCR)(TIMER3_BASE + 0x34)
#define TIMER3_CH2_CCR     (TimerCCR)(TIMER3_BASE + 0x38)
#define TIMER3_CH3_CCR     (TimerCCR)(TIMER3_BASE + 0x3C)
#define TIMER3_CH4_CCR     (TimerCCR)(TIMER3_BASE + 0x40)

#define TIMER4_CH1_CCR     (TimerCCR)(TIMER4_BASE + 0x34)
#define TIMER4_CH2_CCR     (TimerCCR)(TIMER4_BASE + 0x38)
#define TIMER4_CH3_CCR     (TimerCCR)(TIMER4_BASE + 0x3C)
#define TIMER4_CH4_CCR     (TimerCCR)(TIMER4_BASE + 0x40)


/* Turn on timer with prescale as the divisor
 * void timer_init(uint32_t timer, uint16_t prescale)
 *      timer     ->  {1-4}
 *      prescale  ->  {1-65535}
 * */
void timer_init(uint8_t, uint16_t);
void timers_disable(void);
void timers_disable_channel(uint8, uint8);

/* Turn on PWM with duty_cycle on the specified channel in timer.
 * This function takes in a pointer to the corresponding CCR
 * register for the pin cause it saves pwmWrite() a couple of
 * cycles.
 *
 * void timer_pwm(uint8_t channel, uint8_t duty_cycle);
 *      channel    -> {TIMERx_CHn_CCR}
 *      duty_cycle -> {0-65535}
 *
 * PRECONDITIONS:
 *      pin has been set to alternate function output
 *      timer has been initialized
 */
static inline void timer_pwm_write_ccr(TimerCCR CCR, uint16_t duty_cycle) {
    *CCR = duty_cycle;
}

#ifdef __cplusplus
} // extern "C"
#endif


#endif

