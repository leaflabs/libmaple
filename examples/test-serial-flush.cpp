/*
 * Tests the "flush" Serial function.
 */

#include "wirish.h"

#define COMM Serial1

void setup() {
    COMM.begin(9600);
    COMM.println("Hello world!");
}

void loop() {
    COMM.println("Waiting for multiple input...");
    while (COMM.available() < 5)
        ;
    COMM.println(COMM.read());
    COMM.println(COMM.read());
    COMM.flush();

    if (COMM.available()) {
        COMM.println("FAIL! Still had junk in the buffer...");
    }
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
