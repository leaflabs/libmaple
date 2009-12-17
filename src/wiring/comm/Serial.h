#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <inttypes.h>
#include <Print.h>

class Serial : public Print {
    public:
        Serial();
        void begin(uint32_t);
        uint8_t available(void);
        int read(void);
        void flush(void);
        virtual void write(uint8_t);
        using Print::write;
};

extern Serial Serial1;
#endif

