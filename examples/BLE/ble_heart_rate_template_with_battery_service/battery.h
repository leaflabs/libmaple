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

//Defines the battery level percentage change required to send value over the air.
#define BATTERY_LVL_CHANGE_THRESHOLD 1

/**BATTERY DATA BUFFER SIZE: Set to 0 to disable data buffering. If 0, battery data will be discarded when there is
* no data credit. If non 0, data will be inserted in FIFO buffer and sent whenever data credit is available.
*/
#define BATTERY_DATA_BUFF_SIZE 0

//Constants for voltage divider coupled to ADC. ADC and voltage divider is used for battery voltage measurement.
#define REFERNCE_VOLTAGE_MVOLT 1100           //Selected reference voltage of the ADC in millivolts
#define R1_RESISTANCE_KOHM 6490               //Value of R1 resistor in the coupled voltage divider
#define R2_RESISTANCE_KOHM 822                //Value of R2 resistor in the coupled voltage divider
#define BATTERY_AIN_PIN 0                     //Analog input pin to measure, pin A0 = 0, pin A1 = 1, etc
#define OFFSET_ERROR_CALIBRATION_FACTOR 2.15	//Factor to correct offset error of the ADC. Modify if needed.
#define GAIN_ERROR_CALIBRATION_FACTOR 0.9864	//Factor to correct gain error of the ADC. Modify if needed.

/** @brief Initializes the battery data buffers.
 */
void init_battery_data_buffers();

/** @brief Insert data into the battery data buffer if it is not full.
 *  @details Returns SUCCESS if data is inserted, otherwise BUFFER_FULL.
 */
uint8_t insert_data_into_battery_buffer(uint8_t battery_percent_level);

/** @brief Sends data over the air if there is any data in the battery data buffer.
 *  @details Returns SUCCESS if data is sent, otherwise BUFFER_EMPTY.
 */
uint8_t send_data_from_battery_buffer(aci_state_t * aci_state);

/** @brief Function to check the battery.
 *  @details This function checks the battery's current level. Call this function periodically to monitor the battery.
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

/** @brief Samples battery voltage and returns battery level as percentage.
 *  @details Uses the internal ADC to sample the battery voltage. Uses the internal 1.1V VBG voltage
 *  as reference for the AIN input voltage. Performs offset and gain error calibration. Returns
 *  battery level percentage
 */
uint8_t measure_battery(aci_state_t *aci_state);

/** @brief Prints out battery measurement data
 *  @details Prints out on the serial connection: 
 *  Timestamp for ADC sample (milliseconds)
 *  10 bit ADC output value
 *  Voltage on the sampled analog input pin (millivolts)
 *  Supply voltage (millivolts)
 *  Battery level (percentage) 
 */
void print_battery_measurement_data(void);

/** @brief Returns simulated battery level value
 *  @details Returns simulated battery level value in 
 *  percentage. The value is periodically incremented
 *  and decremented.
 */
uint8_t get_simulated_battery_value(void);


#endif //BATTERY_H__

//@}
