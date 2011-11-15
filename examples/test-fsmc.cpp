#include <stddef.h>             // for ptrdiff_t

#include <wirish/wirish.h>
#include <libmaple/fsmc.h>

#ifndef BOARD_maple_native
#error "Sorry, this example only works on Maple Native."
#endif

// Start of FSMC SRAM bank 1
static uint16 *const sram_start = (uint16*)0x60000000;
// End of Maple Native SRAM chip address space (512K 16-bit words)
static uint16 *const sram_end = (uint16*)0x60100000;

void test_single_write(void);
void test_all_addresses(void);

void setup() {
    pinMode(BOARD_LED_PIN, OUTPUT);
    digitalWrite(BOARD_LED_PIN, HIGH);

    SerialUSB.read();
    SerialUSB.println("*** Beginning RAM chip test");

    test_single_write();
    test_all_addresses();

    SerialUSB.println("Tests pass, finished.");
    SerialUSB.println("***\n");
}

void loop() {
}

void test_single_write() {
    uint16 *ptr = sram_start;
    uint16 tmp;

    SerialUSB.print("Writing 0x1234... ");
    *ptr = 0x1234;
    SerialUSB.println("Done.");

    SerialUSB.print("Reading... ");
    tmp = *ptr;
    SerialUSB.print("Done: 0x");
    SerialUSB.println(tmp, HEX);

    if (tmp != 0x1234) {
        SerialUSB.println("Mismatch; abort.");
        ASSERT(0);
    }
}

void test_all_addresses() {
    uint32 start, end;
    uint16 count = 0;
    uint16 *ptr;

    SerialUSB.println("Now writing all memory addresses (unrolled loop)");
    start = micros();
    for (ptr = sram_start; ptr < sram_end;) {
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
        *ptr++ = count++;
    }
    end = micros();
    SerialUSB.print("Done. Elapsed time (us): ");
    SerialUSB.println(end - start);

    SerialUSB.println("Validating writes.");
    for (ptr = sram_start, count = 0; ptr < sram_end; ptr++, count++) {
        uint16 value = *ptr;
        if (value != count) {
            SerialUSB.print("mismatch: 0x");
            SerialUSB.print((uint32)ptr);
            SerialUSB.print(" = 0x");
            SerialUSB.print(value, HEX);
            SerialUSB.print(", should be 0x");
            SerialUSB.print(count, HEX);
            SerialUSB.println(".");
            ASSERT(0);
        }
    }
    SerialUSB.println("Done; all writes seem valid.");

    ptrdiff_t nwrites = sram_end - sram_start;
    double us_per_write = double(end-start) / double(nwrites);
    SerialUSB.print("Number of writes = ");
    SerialUSB.print(nwrites);
    SerialUSB.print("; avg. time per write = ");
    SerialUSB.print(us_per_write);
    SerialUSB.print(" us (");
    SerialUSB.print(1 / us_per_write);
    SerialUSB.println(" MHz)");
}

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
