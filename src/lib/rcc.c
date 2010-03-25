#include "libmaple.h"
#include "rcc.h"

typedef struct RCC {
    volatile uint32 CR;
    volatile uint32 CFGR;
    volatile uint32 CIR;
    volatile uint32 APB2STR;
    volatile uint32 APB1RSTR;
    volatile uint32 AHBENR;
    volatile uint32 APB2ENR;
    volatile uint32 APB1ENR;
    volatile uint32 BDCR;
    volatile uint32 CSR;
} RCC;

void rcc_enable(uint32 p) {

}
