/* *****************************************************************************
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ****************************************************************************/

/**
 *  @file HardwareUsb.h
 *
 *  @brief Defines the maple boot vector structure
 */

#ifndef _BOOTVECT_H_
#define _BOOTVECT_H_

#define BOOTLOADER_VECT_TABLE ((uint32_t*)0x20000000)

#ifdef __cplusplus
extern "C"{
#endif

typedef void (*FuncPtr)(void);

typedef struct {
  FuncPtr serial_tx_cb;
  FuncPtr serial_rx_cb;
  FuncPtr serial_linecoding_cb;
  uint32_t* serial_count_in;
  uint32_t* serial_count_out;
  uint8_t* serial_buffer_out;
  void* linecoding;
  uint8_t major_rev;
  uint8_t minor_rev;
  void* usb_device_ptr;
  void* usb_local_obj_ptr;
} BootVectTable;

#ifdef __cplusplus
}
#endif

#endif // _BOOTVECT_H_
