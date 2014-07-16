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

#ifndef LINK_LOSS_H
#define LINK_LOSS_H

 
/** @defgroup link_loss link_loss
* @{
* @ingroup services
*  
* @brief Link Loss Service (for proximity profile) implementation.
* 
* 
*/


#include <stdint.h>
#include "alert_level_characteristic.h"

/** @brief Callback on link_loss alert.
 *  @details This function is called when a link loss alert characteristic value is updated. 
 *  Implement this function to have your application behave according to the alert level of the link loss alert.
 *  @param level Level of the link_loss alert (see @ref alert_level_characteristic to view possible values).
 */
extern void link_loss_alert_hook(alert_level_t level);


/** Function to be initialize the link_loss service (set the alert on link_loss to NO_ALERT).*/
void link_loss_init(void);


/** @brief Function to handle disconnect event.
 *  @details Call this function on the ACI_EVT_DISCONNECTED event. This function checks the reason for disconnect 
 *  and if it matches a link loss situation, triggers a link_loss event.
 *  @param disconnect_reason Reason for disconnect event (given with the disconnect event).
 */
void proximity_disconect_evt_rcvd(uint8_t disconnect_reason);

/** @brief Function to handle reception of data for link_loss.
 *  @details Call this function on the ACI_EVT_DATA_RECEIVED event. This function checks if the data received is for link_loss.
 *  If so, it memorizes the alert level received to use it for the next link_loss event.
 *  @param pipe_num Pipe which has received data.
 *  @param buffer Pointer to the received data.
 */
void link_loss_pipes_updated_evt_rcvd(uint8_t pipe_num, uint8_t *buffer);


/** @} */

#endif //LINK_LOSS_H
