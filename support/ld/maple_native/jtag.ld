/*
 * Linker script for STM32.
 * STM32 high density chip linker script. Bare metal linker script.
 */
MEMORY
{
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
  rom (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
}

/*
 * Use high density device vector table
 */
GROUP(libcs3_stm32_high_density.a)

REGION_ALIAS("REGION_TEXT", rom);
REGION_ALIAS("REGION_DATA", ram);
REGION_ALIAS("REGION_BSS", ram);

INCLUDE common_rom.inc

