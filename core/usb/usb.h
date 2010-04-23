/* insert license */

#ifndef __USB_H_
#define __USB_H_


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
  void usbSuspend(void);
  void usbResumeInit(void);
  void usbResume(RESUME_STATE);
  
  RESULT usbPowerOn(void);
  RESULT usbPowerOff(void);
  
  void usbDsbISR(void);
  void usbEnbISR(void);

  /* overloaded ISR routine, this is the main usb ISR */
  void usb_lpIRQHandler(void);

  void usbSendHello(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //_USB_H
