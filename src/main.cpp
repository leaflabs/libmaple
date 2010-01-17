#include "wiring.h"
#include "HardwareSerial.h"
#include "wiring_math.h"
#include "HardwareUsb.h"
#include "usb.h"

int ledPin = 13;
void setup() {
    pinMode(ledPin, OUTPUT);
}

int toggle = 1;
void loop() {
    digitalWrite(ledPin, toggle);
    toggle ^= 1;
    delay(100);
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
