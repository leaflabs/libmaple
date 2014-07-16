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

/* Attention! 
*  To maintain compliance with Nordic Semiconductor ASA's Bluetooth profile 
*  qualification listings, this section of source code must not be modified.
*/

#include "hal_platform.h"
#include "lib_battery_level.h"


/*
The discharge curve for 6x Duracell Alkaline DC AA. It is non-linear.
Source:http://www.powerstream.com/AA-tests.htm
In this model it is split into 3 linear sections:
- Section 1: 9.0V - 8.4V = 100% - 91% (9% drop on 600 mV)
- Section 2: 8.4V - 6.6V = 91% - 7% (84% drop on 1800 mV)
- Section 3: 6.6V - 6.0V = 7% - 0% (7% drop on 600 mV)

These numbers are by no means accurate. Temperature and
load in the actual application is not accounted for! Also,
linearization is an approximate.
*/
uint8_t lib_battery_level_percent_alkaline_9_volt(float mvolts)
{
  uint8_t battery_level;
  float battery_level_temp;
  
  if (mvolts >= 9000)
  {
    battery_level = 100;
  }
  else if (mvolts > 8400)
  { 
    battery_level_temp = 9000 - mvolts;
    battery_level_temp = battery_level_temp / 600;
    battery_level_temp = battery_level_temp * 9;
    battery_level_temp = 100 - battery_level_temp;
    battery_level = (uint8_t) battery_level_temp;
  }
  else if (mvolts > 6600)
  {
    battery_level_temp = 8400 - mvolts;
    battery_level_temp = battery_level_temp / 1800;
    battery_level_temp = battery_level_temp * 84;
    battery_level_temp = 91 - battery_level_temp;
    battery_level = (uint8_t) battery_level_temp;
  }
  else if (mvolts > 6000)
  {
    battery_level_temp = 6600 - mvolts;
    battery_level_temp = battery_level_temp / 600;
    battery_level_temp = battery_level_temp * 7;
    battery_level_temp = 7 - battery_level_temp;
    battery_level = (uint8_t) battery_level_temp;  
  }
  else
  {
    battery_level = 0; 
  }

  return battery_level; 
}

/*
The discharge curve for CR2032 is non-linear. In this model it is split into
4 linear sections:
- Section 1: 3.0V - 2.9V = 100% - 42% (58% drop on 100 mV)
- Section 2: 2.9V - 2.74V = 42% - 18% (24% drop on 160 mV)
- Section 3: 2.74V - 2.44V = 18% - 6% (12% drop on 300 mV)
- Section 4: 2.44V - 2.1V = 6% - 0% (6% drop on 340 mV)

These numbers are by no means accurate. Temperature and
load in the actual application is not accounted for!
*/
uint8_t lib_battery_level_percent(uint16_t mvolts)
{
  uint16_t battery_level;

  if (mvolts >= 3000)
  {
    battery_level = 100;
  }
  else if (mvolts > 2900)
  {
    battery_level = 100 - ((3000 - mvolts) * 58) / 100;  
  }
  else if (mvolts > 2740)
  {
    battery_level = 42 - ((2900 - mvolts) * 24) / 160;  
  }
  else if (mvolts > 2440)
  {
    battery_level = 18 - ((2740 - mvolts) * 12) / 300;  
  }
  else if (mvolts > 2100)
  {
    battery_level = 6 - ((2440 - mvolts) * 6) / 340;
  }
  else
  {
    battery_level = 0; 
  }

  return (uint8_t)battery_level; 
}

