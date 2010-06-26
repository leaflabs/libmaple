// Sample main.cpp file. Blinks an LED, sends a message out USART2
// and turns on PWM on pin 2

#include "wirish.h"
#include "usb.h"

#define LED_PIN 13
#define PWM_PIN  2

void setup()
{
    /* Set up the LED to blink  */
    pinMode(LED_PIN, OUTPUT);

    /* Send a message out USART2  */
    Serial2.begin(9600);
    Serial2.println("Debugging DTR/RTS...");

}

int toggle = 0;

void loop() {
    toggle ^= 1;
    digitalWrite(LED_PIN, toggle);
    delay(100);
    Serial2.print("DTR: ");
    Serial2.print(usbGetDTR(), DEC);
    Serial2.print("\tRTS: ");
    Serial2.println(usbGetRTS(), DEC);
}

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated object that need libmaple may fail.
 __attribute__(( constructor )) void premain() {
    init();
}

int main(void)
{
    setup();

    while (1) {
        loop();
    }
    return 0;
}

