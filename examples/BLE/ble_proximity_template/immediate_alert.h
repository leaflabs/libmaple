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

#include <stdint.h>
#include "alert_level_characteristic.h"

/** @defgroup immediate_alert immediate_alert
* @{
* @ingroup services
*  
* @brief immediate_alert service implementation.
* 
* 
*/

#ifndef IMMEDIATE_ALERT_H__
#define IMMEDIATE_ALERT_H__

/** @brief Callback on immediate alert.
 *  @details This function is called when an immediate alert characteristic value is updated. 
 *  Implement this function to have your application behave according to the alert level of the immediate alert.
 *  @param level : Level of the immediate alert (see @ref alert_level_characteristic to view possible values).
 */
extern void immediate_alert_hook(alert_level_t level);

/** @brief Function to handle reception of data for immediate_alert.
 *  @details Call this function on the ACI_EVT_DATA_RECEIVED event. This function checks if the data received is for immediate_alert.
 *  If so it triggers the immediate alert with the received level.
 *  @param pipe_num Pipe which has received data.
 *  @param buffer Pointer to the received data.
 */
void immediate_alert_pipes_updated_evt_rcvd(uint8_t pipe_num, uint8_t *buffer);

/** @brief Function to check if the immediate alert service is available at master side.
 *  @details Returns the return value of lib_aci_is_pipe_available(PIPE_IMMEDIATE_ALERT_ALERT_LEVEL_TX_1).
 */
bool is_immediate_alert_service_available_at_master(aci_state_t * aci_stat);
#endif//IMMEDIATE_ALERT_H__
/** @} */

