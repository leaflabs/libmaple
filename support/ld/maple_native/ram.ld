/*
 * Linker script for STM32.
 * STM32 high density chip linker script. Loads to RAM with Maple bootloader
 */

MEMORY
{
  ram (rwx) : ORIGIN = 0x20000C00, LENGTH = 61K
  rom (rx)  : ORIGIN = 0x08005000, LENGTH = 0K
}

/*
 * Use high density device vector table
 */
GROUP(libcs3_stm32_high_density.a)

REGION_ALIAS("REGION_TEXT", ram);
REGION_ALIAS("REGION_DATA", ram);
REGION_ALIAS("REGION_BSS", ram);

INCLUDE common_ram.inc
