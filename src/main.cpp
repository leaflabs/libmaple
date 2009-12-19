#include "wiring.h"
#include "HardwareSerial.h"
#include "math.h"
#include "usb.h"

void setup();
void loop();

int ledPin = 13;
uint8_t bytes_in;

BootVectTable* mapleVect;

void usb_tx_cb(void) {
}

void usb_rx_cb(void) {
  bytes_in = usb_serialGetRecvLen();
}

void setup()
{
    pinMode(ledPin, OUTPUT);
    Serial2.begin(9600);
    Serial2.println("setup start");

    pinMode(6, PWM);
    pwmWrite(6, 0x8000);

    Serial2.println("setup end");

    mapleVect = (BootVectTable*)(BOOTLOADER_VECT_TABLE);
    mapleVect->serial_tx_cb = usb_tx_cb;
    mapleVect->serial_rx_cb = usb_rx_cb;
}


int toggle = 0;

char* testMsg = "0123456\n";
void loop() {
    toggle ^= 1;
    digitalWrite(ledPin, toggle);
    delay(1000);
    usb_serialWriteStr("blink...\n");

    if (bytes_in > 0) {
      int i;
      for (i=0;i<bytes_in;i++) {
	usb_serialWriteStr("b,");
      }
      bytes_in = 0;
      usb_serialWriteStr("\n");
    }
}


int main(void) {
    init();
    setup();

    while (1) {
        loop();
    }
    return 0;
}

/* Required for C++ hackery */
/* TODO: This really shouldn't go here... move it later
 * */
extern "C" void __cxa_pure_virtual(void) {
    while(1)
        ;
}
