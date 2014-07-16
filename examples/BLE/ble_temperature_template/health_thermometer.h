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

#ifndef HEALTH_THERMOMETER_H
#define HEALTH_THERMOMETER_H
#include "date_time.h"
/** @file
 * @brief 
 */
 
/** @defgroup health_thermometer_service health_thermometer_service
* @{
* @ingroup services
*  
* @brief health_thermometer_service : temperature measurement structure and flags
* 
*/

/** Health Thermometer Flags */
/**HEALTH THERMOMETER FLAGS bit 0 Unit : if 0 then Celsius; if 1 Fahrenheit */
#define H_THERMOMETER_FLAGS_UNIT_BIT         0x01     
/**HEALTH THERMOMETER FLAGS bit 1 : if 0 then Time Stamp field not present; if 1 Time Stamp field present*/
#define H_THERMOMETER_FLAGS_T_STAMP_BIT      0x02     
/**HEALTH THERMOMETER FLAGS bit 2 : if 0 then Temperature Type field not present; if 1 Temperature Type field present*/
#define H_THERMOMETER_FLAGS_TYPE_BIT   0x04     
/**HEALTH THERMOMETER FLAGS bit 3 : RESERVED FOR FUTURE USE*/
#define H_THERMOMETER_FLAGS_RESERVED0_BIT         0x08     
/**HEALTH THERMOMETER FLAGS bit 4 : RESERVED FOR FUTURE USE*/
#define H_THERMOMETER_FLAGS_RESERVED1_BIT 0x10     
/**HEALTH THERMOMETER FLAGS bit 5 : RESERVED FOR FUTURE USE*/
#define H_THERMOMETER_FLAGS_RESERVED2_BIT            0x20     
/**HEALTH THERMOMETER FLAGS bit 6 : RESERVED FOR FUTURE USE*/
#define H_THERMOMETER_FLAGS_RESERVED3_BIT        0x40     
/**HEALTH THERMOMETER FLAGS bit 7 : RESERVED FOR FUTURE USE*/
#define H_THERMOMETER_FLAGS_RESERVED4_BIT        0x80     

typedef enum h_temp_type_t
{
    H_TYPE_NOT_INCLUDED                  = 0,
    H_TYPE_ARMPIT                        = 1,
    H_TYPE_BODY                          = 2,
    H_TYPE_EAR                           = 3,
    H_TYPE_FINGER                        = 4,
    H_TYPE_GASTRO_INTESTINAL_TRACT       = 5,
    H_TYPE_MOUTH                         = 6,
    H_TYPE_RECTUM                        = 7,
    H_TYPE_TOE                           = 8,
    H_TYPE_TYMPANUM                      = 9, 
}h_temp_type_t;


#define H_THERMOMETER_POS_YEAR_LSB 0
#define H_THERMOMETER_POS_YEAR_MSB 1
#define H_THERMOMETER_POS_MOUNTH   2
#define H_THERMOMETER_POS_DAY      3
#define H_THERMOMETER_POS_HOUR     4
#define H_THERMOMETER_POS_MINUTE   5
#define H_THERMOMETER_POS_SECOND   6
#define H_THERMOMETER_POS_TYPE_NO_TSTAMP 0
#define H_THERMOMETER_POS_TYPE_WITH_TSTAMP 7
#define H_THERMOMETER_POS_TEMP_LSB0 0
#define H_THERMOMETER_POS_TEMP_LSB1 1
#define H_THERMOMETER_POS_TEMP_MSB0 2
#define H_THERMOMETER_POS_TEMP_MSB1 3


/** Temperature measurement structure*/
typedef struct h_thermo_temp_measure_t
{
    uint8_t flags;
    uint8_t measurement[4];
    uint8_t time_type[8];
}h_thermo_temp_measure_t;

/** @brief Function to initialize health_thermometer service.
 *  @details Call this function at reset of the application to initialize all internal variables of Health Thermometer service.
 */
void health_thermometer_init();

/** @brief Function to set the unit to Celsius.
 *  @details Call this function to set the Unit bit of the flag byte to Celsius for the next temperature measurement.
 */
void health_thermometer_set_unit_c();

/** @brief Function to set the unit to Fahrenheit.
 *  @details Call this function to set the Unit bit of the flag byte to Fahrenheit for the next temperature measurement.
 */
void health_thermometer_set_unit_f();

/** @brief Function to send a temperature measurement without time_stamp.
 *  @details Call this function to send (indicate) a new temperature measurement.
 *  @param meas_temp Measured temperature to send.
 */
bool health_thermometer_send_measure(uint32_t meas_temp);

/** @brief Function to send a temperature measurement with time_stamp.
 *  @details Call this function to send (indicate) a new temperature measurement with a time_stamp.
 *  @param meas_temp Measured temperature to send.
 *  @param t_stamp Time stamp.
 */
bool health_thermometer_send_measure_with_t_stamp(uint32_t meas_temp, time_stamp_t *t_stamp);

/** @brief Function to set the temperature dynamic type (used in the temperature measurement characteristic field).
 *  @details Call this function to set and add a dynamic temperature measurement type to the next temperature measurement.
 *  @param in_type Type to use (if 0, the type field is not included).
 */
void health_thermometer_set_dynamic_type(h_temp_type_t in_type);
/** @} */

#endif // HEALTH_THERMOMETER_H
