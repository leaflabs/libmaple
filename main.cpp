// Sample main.cpp file. Blinks the built-in LED, sends a message out
// USART2, and turns on PWM on pin 2.

#include "wirish.h"
#include "i2c.h"

static const uint8 slave_address = 0b1010001;

#define NR_ELEMENTS 64
uint8 buf0[NR_ELEMENTS + 2] = {0x0, 0x0};
uint8 buf1[] = {0x0, 0x0};
uint8 buf2[NR_ELEMENTS];

void setup() {
    i2c_msg msgs[3];
    uint32 i;

    pinMode(BOARD_LED_PIN, OUTPUT);

    i2c_master_enable(I2C1, 0);
    for (i = 0; i < sizeof buf0; i++) {
        buf0[i + 2] = i & 0xFF;
    }

#if 0
    /* Write some bytes */
    msgs[0].addr = slave_address;
    msgs[0].flags = 0;
    msgs[0].length = sizeof buf0;
    msgs[0].data = buf0;

    i2c_master_xfer(I2C1, msgs, 1);
    delay(5);
    return;
#endif

    msgs[1].addr = slave_address;
    msgs[1].flags = 0;
    msgs[1].length = sizeof buf1;
    msgs[1].data = buf1;

    msgs[2].addr = slave_address;
    msgs[2].flags = I2C_MSG_READ;
    msgs[2].length = sizeof buf2;
    msgs[2].data = buf2;
    i2c_master_xfer(I2C1, msgs + 1, 2);
#if 0
    for (i = 0; i < 256; i++) {
        /* Read it back  */
        buf1[1] = i;
        msgs[1].addr = slave_address;
        msgs[1].flags = 0;
        msgs[1].length = 2;
        msgs[1].data = buf1;

        msgs[2].addr = slave_address;
        msgs[2].flags = I2C_MSG_READ;
        msgs[2].length = 1;
        msgs[2].data = buf2;
        i2c_master_xfer(I2C1, msgs + 1, 2);
        delay(10);
    }
#endif
}

void loop() {
    toggleLED();
    delay(100);
}

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated object that need libmaple may fail.
__attribute__(( constructor )) void premain() {
    init();
}

int main(void) {
    setup();

    while (1) {
        loop();
    }
    return 0;
}
