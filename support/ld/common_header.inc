/* "Preamble" for linker scripts (such as common_rom.inc) */

OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
ENTRY(_start)
SEARCH_DIR(.)

/*
 * Link against libgcc, libc, and libm
 */
GROUP(libgcc.a libc.a libm.a)

/* These force the linker to search for particular symbols from
 * the start of the link process and thus ensure the user's
 * overrides are picked up
 */
INCLUDE names.inc

/* STM32 vector table. See stm32_vector_table.S  */
EXTERN(__cs3_stm32_vector_table)

/* libcs3 C start function. See cs3.h */
EXTERN(__cs3_start_c)

/* main entry point */
EXTERN(main)

/* Initial stack pointer value. */
EXTERN(__cs3_stack)
PROVIDE(__cs3_stack = __cs3_region_start_ram + LENGTH(ram));

/* Reset vector and chip reset entry point. See start.S */
EXTERN(_start)
PROVIDE(__cs3_reset = _start);

/* Beginning of the heap */
PROVIDE(__cs3_heap_start = _end);
