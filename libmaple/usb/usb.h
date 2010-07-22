/* insert license */

#ifndef __USB_H
#define __USB_H


#include "usb_lib.h"
#include "libmaple.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum 
  {
    RESUME_EXTERNAL,
    RESUME_INTERNAL,
    RESUME_LATER,
    RESUME_WAIT,
    RESUME_START,
    RESUME_ON,
    RESUME_OFF,
    RESUME_ESOF
  } RESUME_STATE;

typedef enum 
  {
    UNCONNECTED,
    ATTACHED,
    POWERED,
    SUSPENDED,
    ADDRESSED,
    CONFIGURED
  } DEVICE_STATE;

  extern volatile uint32 bDeviceState;

  void setupUSB(void);
  void disableUSB(void);
  void usbSuspend(void);
  void usbResumeInit(void);
  void usbResume(RESUME_STATE);
  
  RESULT usbPowerOn(void);
  RESULT usbPowerOff(void);
  
  void usbDsbISR(void);
  void usbEnbISR(void);

  /* overloaded ISR routine, this is the main usb ISR */
  void usb_lpIRQHandler(void);
  void usbWaitReset(void);

  /* blocking functions for send/receive */
  uint16 usbSendBytes(uint8* sendBuf,uint16 len);
  uint8 usbBytesAvailable(void);
  uint8 usbReceiveBytes(uint8* recvBuf, uint8 len);
  uint8 usbGetDTR(void);
  uint8 usbGetRTS(void);
  uint8 usbIsConnected(void);
  uint8 usbIsConfigured(void);
  uint16 usbGetPending(void);

  void usbSendHello(void);


#ifdef __cplusplus
} // extern "C"
#endif

#endif //_USB_H
