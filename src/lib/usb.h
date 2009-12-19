#ifndef _USB_H_
#define _USB_H_

#include <inttypes.h>
#include "util.h"
#include "cortexm3_macro.h"
#include "usb_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define USB_ISR_ADDR              (0x08000090)
#define USB_SERIAL_ENDP_TXADDR    ((uint32_t) 0xC0)
#define USB_SERIAL_ENDP_RXADDR    ((uint32_t) 0x110)
#define USB_SERIAL_ENDP_TX        ((uint16_t) 0x1)
#define USB_SERIAL_ENDP_RX        ((uint16_t) 0x3)
#define USB_SERIAL_BUF_SIZE       (0x40)

#define BOOTLOADER_VECT_TABLE ((uint32_t*)0x20000000)

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
} BootVectTable;

extern BootVectTable* bootVect;

void usb_lpIRQHandler(void);  
void usb_userToPMABufferCopy(u8  *pbUsrBuf,u16 wPMABufAddr,u16 wNBytes);
void usb_PMAToUserBufferCopy(u8  *pbUsrBuf,u16 wPMABufAddr,u16 wNBytes);
void usb_serialWriteStr(const char *outStr);
uint8_t usb_serialGetRecvLen();

#ifdef __cplusplus
} // extern "C"
#endif
#endif //_USB_H
