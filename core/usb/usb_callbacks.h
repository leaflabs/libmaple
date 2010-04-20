#define SET_LINE_CODING        0x20
#define GET_LINE_CODING        0x21
#define SET_CONTROL_LINE_STATE 0x22
#define CONTROL_LINE_DTR       (1 << 0)
#define CONTROL_LINE_RTS       (1 << 1)

typedef struct {
  uint32 bitrate;
  uint8  format;
  uint8  paritytype;
  uint8  datatype;
} USB_Line_Coding;

void vcomDataTxCb(void);
void vcomDataRxCb(void);
void vcomManagementCb(void);

u8* vcomGetSetLineCoding(uint16 length);
void vcomSetLineSate(uint16 wValue);

void usbInit(void);
/* internal functions (as per the usb_core pProperty structure) */
void usbInit(void);
void usbReset(void);
void usbStatusIn(void);
void usbStatusOut(void);

RESULT usbDataSetup(u8 request);
RESULT usbNoDataSetup(u8 request);
RESULT usbGetInterfaceSetting(u8,u8);

u8* usbGetDeviceDescriptor(u16 length);
u8* usbGetConfigDescriptor(u16 length);
u8* usbGetStringDescriptor(u16 length);
u8* usbGetFunctionalDescriptor(u16 length);

/* internal callbacks to respond to standard requests */
void usbGetConfiguration(void);
void usbSetConfiguration(void);
void usbGetInterface(void);
void usbSetInterface(void);
void usbGetStatus(void);
void usbClearFeature(void);
void usbSetEndpointFeature(void);
void usbSetDeviceFeature(void);
void usbSetDeviceAddress(void);

