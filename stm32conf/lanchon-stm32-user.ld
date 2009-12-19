/* Linker script for STM32 (by Lanchon),
 * ROM and RAM relocated to their positions 
 * as placed by Maple bootloader
 *
 * Configure target memory and included script
 * according to your application requirements. */

/* Define memory spaces. */
MEMORY
{
  ram (rwx) : ORIGIN = 0x20000C00, LENGTH = 17K
  rom (rx) : ORIGIN = 0x08005000, LENGTH = 108K
}

/* Include the appropriate script.
 * Options:
 *   lanchon-stm32-rom.ld
 *   lanchon-stm32-rom-hosted.ld
 *   lanchon-stm32-ram.ld
 *   lanchon-stm32-ram-hosted.ld
 */
INCLUDE "lanchon-stm32-ram.ld"
