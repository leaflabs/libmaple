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
#include "heart_rate.h"
#include "hrm_definitions.h"

static uint8_t heart_rate_data_buffer[HEART_RATE_DATA_BUFF_SIZE];
static uint8_t heart_rate_data_buff_insert_ptr;
static uint8_t heart_rate_data_buff_fetch_ptr;

static uint8_t current_heart_rate_data[HR_MAX_PAYLOAD];


void update_heart_rate(aci_state_t *aci_state, uint8_t heart_rate)
{
	if (lib_aci_is_pipe_available(aci_state, PIPE_HEART_RATE_HEART_RATE_MEASUREMENT_TX))
	{
		heart_rate_set_support_contact_bit();
		heart_rate_set_contact_status_bit();
		if(aci_state->data_credit_available > 0)
		{
			if (heart_rate_send_hr((uint8_t)heart_rate))
			{
				aci_state->data_credit_available--;
			}
		}
	}
}

uint8_t get_heart_rate_measurement(void)
{
	//YOUR JOB: insert code here to get data from actual heart rate sensor.
	
	return 0;
}

void init_heart_rate_data_buffers()
{
	int i;
	
	for(i=0;i<HEART_RATE_DATA_BUFF_SIZE;i++)
	{
		heart_rate_data_buffer[i] = NO_DATA;
	}
	heart_rate_data_buff_fetch_ptr = 0;
	heart_rate_data_buff_insert_ptr = 0;
}

uint8_t insert_data_into_heart_rate_buffer(uint8_t heart_rate)
{
	if(heart_rate_data_buffer[heart_rate_data_buff_insert_ptr] != NO_DATA)
	{
		return BUFFER_FULL;
	}
	else
	{
		heart_rate_data_buffer[heart_rate_data_buff_insert_ptr] = heart_rate;
		
		//Move data-buffer insert pointer location
		if(heart_rate_data_buff_insert_ptr == (HEART_RATE_DATA_BUFF_SIZE - 1))
			heart_rate_data_buff_insert_ptr = 0;
		else
			heart_rate_data_buff_insert_ptr++;
		
		return SUCCESS;
	}
}

uint8_t send_data_from_heart_rate_buffer(aci_state_t * aci_state)
{
	if(heart_rate_data_buffer[heart_rate_data_buff_fetch_ptr] == NO_DATA)
	{
		return BUFFER_EMPTY;
	}
	else
	{
		update_heart_rate(aci_state, heart_rate_data_buffer[heart_rate_data_buff_fetch_ptr]);    //Send data from the buffer over the air
		heart_rate_data_buffer[heart_rate_data_buff_fetch_ptr] = NO_DATA;                     //Erase the data from the buffer we just sent
		
		//Move data-buffer fetch pointer location
		if(heart_rate_data_buff_fetch_ptr == (HEART_RATE_DATA_BUFF_SIZE - 1))
			heart_rate_data_buff_fetch_ptr = 0;
		else
			heart_rate_data_buff_fetch_ptr++;
		
		return SUCCESS;
	}
}

void heart_rate_init()
{
  uint8_t i;
  for (i = 0; i < HR_MAX_PAYLOAD; i ++)
  {
    current_heart_rate_data[i] = 0;
  }
  init_heart_rate_data_buffers();
}

void heart_rate_set_support_contact_bit()
{
  current_heart_rate_data[0] |= HEART_RATE_FLAGS_T_SENSOR_CONTACT_SUPPORT;
}

void heart_rate_clear_support_contact_bit()
{
  current_heart_rate_data[0] &= ~HEART_RATE_FLAGS_T_SENSOR_CONTACT_SUPPORT;
}

void heart_rate_set_contact_status_bit()
{
  current_heart_rate_data[0] |= HEART_RATE_FLAGS_T_SENSOR_CONTACT_STATUS;
}

void heart_rate_clear_contact_status_bit()
{
  current_heart_rate_data[0] &= ~HEART_RATE_FLAGS_T_SENSOR_CONTACT_STATUS;
}

bool heart_rate_send_hr(uint8_t meas_hr)
{
  uint8_t data_index = 0;
  current_heart_rate_data[data_index] &= ~HEART_RATE_FLAGS_MEAS_SIZE_BIT;
  current_heart_rate_data[data_index] &= ~HEART_RATE_FLAGS_ENERGY_EXPENDED_STATUS_BIT;
  current_heart_rate_data[data_index] &= ~HEART_RATE_FLAGS_RR_INTERVAL_SUPPORT_BIT;
  data_index++;
  current_heart_rate_data[data_index++] = meas_hr;
  return lib_aci_send_data(PIPE_HEART_RATE_HEART_RATE_MEASUREMENT_TX,
                           (uint8_t *)&current_heart_rate_data[0] ,data_index);
}

bool heart_rate_send_hr_16bits(uint16_t meas_hr)
{
  uint8_t data_index = 0;
  current_heart_rate_data[data_index] |= HEART_RATE_FLAGS_MEAS_SIZE_BIT;
  current_heart_rate_data[data_index] &= ~HEART_RATE_FLAGS_ENERGY_EXPENDED_STATUS_BIT;
  current_heart_rate_data[data_index] &= ~HEART_RATE_FLAGS_RR_INTERVAL_SUPPORT_BIT;
  data_index++;
  current_heart_rate_data[data_index++] = (uint8_t)meas_hr;
  current_heart_rate_data[data_index++] = (uint8_t)(meas_hr>>8);
  return lib_aci_send_data(PIPE_HEART_RATE_HEART_RATE_MEASUREMENT_TX,
                           (uint8_t *)&current_heart_rate_data[0] ,data_index);
}

bool heart_rate_send_hr_expended_energy(uint8_t meas_hr, uint16_t expended_energy)
{
  uint8_t data_index = 0;
  current_heart_rate_data[data_index] &= ~HEART_RATE_FLAGS_MEAS_SIZE_BIT;
  current_heart_rate_data[data_index] |= HEART_RATE_FLAGS_ENERGY_EXPENDED_STATUS_BIT;
  current_heart_rate_data[data_index] &= ~HEART_RATE_FLAGS_RR_INTERVAL_SUPPORT_BIT;
  data_index++;
  current_heart_rate_data[data_index++] = meas_hr;
  current_heart_rate_data[data_index++] = (uint8_t)expended_energy;
  current_heart_rate_data[data_index++] = (uint8_t)(expended_energy>>8);
  return lib_aci_send_data(PIPE_HEART_RATE_HEART_RATE_MEASUREMENT_TX,
                           (uint8_t *)&current_heart_rate_data[0] ,data_index);
}

bool heart_rate_send_hr_16bits_expended_energy(uint16_t meas_hr, uint16_t expended_energy)
{
  uint8_t data_index = 0;
  current_heart_rate_data[data_index] |= HEART_RATE_FLAGS_MEAS_SIZE_BIT;
  current_heart_rate_data[data_index] |= HEART_RATE_FLAGS_ENERGY_EXPENDED_STATUS_BIT;
  current_heart_rate_data[data_index] &= ~HEART_RATE_FLAGS_RR_INTERVAL_SUPPORT_BIT;
  data_index++;
  current_heart_rate_data[data_index++] = (uint8_t)meas_hr;
  current_heart_rate_data[data_index++] = (uint8_t)(meas_hr>>8);
  current_heart_rate_data[data_index++] = (uint8_t)expended_energy;
  current_heart_rate_data[data_index++] = (uint8_t)(expended_energy>>8);
  return lib_aci_send_data(PIPE_HEART_RATE_HEART_RATE_MEASUREMENT_TX,
                           (uint8_t *)&current_heart_rate_data[0] ,data_index);
}

bool heart_rate_send_hr_rr_interval(uint8_t meas_hr, uint16_t *p_rr_intervals, uint8_t nb_intervals)
{
  uint8_t data_index = 0, i;
  current_heart_rate_data[data_index] &= ~HEART_RATE_FLAGS_MEAS_SIZE_BIT;
  current_heart_rate_data[data_index] |= HEART_RATE_FLAGS_RR_INTERVAL_SUPPORT_BIT;
  current_heart_rate_data[data_index] &= ~HEART_RATE_FLAGS_ENERGY_EXPENDED_STATUS_BIT;
  data_index++;
  current_heart_rate_data[data_index++] = meas_hr;
  for(i = 0; i < nb_intervals; i ++)
  {
    current_heart_rate_data[data_index++] = (uint8_t) (p_rr_intervals[i]);
    current_heart_rate_data[data_index++] = (uint8_t)((p_rr_intervals[i])>>8);
  }
  return lib_aci_send_data(PIPE_HEART_RATE_HEART_RATE_MEASUREMENT_TX,
                           (uint8_t *)&current_heart_rate_data[0] ,data_index);
}

bool heart_rate_send_hr_16bits_rr_interval(uint16_t meas_hr, uint16_t *p_rr_intervals, uint8_t nb_intervals)
{
  uint8_t data_index = 0, i;
  current_heart_rate_data[data_index] |= HEART_RATE_FLAGS_MEAS_SIZE_BIT;
  current_heart_rate_data[data_index] |= HEART_RATE_FLAGS_RR_INTERVAL_SUPPORT_BIT;
  current_heart_rate_data[data_index] &= ~HEART_RATE_FLAGS_ENERGY_EXPENDED_STATUS_BIT;
  data_index++;
  current_heart_rate_data[data_index++] = (uint8_t)meas_hr;
  current_heart_rate_data[data_index++] = (uint8_t)(meas_hr>>8);
  for(i = 0; i < nb_intervals; i ++)
  {
    current_heart_rate_data[data_index++] = (uint8_t) (p_rr_intervals[i]);
    current_heart_rate_data[data_index++] = (uint8_t)((p_rr_intervals[i])>>8);
  }
  return lib_aci_send_data(PIPE_HEART_RATE_HEART_RATE_MEASUREMENT_TX,
                           (uint8_t *)&current_heart_rate_data[0] ,data_index);
}

bool heart_rate_send_hr_expended_energy_rr_interval(uint8_t meas_hr, uint16_t expended_energy, uint16_t *p_rr_intervals, uint8_t nb_intervals)
{
  uint8_t data_index = 0, i;
  current_heart_rate_data[data_index] &= ~HEART_RATE_FLAGS_MEAS_SIZE_BIT;
  current_heart_rate_data[data_index] |= HEART_RATE_FLAGS_ENERGY_EXPENDED_STATUS_BIT;
  current_heart_rate_data[data_index] |= HEART_RATE_FLAGS_RR_INTERVAL_SUPPORT_BIT;
  data_index++;
  current_heart_rate_data[data_index++] = meas_hr;
  current_heart_rate_data[data_index++] = (uint8_t)expended_energy;
  current_heart_rate_data[data_index++] = (uint8_t)(expended_energy>>8);
  for(i = 0; i < nb_intervals; i ++)
  {
    current_heart_rate_data[data_index++] = (uint8_t) (p_rr_intervals[i]);
    current_heart_rate_data[data_index++] = (uint8_t)((p_rr_intervals[i])>>8);
  }
  return lib_aci_send_data(PIPE_HEART_RATE_HEART_RATE_MEASUREMENT_TX,
                           (uint8_t *)&current_heart_rate_data[0] ,data_index);
}

bool heart_rate_send_hr_16bits_expended_energy_rr_interval(uint16_t meas_hr, uint16_t expended_energy, uint16_t *p_rr_intervals, uint8_t nb_intervals)
{
  uint8_t data_index = 0, i;
  current_heart_rate_data[data_index] |= HEART_RATE_FLAGS_MEAS_SIZE_BIT;
  current_heart_rate_data[data_index] |= HEART_RATE_FLAGS_ENERGY_EXPENDED_STATUS_BIT;
  current_heart_rate_data[data_index] |= HEART_RATE_FLAGS_RR_INTERVAL_SUPPORT_BIT;
  data_index++;
  current_heart_rate_data[data_index++] = (uint8_t)meas_hr;
  current_heart_rate_data[data_index++] = (uint8_t)(meas_hr>>8);
  current_heart_rate_data[data_index++] = (uint8_t)expended_energy;
  current_heart_rate_data[data_index++] = (uint8_t)(expended_energy>>8);
  for(i = 0; i < nb_intervals; i ++)
  {
    current_heart_rate_data[data_index++] = (uint8_t) (p_rr_intervals[i]);
    current_heart_rate_data[data_index++] = (uint8_t)((p_rr_intervals[i])>>8);
  }
  return lib_aci_send_data(PIPE_HEART_RATE_HEART_RATE_MEASUREMENT_TX,
                           (uint8_t *)&current_heart_rate_data[0] ,data_index);
}

#ifdef PIPE_HEART_RATE_HEART_RATE_CONTROL_POINT_RX_ACK
void heart_rate_pipes_updated_evt_rcvd(aci_state_t *aci_stat, uint8_t pipe_num, uint8_t *buffer)
{
  switch (pipe_num)
  {
    case PIPE_HEART_RATE_HEART_RATE_CONTROL_POINT_RX_ACK :
      if (buffer[0] == HRCP_OPCODE_RESET_ENERY_EXPENDED)
      {
        lib_aci_send_ack(aci_stat, PIPE_HEART_RATE_HEART_RATE_CONTROL_POINT_RX_ACK);
        hook_for_resetting_energy_expended();
      }
      else
      {
        /* Value received is reserved for future use. Send error response*/
        lib_aci_send_nack(aci_stat, PIPE_HEART_RATE_HEART_RATE_CONTROL_POINT_RX_ACK, HRCP_ERR_CONTROL_POINT_NOT_SUPPORTED);
      }
      break;
    default:
      /* Do nothing*/
      break;
  }
}
#endif
