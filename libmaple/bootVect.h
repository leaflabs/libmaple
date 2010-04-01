/* *****************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Andrew Meyer.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * ****************************************************************************/


/**
 *  @file HardwareUsb.h
 *
 *  @brief Defines the maple boot vector structure
 */

#ifndef _BOOTVECT_H_
#define _BOOTVECT_H_

#define BOOTLOADER_VECT_TABLE ((uint32*)0x20000000)

#ifdef __cplusplus
extern "C"{
#endif

typedef void (*FuncPtr)(void);

typedef struct {
  FuncPtr serial_tx_cb;
  FuncPtr serial_rx_cb;
  FuncPtr serial_linecoding_cb;
  uint32* serial_count_in;
  uint32* serial_count_out;
  uint8* serial_buffer_out;
  void* linecoding;
  uint8 major_rev;
  uint8 minor_rev;
  void* usb_device_ptr;
  void* usb_local_obj_ptr;
} BootVectTable;

#ifdef __cplusplus
}
#endif

#endif // _BOOTVECT_H_
