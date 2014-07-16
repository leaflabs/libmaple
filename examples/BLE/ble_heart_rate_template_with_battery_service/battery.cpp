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


#include "lib_aci.h"
#include "services.h"
#include "battery.h"
#include "lib_battery_level.h"
#include "hrm_definitions.h"

static uint8_t battery_data_buffer[BATTERY_DATA_BUFF_SIZE];
static uint8_t batt_data_buff_insert_ptr;
static uint8_t batt_data_buff_fetch_ptr;

static uint32_t ADC_output_value;
static float calculated_mvolts;
static float AIN_mvolts;
static float supply_mvolts;
static uint8_t battery_perc_level;

static uint32_t timestamp;

static uint8_t batt_percentage_simulated = 100;
static uint8_t previous_battery_level      = NO_DATA;
static uint8_t battery_level_on_disconnect = NO_DATA;
static uint8_t percent_level_on_connect    = NO_DATA;

void init_battery_data_buffers()
{
	int i;
	
	for(i=0;i<BATTERY_DATA_BUFF_SIZE;i++)
	{
		battery_data_buffer[i] = NO_DATA;
	}
	batt_data_buff_fetch_ptr = 0;
	batt_data_buff_insert_ptr = 0;
}

uint8_t insert_data_into_battery_buffer(uint8_t battery_percent_level)
{
	if(battery_data_buffer[batt_data_buff_insert_ptr] != NO_DATA)
	{
		return BUFFER_FULL;
	}
	else
	{
		battery_data_buffer[batt_data_buff_insert_ptr] = battery_percent_level;
		
		//Move data-buffer insert pointer location
		if(batt_data_buff_insert_ptr == (BATTERY_DATA_BUFF_SIZE - 1)) 
			batt_data_buff_insert_ptr = 0;
		else
			batt_data_buff_insert_ptr++;
			
		return SUCCESS;
	}	
}

uint8_t send_data_from_battery_buffer(aci_state_t * aci_state)
{
		if(battery_data_buffer[batt_data_buff_fetch_ptr] == NO_DATA)
		{
			return BUFFER_EMPTY;
		}
		else
		{	
			update_battery(aci_state, battery_data_buffer[batt_data_buff_fetch_ptr]);    //Send data from the buffer over the air
			battery_data_buffer[batt_data_buff_fetch_ptr] = NO_DATA;                     //Erase the data from the buffer we just sent
			
			//Move data-buffer fetch pointer location
			if(batt_data_buff_fetch_ptr == (BATTERY_DATA_BUFF_SIZE - 1))
				batt_data_buff_fetch_ptr = 0;
			else
				batt_data_buff_fetch_ptr++;
				
			return SUCCESS;
		}
}
 
bool get_battery_evolution(uint8_t *diff, uint8_t curr_batt_level)
{
  bool is_discharging = false;
  
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

uint8_t measure_battery(aci_state_t *aci_state)
{
  analogReference(INTERNAL);                            //Set the ADC reference as the 1.1V internal band gap voltage
  delay(2);                                             //Create small delay to allow the reference voltage to settle before sampling
  ADC_output_value = analogRead(BATTERY_AIN_PIN);       //sample 10 bit battery measurement
  timestamp = millis();                                 //Mark timestamp for the ADC sampling.
  calculated_mvolts = ((float)ADC_output_value)/1023*REFERNCE_VOLTAGE_MVOLT;  //transform sample value into millivolts At AIN
  calculated_mvolts += OFFSET_ERROR_CALIBRATION_FACTOR; //Calibration for observed ADC offset error. Modify as needed.
  calculated_mvolts *= GAIN_ERROR_CALIBRATION_FACTOR;   //Calibration for observed ADC gain error. Modify as needed.
  AIN_mvolts = calculated_mvolts;                       //Store the voltage value on the analog input pin 
  supply_mvolts = calculated_mvolts * (R2_RESISTANCE_KOHM + R1_RESISTANCE_KOHM) / R2_RESISTANCE_KOHM;  //Calculate the supply voltage
  
  //transform millivolt measurement into percent value. Only suitable for 6x1.5V=9V alkaline battery.
  //Battery level transfer function may be inaccurate. Modify as needed.
  battery_perc_level = lib_battery_level_percent_alkaline_9_volt(supply_mvolts);   
  
  return battery_perc_level;
}

uint8_t get_simulated_battery_value(void)
{
	batt_percentage_simulated--;
	if(batt_percentage_simulated < 1)
	{
		batt_percentage_simulated = 100;
	}
	return batt_percentage_simulated;
}

void print_battery_measurement_data(void)
{
	//Print ADC value, AIN voltage, Supply voltage and battery level
	Serial.print(F("Time: "));
	Serial.print(timestamp);
	Serial.print(F("ms    ADC value (10 bit): "));
	Serial.print(ADC_output_value);
	Serial.print(F("    AIN voltage: "));
	Serial.print(AIN_mvolts);
	Serial.print(F("mV    Supply voltage: "));
	Serial.print(supply_mvolts);
	Serial.print(F("mV    Battery level: "));
	Serial.print(battery_perc_level);
	Serial.println(F("%"));	
}

void send_battery_update(aci_state_t *aci_state, uint8_t percent_level)
{
  if (lib_aci_send_data(PIPE_BATTERY_BATTERY_LEVEL_TX, &percent_level, sizeof(percent_level)))        //Sending battery level over the air
  {
    aci_state->data_credit_available--;
  }
}


void update_battery(aci_state_t * aci_state, uint8_t percent_level)
{
  uint8_t level_difference = 0;
  get_battery_evolution(&level_difference, percent_level);
  
  if (level_difference >= BATTERY_LVL_CHANGE_THRESHOLD)
  {
    lib_aci_set_local_data(aci_state, PIPE_BATTERY_BATTERY_LEVEL_SET, &percent_level, sizeof(percent_level));   //Set battery level
    previous_battery_level = percent_level;
	
    if(lib_aci_is_pipe_available(aci_state, PIPE_BATTERY_BATTERY_LEVEL_TX))
    {
      if(aci_state->data_credit_available > 0)
      {
		send_battery_update(aci_state, percent_level);
      }
    }    
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
