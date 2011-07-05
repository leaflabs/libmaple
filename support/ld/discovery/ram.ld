/*
 * Linker script for STM32.
 * STM32F103RBT6 medium density chip linker script. Loads to ram.
 */

/*
 * Define memory spaces.
 */
MEMORY
{
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 8K
  rom (rx)  : ORIGIN = 0x08000000, LENGTH = 0K
}

/*
 * Use medium density device vector table
 */
GROUP(libcs3_stm32_med_density.a)

REGION_ALIAS("REGION_TEXT", ram);
REGION_ALIAS("REGION_DATA", ram);
REGION_ALIAS("REGION_BSS", ram);

/*
 * Define the rest of the sections
 */
INCLUDE common_ram.inc
