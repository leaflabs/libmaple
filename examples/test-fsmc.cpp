#include <stdio.h>
#include <stddef.h>

#include "wirish.h"
#include "fsmc.h"

#define LED       BOARD_LED_PIN

// Start of FSMC SRAM bank 1
static uint16 *const ptr_start = (uint16*)0x60000000;
// End of Maple Native SRAM chip address space (512K 16-bit words)
static uint16 *const ptr_end = (uint16*)0x60080000;
// For snprintf
static char buf[100];

void setup() {
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);

    Serial1.begin(115200);
    Serial1.println("Hello World!");

    Serial1.print("Initializing RAM chip... ");
    fsmc_native_sram_init();
    Serial1.println("Done.");
}

void test_single_write() {
    uint16 *ptr = ptr_start;
    uint16 tmp;

    Serial1.print("Writing 0x1234... ");
    *ptr = 0x1234;
    Serial1.println("Done.");

    Serial1.print("Reading... ");
    tmp = *ptr;
    Serial1.print("Done: 0x");
    Serial1.println(tmp, HEX);

    if (tmp != 0x1234) {
        Serial1.println("Mismatch, abort.");
        ASSERT(0);
    }
}

void test_all_addresses() {
    uint32 start, end;
    uint16 count = 0;
    uint16 *ptr;
    Serial1.println("Now writing all memory addresses (unrolled loop)");
    start = micros();
    for (ptr = ptr_start; ptr < ptr_end;) {
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
    Serial1.print("Done. Elapsed time (us): ");
    Serial1.println(end - start);

    Serial1.println("Validating writes.");
    for (ptr = ptr_start, count = 0; ptr < ptr_end; ptr++, count++) {
        if (*ptr != count) {
            snprintf(buf, sizeof buf, "mismatch: %p = 0x%xu, should be 0x%xu.",
                     ptr, *ptr, count);
            Serial1.println(buf);
            ASSERT(0);
        }
    }
    ptrdiff_t nwrites = ptr_end - ptr_start;
    double us_per_write = double(end-start) / double(nwrites);
    Serial1.println("Done; all writes seem valid.");
    snprintf(buf, sizeof buf,
             "Number of writes = %d; avg. time per write = %g us (%g MHz)",
             nwrites, us_per_write, 1 / us_per_write);
    Serial1.println(buf);
}

__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    test_single_write();
    test_all_addresses();

    Serial1.println("Tests pass, finished.");

    while (true)
        ;

    return 0;
}
