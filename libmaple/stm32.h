/**
 *  @brief General STM32 specific definitions
 */

#ifndef _STM32_H_
#define _STM32_H_

#ifndef PCLK1
#define PCLK1   36000000U
#endif
#ifndef PCLK2
#define PCLK2   72000000U
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

/* MCU-specific configuration */
#if defined(MCU_STM32F103RB)
    /* e.g., LeafLabs Maple */

    /* Number of GPIO ports (GPIOA, GPIOB, etc.) */
    #define NR_GPIO_PORTS              4

    /* SRAM size, in bytes */
    #define SRAM_SIZE             0x5000

#elif defined(MCU_STM32F103ZE)
    /* e.g., LeafLabs Maple Native */

    #define NR_GPIO_PORTS              7
    #define SRAM_SIZE            0x10000

#elif defined(MCU_STM32F103CB)
    /* e.g., LeafLabs Maple Mini */

    /* Note that this is not, strictly speaking, true.  But only pins
       0 and 1 exist, and they're used for OSC on the Mini, so we'll
       live with this for now. */
    #define NR_GPIO_PORTS              3

    #define SRAM_SIZE             0x5000

#elif defined(MCU_STM32F103RE)
    /* e.g., LeafLabs Maple RET6 edition */

    #define NR_GPIO_PORTS              4
    #define SRAM_SIZE            0x10000

#else

#error "No MCU type specified. Add something like -DMCU_STM32F103RB "   \
       "to your compiler arguments (probably in a Makefile)."

#endif

#endif

