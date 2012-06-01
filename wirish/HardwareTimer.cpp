/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Bryan Newbold.
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

#include <wirish/HardwareTimer.h>
#include <wirish/boards.h>             // for CYCLES_PER_MICROSECOND
#include <wirish/wirish_math.h>

// TODO [0.1.0] Remove deprecated pieces

#define MAX_RELOAD ((1 << 16) - 1)

/*
 * Big ugly table of timers available on the MCU. Needed by the
 * HardwareTimer constructor. Sigh; maybe predefined instances weren't
 * such a bad idea. Oh well, at least the HardwareTimer interface is
 * officially unstable since v0.0.12; we can always get rid of this
 * later.
 */

#define MAX_NR_TIMERS 17 // No STM32 I've ever heard of has higher than TIMER17

static timer_dev *devs[MAX_NR_TIMERS] = {
#if STM32_HAVE_TIMER(1)
    TIMER1,
#else
    NULL,
#endif
#if STM32_HAVE_TIMER(2)
    TIMER2,
#else
    NULL,
#endif
#if STM32_HAVE_TIMER(3)
    TIMER3,
#else
    NULL,
#endif
#if STM32_HAVE_TIMER(4)
    TIMER4,
#else
    NULL,
#endif
#if STM32_HAVE_TIMER(5)
    TIMER5,
#else
    NULL,
#endif
#if STM32_HAVE_TIMER(6)
    TIMER6,
#else
    NULL,
#endif
#if STM32_HAVE_TIMER(7)
    TIMER7,
#else
    NULL,
#endif
#if STM32_HAVE_TIMER(8)
    TIMER8,
#else
    NULL,
#endif
#if STM32_HAVE_TIMER(9)
    TIMER9,
#else
    NULL,
#endif
#if STM32_HAVE_TIMER(10)
    TIMER10,
#else
    NULL,
#endif
#if STM32_HAVE_TIMER(11)
    TIMER11,
#else
    NULL,
#endif
#if STM32_HAVE_TIMER(12)
    TIMER12,
#else
    NULL,
#endif
#if STM32_HAVE_TIMER(13)
    TIMER13,
#else
    NULL,
#endif
#if STM32_HAVE_TIMER(14)
    TIMER14,
#else
    NULL,
#endif
#if STM32_HAVE_TIMER(15)
    TIMER15,
#else
    NULL,
#endif
#if STM32_HAVE_TIMER(16)
    TIMER16,
#else
    NULL,
#endif
#if STM32_HAVE_TIMER(17)
    TIMER17,
#else
    NULL,
#endif
};

/*
 * HardwareTimer routines
 */

HardwareTimer::HardwareTimer(uint8 timerNum) {
    ASSERT(timerNum <= MAX_NR_TIMERS);
    this->dev = devs[timerNum - 1];
    ASSERT(this->dev != NULL);
}

void HardwareTimer::pause(void) {
    timer_pause(this->dev);
}

void HardwareTimer::resume(void) {
    timer_resume(this->dev);
}

uint32 HardwareTimer::getPrescaleFactor(void) {
    return timer_get_prescaler(this->dev) + 1;
}

void HardwareTimer::setPrescaleFactor(uint32 factor) {
    timer_set_prescaler(this->dev, (uint16)(factor - 1));
}

uint16 HardwareTimer::getOverflow() {
    return timer_get_reload(this->dev);
}

void HardwareTimer::setOverflow(uint16 val) {
    timer_set_reload(this->dev, val);
}

uint16 HardwareTimer::getCount(void) {
    return timer_get_count(this->dev);
}

void HardwareTimer::setCount(uint16 val) {
    uint16 ovf = this->getOverflow();
    timer_set_count(this->dev, min(val, ovf));
}

uint16 HardwareTimer::setPeriod(uint32 microseconds) {
    // Not the best way to handle this edge case?
    if (!microseconds) {
        this->setPrescaleFactor(1);
        this->setOverflow(1);
        return this->getOverflow();
    }

    uint32 period_cyc = microseconds * CYCLES_PER_MICROSECOND;
    uint16 prescaler = (uint16)(period_cyc / MAX_RELOAD + 1);
    uint16 overflow = (uint16)round(period_cyc / prescaler);
    this->setPrescaleFactor(prescaler);
    this->setOverflow(overflow);
    return overflow;
}

void HardwareTimer::setMode(int channel, timer_mode mode) {
    timer_set_mode(this->dev, (uint8)channel, (timer_mode)mode);
}

uint16 HardwareTimer::getCompare(int channel) {
    return timer_get_compare(this->dev, (uint8)channel);
}

void HardwareTimer::setCompare(int channel, uint16 val) {
    uint16 ovf = this->getOverflow();
    timer_set_compare(this->dev, (uint8)channel, min(val, ovf));
}

void HardwareTimer::attachInterrupt(int channel, voidFuncPtr handler) {
    timer_attach_interrupt(this->dev, (uint8)channel, handler);
}

void HardwareTimer::detachInterrupt(int channel) {
    timer_detach_interrupt(this->dev, (uint8)channel);
}

void HardwareTimer::refresh(void) {
    timer_generate_update(this->dev);
}

/* -- Deprecated predefined instances -------------------------------------- */

HardwareTimer Timer1(1);
HardwareTimer Timer2(2);
HardwareTimer Timer3(3);
HardwareTimer Timer4(4);
#ifdef STM32_HIGH_DENSITY
HardwareTimer Timer5(5);
HardwareTimer Timer6(6);
HardwareTimer Timer7(7);
HardwareTimer Timer8(8);
#endif
