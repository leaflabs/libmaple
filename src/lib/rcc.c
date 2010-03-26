#include "libmaple.h"
#include "rcc.h"
#include "stm32f10x_flash.h"

#define RCC_BASE               0x40021000
#define RCC_CR                 (RCC_BASE + 0x0)
#define RCC_CFGR               (RCC_BASE + 0x4)
#define RCC_CIR                (RCC_BASE + 0x8)
#define RCC_APB2STR            (RCC_BASE + 0xC)
#define RCC_APB1RSTR           (RCC_BASE + 0x10)
#define RCC_AHBENR             (RCC_BASE + 0x14)
#define RCC_APB2ENR            (RCC_BASE + 0x18)
#define RCC_APB1ENR            (RCC_BASE + 0x1C)
#define RCC_BDCR               (RCC_BASE + 0x20)
#define RCC_CSR                (RCC_BASE + 0x24)
#define RCC_AHBSTR             (RCC_BASE + 0x28)
#define RCC_CFGR2              (RCC_BASE + 0x2C))

#define HSEON                 BIT(16)

#define HSERDY            *(volatile uint32_t*)(BITBAND_PERI(RCC_CR + 2, 0))

#define HPRE                          0x000000F0
#define PPRE                          0x00000700
#define PLLMUL                        0x002C0000
#define PLL_MUL_9                     0x001C0000
#define PLLSRC                        BIT(16)
#define SYSCLK_DIV_1                  (0x0 << 4)
#define HCLK_DIV_1                    0
#define HCLK_DIV_2                    0x00000400

#define PLLRDY                       BIT(25)
#define PLLON                         BIT(24)
#define PLL_INPUT_CLK_HSE             BIT(16)


static void set_ahb_prescaler(uint32_t divider) {
    uint32_t tmp = __read(RCC_CFGR);

    switch (divider) {
    case SYSCLK_DIV_1:
        tmp &= ~HPRE;
        tmp |= SYSCLK_DIV_1;
        break;
    default:
        ASSERT(0);
    }

    __write(RCC_CFGR, tmp);
}

static void set_apb1_prescaler(uint32_t divider) {
    uint32_t tmp = __read(RCC_CFGR);

    switch (divider) {
    case HCLK_DIV_2:
        tmp &= ~PPRE;
        tmp |= HCLK_DIV_2;
        break;
    default:
        ASSERT(0);
    }

    __write(RCC_CFGR, tmp);
}

static void set_apb2_prescaler(uint32_t divider) {
    uint32_t tmp = __read(RCC_CFGR);

    switch (divider) {
    case HCLK_DIV_1:
        break;
    default:
        ASSERT(0);
    }
}

static void pll_init(void) {
    uint32_t tmp;

    /* set pll multiplier to 9 */
    tmp = __read(RCC_CFGR);
    tmp &= ~PLLMUL;
    tmp |= PLL_MUL_9;

    /* set pll clock to be hse */
    tmp |= PLL_INPUT_CLK_HSE;
    __write(RCC_CFGR, tmp);

    /* turn on the pll  */
    __set_bits(RCC_CR, PLLON);

    while(!__get_bits(RCC_CR, PLLRDY)) {
        asm volatile("nop");
    }

    /* select pll for system clock source  */
    tmp = __read(RCC_CFGR);
    tmp &= ~0x3;
    tmp |= 0x2;
    __write(RCC_CFGR, tmp);

    while (__get_bits(RCC_CFGR, 0x00000008) != 0x8) {
        asm volatile("nop");
    }
}


void rcc_enable(uint32 p) {
}

void rcc_init(void) {


__set_bits(RCC_CR, HSEON);

    while (!HSERDY) {
        asm volatile("nop");
    }

      /* Enable Prefetch Buffer */
      FLASH_PrefetchBufferCmd( (u32)FLASH_PrefetchBuffer_Enable);

      /* Flash 2 wait state */
      FLASH_SetLatency(FLASH_Latency_2);

      set_ahb_prescaler(SYSCLK_DIV_1);
      set_apb1_prescaler(HCLK_DIV_2);
      set_apb2_prescaler(HCLK_DIV_1);

   pll_init();

    __set_bits(RCC_APB2ENR, BIT(2));
    __set_bits(RCC_APB2ENR, BIT(3));
    __set_bits(RCC_APB2ENR, BIT(4));
    __set_bits(RCC_APB2ENR, BIT(5));
}
