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
*  To maintain compliance with Nordic Semiconductor ASA�s Bluetooth profile 
*  qualification listings, this section of source code must not be modified.
*/

/** @defgroup battery battery
* @{
* @ingroup services
*
* @brief battery service implementation.
* @details
* This module implements the battery service with characteristics : battery_level, battery_state and the aggregate of level and state.
*
* The level, in percent, is computed using @ref lib_battery_level by the function @ref update_battery.
*
*/
#include <stdint.h>

#ifndef BATTERY_H__
#define BATTERY_H__

#define BATTERY_LVL_CHANGE_THRESHOLD 2

/** @brief Function to check the battery.
 *  @details This function checks the battery's current level. Call this function on a regular basis to monitor the battery.
 *  @param percent_level Measured battery level in percent.
 */
void update_battery(aci_state_t *aci_stat, uint8_t percent_level);


/** @brief Battery's pipe_status event handler.
 *  @details Call this function on @c PipeStatusEvent.
 */
void battery_on_pipe_status(aci_state_t *aci_stat);

/** @brief Battery's connect event handler.
 *  @details Call this function on @c ConnectedEvent.
 *  @param percent_level Measured battery level in percent.
 */
void battery_on_connect(uint8_t percent_level);

/** @brief Battery's disconnect event handler.
 *  @details Call this function on @c DisconnectedEvent.
 *  @param percent_level Measured battery level in percent.
 */
void battery_on_disconnect(uint8_t percent_level);


#endif //BATTERY_DEMO_H__

//@}
