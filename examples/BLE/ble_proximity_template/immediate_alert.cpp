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
#include "lib_aci.h"
#include "services.h"
#include "alert_level_characteristic.h"
#include "immediate_alert.h"


void immediate_alert_pipes_updated_evt_rcvd(uint8_t pipe_num, uint8_t *buffer)
{
  switch (pipe_num)
  {
    case PIPE_IMMEDIATE_ALERT_ALERT_LEVEL_RX :
      immediate_alert_hook((alert_level_t)buffer[0]);
      break;
  }
}

/*  This function returns true if the immediate alert service is available at the master.
	The user of this function may decide take appropriate action (if needed) based of the
	return value of this function. */

bool is_immediate_alert_service_available_at_master(aci_state_t * aci_stat)
{
	return lib_aci_is_pipe_available(aci_stat, PIPE_IMMEDIATE_ALERT_ALERT_LEVEL_TX_1);

}
