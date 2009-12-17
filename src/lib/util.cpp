#include "wiring.h"
#include "Serial.h"
#include "util.h"
#include "io.h"

#define ERROR_PIN        13

/* Required for C++ hackery */
extern "C" void __cxa_pure_virtual(void) {
    while(1)
        ;
}

/* Error assert + fade */
void _fail(const char* file, int line, const char* exp) {
    int32_t  slope   = 1;
    int32_t CC      = 0x0000;
    int32_t TOP_CNT = 0x02FF;
    int32_t i       = 0;

    Serial1.print("ERROR: FAILED ASSERT(");
    Serial1.print(exp);
    Serial1.print("): ");
    Serial1.print(file);
    Serial1.print(":");
    Serial1.println(line);

    while (1) {
        if (CC == TOP_CNT)  {
            slope = -1;
        } else if (CC == 0) {
            slope = 1;
        }

        if (i == TOP_CNT)  {
            CC += slope;
            i = 0;
        }

        if (i < CC) {
            digitalWrite(ERROR_PIN, HIGH);
        } else {
            digitalWrite(ERROR_PIN, LOW);
        }
        i++;
    }
}
