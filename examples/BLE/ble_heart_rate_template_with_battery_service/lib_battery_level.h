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

/** @file

@defgroup lib_battery_level lib_battery_level
@{
@ingroup lib

@brief Battery model that gives the battery level based on supply voltage
@details The model is based on the CR2032 coin cell battery. The nominal
voltage is 3.0 Volts. The voltage will drop as the battery drains.

 */


#ifndef LIB_BATTERY_LEVEL_H__
#define LIB_BATTERY_LEVEL_H__

#include "hal_platform.h"

/** @brief Calculates the battery level in percent based on supply voltage

@details The calculation is based on a linearized version of typical alcaline battery
discharge curve. 9.0V returns 100% battery level while the limit for power failure is
6.0V and is considered to be the lower boundary.

@param mvolts The supply voltage in mV (9000-6000).
@return Battery level in percent.

*/

uint8_t lib_battery_level_percent_alkaline_9_volt(float mvolts);

/** @brief Calculates the battery level in percent based on supply voltage

@details The calculation is based on a linearized version of the battery's discharge
curve. 3.0V returns 100% battery level while the limit for power failure is 2.1V and 
is considered to be the lower boundary.

@param mvolts The supply voltage in mV (9000-6000).
@return Battery level in percent.

*/
uint8_t lib_battery_level_percent(uint16_t mvolts);

#endif // LIB_BATTERY_LEVEL_H__

/** @} */
