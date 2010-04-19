/* insert license */

#include "descriptors.h"

USB_Descriptor_Device usbVcomDescriptor_Device = {
 bLength:              sizeof(USB_Descriptor_Device), 
 bDescriptorType:      USB_DESCRIPTOR_TYPE_DEVICE,
 bcdUSB:               0x0200,
 bDeviceClass:         USB_DEVICE_CLASS_CDC,
 bDeviceSubClass:      USB_DEVICE_SUBCLASS_CDC,
 bDeviceProtocol:      0x00,
 bMaxPacketSize0:      0x40,
 idVendor:             VCOM_ID_VENDOR,
 idProduct:            VCOM_ID_PRODUCT,
 bcdDevice:            0x0200,
 iManufacturer:        0x00,
 iProduct:             0x00,
 iSerialNumber:        0x00,
 bNumConfigurations:   0x01
};

USB_Descriptor_Configuration usbVcomDescriptor_Config = {
 Header:
   {
   bLength:                   sizeof(USB_Descriptor_Config_Header),
   bDescriptorType:           USB_DESCRIPTOR_TYPE_CONFIGURATION,
   wTotalLength:              sizeof(USB_Descriptor_Configuration),
   bNumInterfaces:            0x02,
   bConfigurationValue:       0x01,
   iConfiguration:            0x00,
   bmAttributes:              (USB_CONFIG_ATTR_BUSPOWERED | USB_CONFIG_ATT_SELF_POWERED),
   bMaxPower:                 USB_CONFIG_POWER_MA(100)
   },

 CCI_Interface:
   {
   bLength:                  sizeof(USB_Descriptor_Interface),
   bDescriptorType:          USB_DESCRIPTOR_TYPE_INTERFACE,
   bInterfaceNumber:         0x00,
   bAlternateSetting:        0x00,
   bNumEndpoints:            0x01,
   bInterfaceClass:          0x02,
   bInterfaceSubClass:       0x02,
   bInterfaceProtocol:       0x01,
   iInterface:               0x00
   },

 CDC_Functional_IntHeader:
   {
   bLength:                  sizeof(CDC_FUNCTIONAL_DESCRIPTOR(2)),
   bDescriptorType:          0x24,
   SubType:                  0x00,
   Data:                     {0x01, 0x10}
   },

 CDC_Functional_CallManagement:
   {
   bLength:                  sizeof(CDC_FUNCTIONAL_DESCRIPTOR(2)),
   bDescriptorType:          0x24,
   SubType:                  0x01,
   Data:                     {0x03, 0x01}
   },

 CDC_Functional_ACM:
   {
   bLength:                  sizeof(CDC_FUNCTIONAL_DESCRIPTOR(1)),
   bDescriptorType:          0x24,
   SubType:                  0x02,
   Data:                     {0x06}
   },

 CDC_Functional_Union:
   {
   bLength:                  sizeof(CDC_FUNCTIONAL_DESCRIPTOR(2)),
   bDescriptorType:          0x24,
   SubType:                  0x06,
   Data:                     {0x00, 0x01}
   },

 ManagementEndpoint: 
   {
   bLength:                 sizeof(USB_Descriptor_Endpoint),
   bDescriptorType:         USB_DESCRIPTOR_TYPE_ENDPOINT,
   bEndpointAddress:        CDC_NOTIFICATION_EPNUM,
   bmAttributes:            EP_TYPE_INTERRUPT,
   wMaxPacketSize:          CDC_NOTIFICATION_EPSIZE,
   bInterval:               0xFF
   },

 DCI_Interface:
   {
   bLength:                sizeof(USB_Descriptor_Interface),
   bDescriptorType:        USB_DESCRIPTOR_TYPE_INTERFACE,
   bInterfaceNumber:       0x01,
   bAlternateSetting:      0x00,
   bNumEndpoints:          0x02,
   bInterfaceClass:        0x0A,
   bInterfaceSubClass:     0x00,
   bInterfaceProtocol:     0x00,
   iInterface:             0x00
   }.

 DataOutEndpoint:
   {
   bLength:               sizeof(USB_Descriptor_Endpoint),
   bDescriptorType:       USB_DESCRIPTOR_TYPE_ENDPOINT,
   bEndpointAddress:      VCOM_RX_EPNUM,
   bmAttributes:          EP_TYPE_BULK,
   wMaxPacketSize:        VCOM_RX_EPSIZE,
   bInterval:             0x00
   },

 DataInPoiint:
   {
   bLength:               sizeof(USB_Descriptor_Endpoint),
   bDescriptorType:       USB_DESCRIPTOR_TYPE_ENDPOINT,
   bEndpointAddress:      VCOM_TX_EPNUM,
   bmAttributes:          EP_TYPE_BULK,
   wMaxPacketSize:        VCOM_TX_EPSIZE,
   bInterval:             0x00
   },
};
