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

/**
 *  @brief wirish timer class to manage the four 16-bit timer peripherals
 */

#ifndef _HARDWARETIMER_H_
#define _HARDWARETIMER_H_

#include "timers.h"

/**
 * Interface to one of the 16-bit timer peripherals.
 *
 * User code should not instantiate this class directly; instead, use
 * one of the predefined Timer<n> instances (Timer1, Timer2, etc.).
 *
 * HardwareTimer instances can be configured to generate periodic or
 * delayed events with minimal work done by the microcontroller.  Each
 * timer maintains a single 16-bit count that can be configured with a
 * prescaler and overflow value.
 *
 * By default, a timer's counter is incremented once per clock cycle.
 * The prescaler acts as a divider of the 72MHz Maple system clock;
 * without prescaling, the timer's count would reach 65535 (2**16-1)
 * and roll over over 1000 times per second.
 *
 * The overflow value is the maximum value the counter will reach.  It
 * defaults to 65535; smaller values will cause the counter to reset
 * more frequently.
 */
class HardwareTimer {
 private:
    timer_dev_num timerNum;

 public:
    HardwareTimer(timer_dev_num timer_num);

    /**
     * Return this timer's device number. For example,
     *  Timer1.getTimerNum() == TIMER1
     */
    timer_dev_num getTimerNum() { return timerNum; }

    /**
     * Stop the counter, without affecting its configuration.
     *
     * The timer will no longer count or fire interrupts after this
     * function is called, until it is resumed.  This function is
     * useful during timer setup periods, in order to prevent
     * interrupts from firing before the timer is fully configured.
     *
     * Note that there is some function call overhead associated with
     * this method, so using it in concert with
     * HardwareTimer::resume() is not a robust way to align multiple
     * timers to the same count value.
     *
     * @see HardwareTimer::resume()
     */
    void pause(void);

    /**
     * Resume a paused timer, without affecting its configuration.
     *
     * The timer will resume counting and firing interrupts as
     * appropriate.
     *
     * Note that there is some function call overhead associated with
     * using this method, so using it in concert with
     * HardwareTimer::pause() is not a robust way to align multiple
     * timers to the same count value.
     *
     * @see HardwareTimer::pause()
     */
    void resume(void);

    /**
     * Returns the timer's prescale factor.
     * @see HardwareTimer::setPrescaleFactor()
     */
    uint16 getPrescaleFactor();

    /**
     * Set the timer's prescale factor.
     *
     * The prescaler acts as a clock divider to slow down the rate at
     * which the counter increments.
     *
     * For example, the system clock rate is 72MHz, so the counter
     * will reach 65535 in (13.89 nanoseconds) * (65535 counts) =
     * (910.22 microseconds), or about a thousand times a second. If
     * the prescaler equals 1098, then the clock rate is effectively
     * 65.56KHz, and the counter will reach 65536 in (15.25
     * microseconds) * (65536 counts) = (0.999 seconds), or about once
     * per second.
     *
     * The HardwareTimer::setPeriod() method may also be used as a
     * convenient alternative.
     *
     * @param factor The new prescale value to set.
     * @see HardwareTimer::setPeriod()
     */
    void setPrescaleFactor(uint16 factor);

    /**
     * Gets the timer overflow value.
     * @see HardwareTimer::setOverflow()
     */
    uint16 getOverflow();

    /**
     * Sets the timer overflow (or "reload") value.
     *
     * When the timer's counter reaches this, value it resets to
     * zero. Its default value is 65535 (the largest unsigned 16-bit
     * integer); setting the overflow to anything lower will cause
     * interrupts to be called more frequently (see the setPeriod()
     * function below for a shortcut). This number sets the maximum
     * value for the channel compare values.
     *
     * @param val The new overflow value to set
     */
    void setOverflow(uint16 val);

    /**
     * Retrieve the current timer count.
     *
     * @return The timer's current count value
     */
    uint16 getCount(void);

    /**
     * Set the current timer count.
     *
     * Note that there is some function call overhead associated with
     * calling this method, so using it is not a robust way to get
     * multiple timers to share a count value.
     *
     * @param val The new count value to set.  If this value exceeds
     *            the timer's overflow value, it is truncated to the
     *            overflow value.
     */
    void setCount(uint16 val);

    /**
     * Configure the prescaler and overflow values to generate a timer
     * reload with a period as close to the given number of
     * microseconds as possible.
     *
     * The return value is the overflow, which may be used to set
     * channel compare values.  However, if a clock that fires an
     * interrupt every given number of microseconds is all that is
     * desired, and the relative "phases" are unimportant, channel
     * compare values may all be set to 1.
     *
     * @param microseconds the desired period of the timer.
     * @return the overflow value (and thus, the largest value that can be
     *         set as a compare).
     */
    uint16 setPeriod(uint32 microseconds);

    /**
     * Set the given channel of this timer to the given mode.
     *
     * @param channel Timer channel, from 1 to 4
     * @param mode Mode to set
     */
    void setChannelMode(int channel, TimerMode mode);

    /**
     * Set channel 1 of this timer to the given mode.
     *
     * Note: Timer1.setChannel1Mode(TIMER_PWM) may not work as
     * expected; if you want PWM functionality on a channel make sure
     * you don't set it to something else!
     *
     * @see TimerMode
     */
    void setChannel1Mode(TimerMode mode);

    /**
     * Set channel 2 of this timer to the given mode.
     * @see TimerMode
     */
    void setChannel2Mode(TimerMode mode);

    /**
     * Set channel 3 of this timer to the given mode.
     * @see TimerMode
     */
    void setChannel3Mode(TimerMode mode);

    /**
     * Set channel 4 of this timer to the given mode.
     * @see TimerMode
     */
    void setChannel4Mode(TimerMode mode);

    /**
     * Gets the compare value for the given channel.
     * @see HardwareTimer::setCompare()
     */
    uint16 getCompare(int channel);

    /** Equivalent to getCompare(1) */
    uint16 getCompare1();

    /** Equivalent to getCompare(2) */
    uint16 getCompare2();

    /** Equivalent to getCompare(3) */
    uint16 getCompare3();

    /** Equivalent to getCompare(4) */
    uint16 getCompare4();

    /**
     * Sets the compare value for the given channel.
     *
     * When the counter reaches this value the interrupt for this
     * channel will fire if the channel mode is TIMER_OUTPUTCOMPARE
     * and an interrupt is attached.
     *
     * By default, this only changes the relative offsets between
     * events on a single timer ("phase"); they don't control the
     * frequency with which they occur. However, a common trick is to
     * increment the compare value manually in the interrupt handler
     * so that the event will fire again after the increment
     * period. There can be a different increment value for each
     * channel, so this trick allows events to be programmed at 4
     * different rates on a single timer. Note that function call
     * overheads mean that the smallest increment rate is at least a
     * few microseconds.
     *
     * @param channel the channel whose compare to set, from 1 to 4.
     * @param compare The compare value to set.  If greater than this
     *                timer's overflow value, it will be truncated to
     *                the overflow value.
     *
     * @see TimerMode
     * @see HardwareTimer::setChannelMode()
     * @see HardwareTimer::attachInterrupt()
     */
    void setCompare(int channel, uint16 compare);

    /**
     * Equivalent to setCompare(1, compare).
     */
    void setCompare1(uint16 compare);

    /**
     * Equivalent to setCompare(2, compare).
     */
    void setCompare2(uint16 compare);

    /**
     * Equivalent to setCompare(3, compare).
     */
    void setCompare3(uint16 compare);

    /**
     * Equivalent to setCompare(4, compare).
     */
    void setCompare4(uint16 compare);

    /**
     * Attach an interrupt handler to the given channel.  This
     * interrupt handler will be called when the timer's counter
     * reaches the given channel compare value.
     *
     * The argument should be a function which takes no arguments and
     * has no return value; i.e. it should have signature
     *
     *     void (*handler)(void);
     *
     * Note: The function (often called an interrupt service routine,
     * or ISR) should attempt to return as quickly as possible.
     * Blinking the LED, some logic, PWM updates, and Serial writes
     * are fine; writing to SerialUSB or waiting for user input can
     * take a long time and other compare interrupts won't fire. Tip:
     * if you have a delay() in your interrupt routine, you're probably
     * doing it wrong.
     *
     * @param channel the channel to attach the ISR to, from 1 to 4.
     * @param handler The ISR to attach to the given channel.
     * @see voidFuncPtr
     */
    void attachInterrupt(int channel, voidFuncPtr handler);

    /**
     * Equivalent to attachCompareInterrupt(1, handler).
     * @see HardwareTimer::attachCompareInterrupt()
     */
    void attachCompare1Interrupt(voidFuncPtr handler);

    /**
     * Equivalent to attachCompareInterrupt(2, handler).
     * @see HardwareTimer::attachCompareInterrupt()
     */
    void attachCompare2Interrupt(voidFuncPtr handler);

    /**
     * Equivalent to attachCompareInterrupt(3, handler).
     * @see HardwareTimer::attachCompareInterrupt()
     */
    void attachCompare3Interrupt(voidFuncPtr handler);

    /**
     * Equivalent to attachCompareInterrupt(4, handler).
     * @see HardwareTimer::attachCompareInterrupt()
     */
    void attachCompare4Interrupt(voidFuncPtr handler);

    /**
     * Remove the interrupt handler attached to the given channel, if
     * any.  The handler will no longer be called by this timer.
     *
     * @param channel the channel whose interrupt to detach, from 1 to 4.
     * @see HardwareTimer::attachInterrupt()
     */
    void detachInterrupt(int channel);

    /**
     * Equivalent to detachInterrupt(1).
     * @see HardwareTimer::detachInterrupt()
     */
    void detachCompare1Interrupt(void);

    /**
     * Equivalent to detachInterrupt(2).
     * @see HardwareTimer::detachInterrupt()
     */
    void detachCompare2Interrupt(void);

    /**
     * Equivalent to detachInterrupt(3).
     * @see HardwareTimer::detachInterrupt()
     */
    void detachCompare3Interrupt(void);

    /**
     * Equivalent to detachInterrupt(4).
     * @see HardwareTimer::detachInterrupt()
     */
    void detachCompare4Interrupt(void);

    /**
     * Re-initializes the counter (to 0 in upcounting mode, which is
     * the default), and generates an update of the prescale and
     * overflow registers.
     */
    void generateUpdate(void);
};

/** Pre-instantiated timer for use by user code. */
extern HardwareTimer Timer1;
/** Pre-instantiated timer for use by user code. */
extern HardwareTimer Timer2;
/** Pre-instantiated timer for use by user code. */
extern HardwareTimer Timer3;
/** Pre-instantiated timer for use by user code. */
extern HardwareTimer Timer4;
#if NR_TIMERS >= 8
/** Pre-instantiated timer for use by user code, on devices with
    more than four timers (this does not include the Maple). */
extern HardwareTimer Timer5;
/** Pre-instantiated timer for use by user code, on devices with
    more than four timers (this does not include the Maple). */
extern HardwareTimer Timer8;
#endif

/**
 * Get one of the pre-instantiated HardwareTimer instances, given a
 * timer device number.
 *
 * Be careful not to pass an actual number to this function.  For
 * example, getTimer(1) will not return Timer1.  Use a real
 * timer_dev_num, e.g. TIMER1, TIMER2, etc.
 *
 * @param timerNum the timer device number, e.g. TIMER1.
 *
 * @return Pointer to the HardwareTimer instance corresponding to the
 * given timer device number.  If timerNum is TIMER_INVALID, returns a
 * null pointer.
 *
 * @see timer_dev_num
 */
HardwareTimer* getTimer(timer_dev_num timerNum);

#endif

