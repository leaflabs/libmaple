// Toggles the built-in LED when the built in button
// on the Maple is pushed in. This uses the attachInterrupt function to
// setup the interrupt handler for the button being pressed.
//
// More about attachInterrupt:
// http://leaflabs.com/docs/lang/api/attachinterrupt.html
//

#include <wirish/wirish.h>

// LED is off by default
bool isLEDOn = false;

// Interrupt handler takes in nothing and returns nothing.
void interruptHandler() {
    // Set LED
    isLEDOn = !isLEDOn;
    digitalWrite(BOARD_LED_PIN, isLEDOn);

    // Delay slightly for switch debouncing.
    delay(20);
}

// Setup pin modes and the interrupt handler
void setup() {
    pinMode(BOARD_BUTTON_PIN, INPUT);
    pinMode(BOARD_LED_PIN, OUTPUT);

    attachInterrupt(BOARD_BUTTON_PIN, interruptHandler, RISING);
}

// Loop. Does nothing in this example.
void loop() {

}

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need libmaple may fail.
__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (true) {
        loop();
    }
    return 0;
}
