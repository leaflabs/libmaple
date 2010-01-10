#include "wiring.h"
#include "HardwareSerial.h"
#include "wiring_math.h"
#include "HardwareUsb.h"
#include "usb.h"

//HardwareUsb USB;

int ledPin = 13;
void setup() {
    pinMode(ledPin,OUTPUT);
    Serial2.begin(9600);
    Serial3.begin(9600);
}

volatile int toggle = 1;

void loop() {
    digitalWrite(ledPin, toggle);
    toggle ^= 1;
    delay(500);
//    USB.print(millis());
//    USB.println("\r");
    Serial2.print(millis(), DEC);
    Serial3.print(millis(), DEC);
    Serial3.print(": ");
//    Serial3.print(USB.available(), DEC);
    Serial3.println();
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
