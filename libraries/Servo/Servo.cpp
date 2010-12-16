/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010, LeafLabs, LLC.
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

#include "Servo.h"

#include "boards.h"
#include "io.h"
#include "pwm.h"
#include "wirish_math.h"

// Configure prescaler and overflow for a 20msec period (could just
// use HardwareTimer::setPeriod(), but this lets conversions below
// happen more statically, in combination with an inlined map() -- a
// premature optimization? TODO profile speed/size tradeoff)
#define CYC_20MSEC     (20000 * CYCLES_PER_MICROSECOND)
#define SERVO_PRE ((uint16)((CYC_20MSEC >> 16) + 1))
#define SERVO_OVF ((uint16)((CYC_20MSEC / SERVO_PRE) - 1))
#define SERVO_TAU_USEC \
    ((uint32)(((double)SERVO_OVF) * SERVO_PRE / CYCLES_PER_MICROSECOND + 0.5))

#define US_TO_COMPARE(us) ((uint16)map(us, 0, SERVO_TAU_USEC, 0, SERVO_OVF))
#define COMPARE_TO_US(c)  ((uint32)map(c, 0, SERVO_OVF, 0, SERVO_TAU_USEC))

#define ANGLE_TO_US(a)  ((uint16)(map(a, 0, 180, this->min, this->max)))
#define US_TO_ANGLE(us) ((uint8)(map(us, this->min, this->max, 0, 180)))

Servo::Servo() {
    this->pin = NOT_ATTACHED;
    this->timer = 0;
    this->channel = TIMER_INVALID;
    this->min = SERVO_DEFAULT_MIN_PW;
    this->max = SERVO_DEFAULT_MAX_PW;
}

bool Servo::attach(uint8_t pin) {
    return this->attach(pin, SERVO_DEFAULT_MIN_PW, SERVO_DEFAULT_MAX_PW);
}

bool Servo::attach(uint8_t pin, uint16_t min, uint16_t max) {
    timer_dev_num timer_num = PIN_MAP[pin].timer_num;
    uint32_t channel = PIN_MAP[pin].timer_chan;
    if (timer_num == TIMER_INVALID) {
        // don't reset any members or ASSERT(0), to keep driving any
        // previously attach()ed servo.
        return false;
    }
    this->pin = pin;
    this->timer = getTimer(timer_num);
    this->channel = channel;
    this->min = min;
    this->max = max;

    pinMode(pin, PWM);

    this->timer->pause();
    this->timer->setPrescaleFactor(SERVO_PRE);
    this->timer->setOverflow(SERVO_OVF);
    this->timer->generateUpdate();
    this->timer->resume();
    return true;
}

bool Servo::detach() {
    if (this->pin == NOT_ATTACHED) return false;

    this->timer->setChannelMode(this->channel, TIMER_DISABLED);

    this->pin = NOT_ATTACHED;
    this->timer = 0;
    this->channel = TIMER_INVALID;
    this->min = SERVO_DEFAULT_MIN_PW;
    this->max = SERVO_DEFAULT_MAX_PW;

    return true;
}

void Servo::write(unsigned int value) {
    if (value < SERVO_MAX_WRITE_ANGLE) {
        this->writeMicroseconds(ANGLE_TO_US(value));
    } else {
        this->writeMicroseconds(value);
    }
}

void Servo::writeMicroseconds(uint16_t pulseWidth) {
    if (this->pin == NOT_ATTACHED) {
        ASSERT(0);
        return;
    }

    pulseWidth = constrain(pulseWidth, this->min, this->max);
    pwmWrite(this->pin, US_TO_COMPARE(pulseWidth));
}

int Servo::read() const {
    if (this->pin == NOT_ATTACHED) {
        ASSERT(0);
        return 0;
    }

    unsigned int pw = this->readMicroseconds();
    int a = US_TO_ANGLE(pw);
    // map() round-trips in a weird way we correct for here
    return a == 0 || a == 180 ? a : a + 1;
}

uint16_t Servo::readMicroseconds() const {
    if (this->pin == NOT_ATTACHED) {
        ASSERT(0);
        return 0;
    }

    unsigned int compare = this->timer->getCompare(this->channel);
    uint16_t c = COMPARE_TO_US(compare);
    // map() round-trips in a weird way we correct for here
    return c == 0 || c == 180 ? c : c + 1;
}
