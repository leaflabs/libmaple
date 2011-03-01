// Sample i2c master example for development i2c branch. Writes 0-63 to
// addresses 0-63 on a 24LC256 EEPROM, then reads them back.

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

    for (i = 0; i < sizeof buf0; i++) {
        buf0[i + 2] = i & 0xFF;
    }

    i2c_master_enable(I2C1, 0);

    /* Write some bytes */
    msgs[0].addr = slave_address;
    msgs[0].flags = 0;
    msgs[0].length = sizeof buf0;
    msgs[0].data = buf0;
    i2c_master_xfer(I2C1, msgs, 1);
    delay(5);

    /* Write slave address to read */
    msgs[1].addr = slave_address;
    msgs[1].flags = 0;
    msgs[1].length = 2;
    msgs[1].data = buf1;

    /* Repeated start condition, then read NR_ELEMENTS bytes back */
    msgs[2].addr = slave_address;
    msgs[2].flags = I2C_MSG_READ;
    msgs[2].length = sizeof buf2;
    msgs[2].data = buf2;
    i2c_master_xfer(I2C1, msgs + 1, 2);
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
