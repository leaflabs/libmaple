// Toggles the built-in LED when the built in button
// on the Maple is pushed in. This uses the attachInterrupt function to
// setup the interrupt handler for the button being pressed.
//
// This is similar to the exti-interrupt example, but shows the use of a class
// method to handle interrupts.
//
// More about attachInterrupt:
// http://leaflabs.com/docs/lang/api/attachinterrupt.html
//


#include <wirish/wirish.h>

class MyAwesomeClass {
public:
    // Setup the interrupt handler
    void initialize() {
        // LED is off by default
        this->isLEDOn = false;

        // Attach interrupt to class method handler
        attachInterrupt(BOARD_BUTTON_PIN, buttonInterruptHandler, this, RISING);
    }

private:

    bool isLEDOn;

    // Static event handler takes a void * argument that was originally
    // passed to the attachInterrupt call. If the argument in question is an
    // instance of the class (MyAwesomeClass in this case), the static function
    // get access to that instance's data (even private data).
    //
    // In other words, this setup allows the Maple to have class method
    // interrupt handlers (albeit with a work around).
    //
    // However, as you might imagine, this argument can be anything (if you
    // don't need instance data access).
    //
    static void buttonInterruptHandler(void *arg) {
        // Cast the "generic" void argument to the class instance.
        MyAwesomeClass *instance = (MyAwesomeClass *)arg;

        // Accessing private instance data
        instance->isLEDOn = !(instance->isLEDOn);

        // Set LED
        digitalWrite(BOARD_LED_PIN, instance->isLEDOn);

        // Delay slightly for switch de-bouncing
        delay(20);
    }
};

MyAwesomeClass myClass;

// Setup pin modes and the interrupt handler class
void setup() {
    pinMode(BOARD_BUTTON_PIN, INPUT);
    pinMode(BOARD_LED_PIN, OUTPUT);

    // The initialize method sets up the event handler to the private method
    // in MyAwesomeClass. There is however, nothing stopping you from setting
    // up event handlers which are public methods in classes.
    myClass.initialize();
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
