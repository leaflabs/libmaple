// Tests the "flush" Serial function

#include "wirish.h"

void setup() {
    /* Send a message out USART2  */
    Serial2.begin(9600);
    Serial2.println("Hello world!");
}

void loop() {
    Serial2.println("Waiting for multiple input...");
    while(Serial2.available() < 5) { }
    Serial2.println(Serial2.read());
    Serial2.println(Serial2.read());
    Serial2.flush();
    if(Serial2.available()) {
        Serial2.println("FAIL! Still had junk in the buffer...");
    }
}

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need libmaple may fail.
__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (1) {
        loop();
    }
    return 0;
}
