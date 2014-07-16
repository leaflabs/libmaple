/* Copyright (c) 2014, Nordic Semiconductor ASA
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <Arduino.h>

extern uint8_t timer1_f;

/*** FUNC

Name:           Timer1start

Function:       Start timer 1 to interrupt periodically. Call this from 
                the Arduino setup() function.

Description:    The pre-scaler and the timer count divide the timer-counter
                clock frequency to give a timer overflow interrupt rate:

                Interrupt rate =  16MHz / (prescaler * (255 - TCNT2))

        TCCR2B[b2:0]   Prescaler    Freq [KHz], Period [usec] after prescale
          0x0            (TC stopped)     0         0
          0x1                1        16000.        0.0625
          0x2                8         2000.        0.500
          0x3               32          500.        2.000
          0x4               64          250.        4.000
          0x5              128          125.        8.000
          0x6              256           62.5      16.000
          0x7             1024           15.625    64.000


Parameters: void

Returns:    void

FUNC ***/

void Timer1start(void) 
{

    // Setup Timer1 overflow to fire every 4000ms 
    //   period [sec] = (1 / f_clock [sec]) * prescale * (count)
    //                  (1/16000000)  * 1024 * (count) = 4000 ms


    TCCR1B  = 0x00;        // Disable Timer1 while we set it up

    TCNT1H  = 11;          // Approx 4000ms when prescaler is set to 1024
    TCNT1L  = 0; 
    TIFR1   = 0x00;        // Timer1 INT Flag Reg: Clear Timer Overflow Flag
    TIMSK1  = 0x01;        // Timer1 INT Reg: Timer1 Overflow Interrupt Enable
    TCCR1A  = 0x00;        // Timer1 Control Reg A: Wave Gen Mode normal
    TCCR1B  = 0x05;        // Timer1 Control Reg B: Timer Prescaler set to 1024
}

void Timer1stop(void)
{
    TCCR1B = 0x00;
    TIMSK1 = 0x00;
}

/*** FUNC

Name:       Timer1 ISR

Function:   Handles the Timer1-overflow interrupt

FUNC ***/

ISR(TIMER1_OVF_vect) 
{    
    if (0 == timer1_f)
    {
      timer1_f = 1;
    }

    TCNT1H = 11;    // Approx 4000 ms - Reload
    TCNT1L = 0;
    TIFR1  = 0x00;    // timer1 int flag reg: clear timer overflow flag
};
