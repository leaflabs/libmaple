/**
 *  @brief General STM32 specific definitions
 */

#ifndef _STM32_H_
#define _STM32_H_

#ifdef MCU_STM32F100RB
    #define RCC_PLLMUL RCC_PLLMUL_3
    #define RCC_PLLMUL_VALUE 3
    #define DELAY_US_MULTIPLIER 8

    /* Where to put usercode, based on space reserved for bootloader. */
    #define USER_ADDR_ROM 0x08000000
#else
    #define RCC_PLLMUL RCC_PLLMUL_9
    #define RCC_PLLMUL_VALUE 9
    #define DELAY_US_MULTIPLIER 12
    #define USER_ADDR_ROM 0x08005000
#endif

#define USER_ADDR_RAM 0x20000C00
#define STACK_TOP     0x20000800

/* The operating frequency of the crystal */
#define HSO_FREQ_HZ 8000000UL

#ifndef CLOCK_SPEED_HZ
#define CLOCK_SPEED_HZ  (HSO_FREQ_HZ * RCC_PLLMUL_VALUE)
#endif

#ifndef PCLK1
#define PCLK1           (CLOCK_SPEED_HZ / 2)  /* RCC_APB1_HCLK_DIV_2 */
#endif
#ifndef PCLK2
#define PCLK2           CLOCK_SPEED_HZ        /* RCC_APB2_HCLK_DIV_1*/
#endif

#ifdef STM32_MEDIUM_DENSITY
    #define NR_INTERRUPTS 43
#else
#ifdef STM32_HIGH_DENSITY
    #define NR_INTERRUPTS 60
#else
#error "No STM32 board type defined!"
#endif
#endif

#endif

