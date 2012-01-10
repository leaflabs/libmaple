/*
 * STM3220G-EVAL (STM32F207IGH6) linker script for JTAG (bare metal,
 * no bootloader) builds.
 */

MEMORY
{
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
  rom (rx)  : ORIGIN = 0x08000000, LENGTH = 1024K
}

REGION_ALIAS("REGION_TEXT", rom);
REGION_ALIAS("REGION_DATA", ram);
REGION_ALIAS("REGION_BSS", ram);
REGION_ALIAS("REGION_RODATA", rom);

INCLUDE common.inc
