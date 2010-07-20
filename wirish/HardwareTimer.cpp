/* *****************************************************************************
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
 * ****************************************************************************/

/**
 *  @brief wirish timer class to manage the four 16-bit timer peripherals
 *
 *  This implementation is not very efficient (lots of duplicated functions)
 */

#include "wirish.h"
#include "HardwareTimer.h"

HardwareTimer::HardwareTimer(uint8 timerNum) {
    ASSERT(timerNum == 1 ||
           timerNum == 2 ||
           timerNum == 3 ||
           timerNum == 4);
    this->timerNum = timerNum;
    // Need to remember over flow for bounds checking
    this->overflow = 0xFFFF;
}

void HardwareTimer::resume(void) {
    timer_resume(this->timerNum);
}
void HardwareTimer::pause(void) {
    timer_pause(this->timerNum);
}
void HardwareTimer::setPrescaleFactor(uint16 factor) {
    // The prescaler register is zero-indexed
    timer_set_prescaler(this->timerNum, factor-1);
}
void HardwareTimer::setOverflow(uint16 val) {
    this->overflow = val;
    timer_set_reload(this->timerNum, val);
}
void HardwareTimer::setCount(uint16 val) {    
    if(val > this->overflow)
        val = this->overflow;
    timer_set_count(this->timerNum, val);
}
uint16 HardwareTimer::getCount(void) {
    return timer_get_count(this->timerNum);
}

// This function will set the prescaler and overflow to get
// a period of the given length with the most resolution; 
// the return value is the overflow value and thus the largest
// value that can be set as a compare.
uint16 HardwareTimer::setPeriod(uint32 microseconds) {
    // XXX: 72MHz shouldn't be hard coded in here... global define?
    
    // Not the best way to handle this edge case?
    if(!microseconds) {
        setPrescaleFactor(1);
        setOverflow(1);
        return this->overflow;
    }
    // With a prescale factor of 1, there are 72counts/ms
    uint16 ps = ((microseconds*72)/65536) + 1;
    setPrescaleFactor(ps);
    // Find this overflow will always be less than 65536
    setOverflow((microseconds*72)/ps);
    return this->overflow;    
}
void HardwareTimer::setChannel1Mode(uint8 mode) {
    timer_set_mode(this->timerNum,1,mode);
}
void HardwareTimer::setChannel2Mode(uint8 mode) {
    timer_set_mode(this->timerNum,2,mode);
}
void HardwareTimer::setChannel3Mode(uint8 mode) {
    timer_set_mode(this->timerNum,3,mode);
}
void HardwareTimer::setChannel4Mode(uint8 mode) {
    timer_set_mode(this->timerNum,4,mode);
}
void HardwareTimer::setCompare1(uint16 val) {
    if(val > this->overflow)
        val = this->overflow;
    timer_set_compare_value(this->timerNum,1,val);
}
void HardwareTimer::setCompare2(uint16 val) {
    if(val > this->overflow)
        val = this->overflow;
    timer_set_compare_value(this->timerNum,2,val);
}
void HardwareTimer::setCompare3(uint16 val) {
    ASSERT(this->timerNum);
    if(val > this->overflow)
        val = this->overflow;
    timer_set_compare_value(this->timerNum,3,val);
}
void HardwareTimer::setCompare4(uint16 val) {
    if(val > this->overflow)
        val = this->overflow;
    timer_set_compare_value(this->timerNum,4,val);
}
void HardwareTimer::attachCompare1Interrupt(voidFuncPtr handler) {
    timer_attach_interrupt(this->timerNum,1,handler);
}
void HardwareTimer::attachCompare2Interrupt(voidFuncPtr handler) {
    timer_attach_interrupt(this->timerNum,2,handler);
}
void HardwareTimer::attachCompare3Interrupt(voidFuncPtr handler) {
    timer_attach_interrupt(this->timerNum,3,handler);
}
void HardwareTimer::attachCompare4Interrupt(voidFuncPtr handler) {
    timer_attach_interrupt(this->timerNum,4,handler);
}
void HardwareTimer::detachCompare1Interrupt(void) {
    timer_detach_interrupt(this->timerNum,1);
}
void HardwareTimer::detachCompare2Interrupt(void) {
    timer_detach_interrupt(this->timerNum,2);
}
void HardwareTimer::detachCompare3Interrupt(void) {
    timer_detach_interrupt(this->timerNum,3);
}
void HardwareTimer::detachCompare4Interrupt(void) {
    timer_detach_interrupt(this->timerNum,4);
}

HardwareTimer Timer1(1);
HardwareTimer Timer2(2);
HardwareTimer Timer3(3);
HardwareTimer Timer4(4);

