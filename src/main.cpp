#include "wiring.h"
#include "HardwareSerial.h"
#include "math.h"
#include "usb.h"

void setup();
void loop();

int ledPin = 13;


void setup()
{
    pinMode(ledPin, OUTPUT);
    Serial2.begin(9600);
    Serial2.println("setup start");

    pinMode(6, PWM);
    pwmWrite(6, 0x8000);

    Serial2.println("setup end");
}

int toggle = 0;

char* testMsg = "0123456\n";
void loop() {
    toggle ^= 1;
    digitalWrite(ledPin, toggle);
    delay(1000);

    usb_userToPMABufferCopy((u8*)testMsg,USB_SERIAL_ENDP_TXADDR,8);
    _SetEPTxCount(USB_SERIAL_ENDP_TX,8);
    _SetEPTxValid(USB_SERIAL_ENDP_TX);
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
