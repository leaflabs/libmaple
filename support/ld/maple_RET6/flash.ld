/*
 * STM32F103RET6 high density chip linker script for use with Maple
 * bootloader.  Loads to Flash.
 */

MEMORY
{
  ram (rwx) : ORIGIN = 0x20000C00, LENGTH = 61K
  rom (rx)  : ORIGIN = 0x08005000, LENGTH = 492K
}

GROUP(libcs3_stm32_high_density.a)

REGION_ALIAS("REGION_TEXT", rom);
REGION_ALIAS("REGION_DATA", ram);
REGION_ALIAS("REGION_BSS", ram);

INCLUDE common_rom.inc
