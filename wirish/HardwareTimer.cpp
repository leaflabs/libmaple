/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Bryan Newbold.
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

/*
 * wirish timer class to manage the four 16-bit timer peripherals
 */

#include "wirish.h"
#include "HardwareTimer.h"

HardwareTimer::HardwareTimer(timer_dev_num timerNum) {
    ASSERT(timerNum != TIMER_INVALID);

    this->timerNum = timerNum;
}

void HardwareTimer::resume(void) {
    timer_resume(this->timerNum);
}

void HardwareTimer::pause(void) {
    timer_pause(this->timerNum);
}

uint16 HardwareTimer::getPrescaleFactor(void) {
    return timer_get_prescaler(this->timerNum) + 1;
}

void HardwareTimer::setPrescaleFactor(uint16 factor) {
    // The prescaler register is zero-indexed
    timer_set_prescaler(this->timerNum, factor-1);
}

uint16 HardwareTimer::getOverflow() {
    return timer_get_reload(this->timerNum);
}

void HardwareTimer::setOverflow(uint16 val) {
    timer_set_reload(this->timerNum, val);
}

uint16 HardwareTimer::getCount(void) {
    return timer_get_count(this->timerNum);
}

void HardwareTimer::setCount(uint16 val) {
    uint16 ovf = this->getOverflow();
    timer_set_count(this->timerNum, min(val, ovf));
}

uint16 HardwareTimer::setPeriod(uint32 microseconds) {
    // Not the best way to handle this edge case?
    if(!microseconds) {
        setPrescaleFactor(1);
        setOverflow(1);
        return this->getOverflow();
    }
    uint32 cycles = microseconds * CYCLES_PER_MICROSECOND;

    // With a prescale factor of 1, there are CYCLES_PER_MICROSECOND
    // counts/ms
    uint16 ps = (uint16)((cycles >> 16) + 1);
    setPrescaleFactor(ps);

    // Finally, this overflow will always be less than 65536
    setOverflow((cycles/ps) - 1);

    return this->getOverflow();
}

inline void HardwareTimer::setChannelMode(int channel, TimerMode mode) {
    timer_set_mode(this->timerNum, channel, mode);
}

void HardwareTimer::setChannel1Mode(TimerMode mode) {
    this->setChannelMode(1, mode);
}

void HardwareTimer::setChannel2Mode(TimerMode mode) {
    this->setChannelMode(2, mode);
}

void HardwareTimer::setChannel3Mode(TimerMode mode) {
    this->setChannelMode(3, mode);
}

void HardwareTimer::setChannel4Mode(TimerMode mode) {
    this->setChannelMode(4, mode);
}

inline uint16 HardwareTimer::getCompare(int channel) {
    return timer_get_compare_value(this->timerNum, channel);
}

uint16 HardwareTimer::getCompare1() {
    return this->getCompare(1);
}

uint16 HardwareTimer::getCompare2() {
    return this->getCompare(2);
}

uint16 HardwareTimer::getCompare3() {
    return this->getCompare(3);
}

uint16 HardwareTimer::getCompare4() {
    return this->getCompare(4);
}

inline void HardwareTimer::setCompare(int channel, uint16 val) {
    uint16 ovf = this->getOverflow();
    timer_set_compare_value(this->timerNum, channel, min(val, ovf));
}

void HardwareTimer::setCompare1(uint16 val) {
    this->setCompare(1, val);
}

void HardwareTimer::setCompare2(uint16 val) {
    this->setCompare(2, val);
}

void HardwareTimer::setCompare3(uint16 val) {
    this->setCompare(3, val);
}

void HardwareTimer::setCompare4(uint16 val) {
    this->setCompare(4, val);
}

inline void HardwareTimer::attachInterrupt(int channel, voidFuncPtr handler) {
    timer_attach_interrupt(this->timerNum, channel, handler);
}

void HardwareTimer::attachCompare1Interrupt(voidFuncPtr handler) {
    this->attachInterrupt(1, handler);
}

void HardwareTimer::attachCompare2Interrupt(voidFuncPtr handler) {
    this->attachInterrupt(2, handler);
}

void HardwareTimer::attachCompare3Interrupt(voidFuncPtr handler) {
    this->attachInterrupt(3, handler);
}

void HardwareTimer::attachCompare4Interrupt(voidFuncPtr handler) {
    this->attachInterrupt(4, handler);
}

inline void HardwareTimer::detachInterrupt(int channel) {
    timer_detach_interrupt(this->timerNum, channel);
}

void HardwareTimer::detachCompare1Interrupt(void) {
    this->detachInterrupt(1);
}

void HardwareTimer::detachCompare2Interrupt(void) {
    this->detachInterrupt(2);
}

void HardwareTimer::detachCompare3Interrupt(void) {
    this->detachInterrupt(3);
}

void HardwareTimer::detachCompare4Interrupt(void) {
    this->detachInterrupt(4);
}

void HardwareTimer::generateUpdate(void) {
    timer_generate_update(this->timerNum);
}


HardwareTimer Timer1(TIMER1);
HardwareTimer Timer2(TIMER2);
HardwareTimer Timer3(TIMER3);
HardwareTimer Timer4(TIMER4);
#if NR_TIMERS >= 8
HardwareTimer Timer5(TIMER5);    // High-density devices only
HardwareTimer Timer8(TIMER8);    // High-density devices only
#endif

HardwareTimer* getTimer(timer_dev_num timerNum) {
    switch (timerNum) {
    case TIMER1:
        return &Timer1;
    case TIMER2:
        return &Timer2;
    case TIMER3:
        return &Timer3;
    case TIMER4:
        return &Timer4;
#if NR_TIMERS >= 8
    case TIMER5:
        return &Timer5;
    case TIMER8:
        return &Timer8;
#endif
    default:
        return 0;
    }
}
