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
 */

#ifndef _TIMER_H_
#define _TIMER_H_

class HardwareTimer {
    private:
        uint16 overflow;
        uint8 timerNum;

    public:
        HardwareTimer(uint8 timer_num);

        void pause(void);
        void resume(void);
        void setPrescaleFactor(uint16 factor);
        void setOverflow(uint16 val); // truncates to overflow
        void setCount(uint16 val);    // truncates to overflow
        uint16 getCount(void);

        // tries to set prescaler and overflow wisely; returns overflow
        uint16 setPeriod(uint32 microseconds); 
        void setChannel1Mode(uint8 mode);
        void setChannel2Mode(uint8 mode);
        void setChannel3Mode(uint8 mode);
        void setChannel4Mode(uint8 mode);
        void setCompare1(uint16 val); // truncates to overflow
        void setCompare2(uint16 val); // truncates to overflow
        void setCompare3(uint16 val); // truncates to overflow
        void setCompare4(uint16 val); // truncates to overflow
        void attachCompare1Interrupt(voidFuncPtr handler);
        void attachCompare2Interrupt(voidFuncPtr handler);
        void attachCompare3Interrupt(voidFuncPtr handler);
        void attachCompare4Interrupt(voidFuncPtr handler);
        void detachCompare1Interrupt(void);
        void detachCompare2Interrupt(void);
        void detachCompare3Interrupt(void);
        void detachCompare4Interrupt(void);
};

extern HardwareTimer Timer1;
extern HardwareTimer Timer2;
extern HardwareTimer Timer3;
extern HardwareTimer Timer4;

#endif

