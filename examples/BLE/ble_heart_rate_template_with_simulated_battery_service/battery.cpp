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


#include "lib_aci.h"
#include "services.h"
#include "battery.h"

#define INVALID_BATTERY_LEVEL 0xFF

static uint8_t previous_battery_level      = INVALID_BATTERY_LEVEL;
static uint8_t battery_level_on_disconnect = INVALID_BATTERY_LEVEL;
static uint8_t percent_level_on_connect    = INVALID_BATTERY_LEVEL;
  
bool get_battery_evolution(uint8_t *diff, uint8_t curr_batt_level)
{
  bool is_discharging = false;
  
//  Serial.print(F("    Current battery level: "));
//  Serial.print(curr_batt_level);
//  Serial.print(F("    previous battery level: "));
//  Serial.println(previous_battery_level);
  if (curr_batt_level != previous_battery_level)
  {
    if (curr_batt_level < previous_battery_level)
    {
      *diff = previous_battery_level - curr_batt_level;
      is_discharging = true;
    }
    else
    {
      *diff = curr_batt_level - previous_battery_level;
      is_discharging = false;
    }
  }
  return (is_discharging);
}

void update_battery(aci_state_t *aci_stat, uint8_t percent_level)
{
  bool is_discharging = false;
  uint8_t level_difference = 0;
//  Serial.print(F("  Is discharging: "));
//  Serial.print(is_discharging);
//  Serial.print(F("    level_difference: "));
//  Serial.print(level_difference);
//  Serial.print(F("    BATTERY_LVL_CHANGE_THRESHOLD: "));
//  Serial.println(BATTERY_LVL_CHANGE_THRESHOLD);
  is_discharging = get_battery_evolution(&level_difference, percent_level);
  
  if (level_difference >= BATTERY_LVL_CHANGE_THRESHOLD)
  {
    //Serial.print(F("    Setting battery level ..."));
    lib_aci_set_local_data(aci_stat, PIPE_BATTERY_BATTERY_LEVEL_SET, &percent_level, sizeof(percent_level));
    if(lib_aci_is_pipe_available(aci_stat, PIPE_BATTERY_BATTERY_LEVEL_TX))
    {
      //Serial.print(F("    Sending battery level over the air ..."));
      if (lib_aci_send_data(PIPE_BATTERY_BATTERY_LEVEL_TX, &percent_level, sizeof(percent_level)))
      {
        aci_stat->data_credit_available--;
      }
    }
    previous_battery_level = percent_level;
  }  
}

void battery_on_pipe_status(aci_state_t *aci_stat)
{
  if (percent_level_on_connect != battery_level_on_disconnect)
  {
    if(lib_aci_is_pipe_available(aci_stat, PIPE_BATTERY_BATTERY_LEVEL_TX))
    {
      lib_aci_send_data(PIPE_BATTERY_BATTERY_LEVEL_TX, &percent_level_on_connect, sizeof(percent_level_on_connect));
    }
  }
}

void battery_on_connect(aci_state_t *aci_stat, uint8_t percent_level)
{
  percent_level_on_connect = percent_level;
  lib_aci_set_local_data(aci_stat, PIPE_BATTERY_BATTERY_LEVEL_SET, &percent_level, sizeof(percent_level));
}

void battery_on_disconnect(uint8_t percent_level)
{
  battery_level_on_disconnect = percent_level;
}
