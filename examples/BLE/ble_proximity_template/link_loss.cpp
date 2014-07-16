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


#include <hal_platform.h>
#include "alert_level_characteristic.h"
#include "services.h"
#include "lib_aci.h"
#include "link_loss.h"

/*link loss Service */
volatile alert_level_t alert_handle_on_link_loss;

void link_loss_init(void)
{
  alert_handle_on_link_loss = ALERT_LEVEL_NO_ALERT;
}

void proximity_disconect_evt_rcvd(uint8_t disconnect_reason)
{
  if ((DISCONNECT_REASON_CX_CLOSED_BY_PEER_DEVICE != disconnect_reason)&&(DISCONNECT_REASON_CX_CLOSED_BY_LOCAL_DEVICE != disconnect_reason))
  {
    link_loss_alert_hook(alert_handle_on_link_loss);
  }
}

void link_loss_pipes_updated_evt_rcvd(uint8_t pipe_num, uint8_t *buffer)
{
  switch (pipe_num)
  {
    case PIPE_LINK_LOSS_ALERT_ALERT_LEVEL_RX_ACK_AUTO :
      alert_handle_on_link_loss = (alert_level_t)buffer[0];
      break;
  }
}
