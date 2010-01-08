#include "wiring.h"
#include "HardwareSerial.h"
#include "wiring_math.h"
#include "usb.h"

int ledPin = 13;
int toggle=0;
void setup() {
//    pinMode(ledPin,OUTPUT);
//    Serial2.begin(9600);
}

void loop() {
    asm volatile("nop");
//    digitalWrite(ledPin,HIGH);
//    delay(200);
//    digitalWrite(ledPin,LOW);
//    delay(200);
//    Serial2.println("Hello world");
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
