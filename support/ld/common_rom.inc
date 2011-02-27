/* Linker script for STM32 (by Lanchon with Mods by LeafLabs) */

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
PROVIDE(__cs3_stack = __cs3_region_start_ram + __cs3_region_size_ram);

/* Reset vector and chip reset entry point. See start.S */
EXTERN(_start)
PROVIDE(__cs3_reset = _start);

/* Beginning of the heap */
PROVIDE(__cs3_heap_start = _end);

/* End of the heap */
PROVIDE(__cs3_heap_end = __cs3_region_start_ram + LENGTH(ram));


SECTIONS
{
  .text :
      {
        CREATE_OBJECT_SYMBOLS
        __cs3_region_start_rom = .;
        *(.cs3.region-head.rom)

        /*
         * STM32 vector table
         */
        __cs3_interrupt_vector = __cs3_stm32_vector_table;
        *(.cs3.interrupt_vector)
        /* Make sure we pulled in an interrupt vector.  */
        ASSERT (. != __cs3_stm32_vector_table, "No interrupt vector");

        *(.rom)
        *(.rom.b)

        /*
         * Program code and vague linking
         */
        *(.rom)
        *(.rom.b)
        *(.text .text.* .gnu.linkonce.t.*)
        *(.plt)
        *(.gnu.warning)
        *(.glue_7t) *(.glue_7) *(.vfp11_veneer)

        *(.rodata .rodata.* .gnu.linkonce.r.*)

        *(.ARM.extab* .gnu.linkonce.armextab.*)
        *(.gcc_except_table)
        *(.eh_frame_hdr)
        *(.eh_frame)

        . = ALIGN(4);
        KEEP(*(.init))

        . = ALIGN(4);
        __preinit_array_start = .;
        KEEP (*(.preinit_array))
        __preinit_array_end = .;

        . = ALIGN(4);
        __init_array_start = .;
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        __init_array_end = .;

        . = ALIGN(0x4);
        KEEP (*crtbegin.o(.ctors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
        KEEP (*(SORT(.ctors.*)))
        KEEP (*crtend.o(.ctors))

        . = ALIGN(4);
        KEEP(*(.fini))

        . = ALIGN(4);
        __fini_array_start = .;
        KEEP (*(.fini_array))
        KEEP (*(SORT(.fini_array.*)))
        __fini_array_end = .;

        KEEP (*crtbegin.o(.dtors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
        KEEP (*(SORT(.dtors.*)))
        KEEP (*crtend.o(.dtors))

        . = ALIGN(4);
        __cs3_regions = .;
        LONG (0)
        LONG (__cs3_region_init_ram)
        LONG (__cs3_region_start_ram)
        LONG (__cs3_region_init_size_ram)
        LONG (__cs3_region_zero_size_ram)
      } > REGION_TEXT

  /*
   * .ARM.exidx exception unwinding
   */
  __exidx_start = .;
  .ARM.exidx :
      {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
      } > REGION_TEXT
  __exidx_end = .;

  /*
   * End of text
   */
  .text.align :
      {
        . = ALIGN(8);
        _etext = .;
      } > REGION_TEXT

   /* expose a custom rom only section */
  .USER_FLASH :
  {
    *(.USER_FLASH)
  } >rom

   /* __cs3_region_end_rom is deprecated */
   __cs3_region_end_rom = __cs3_region_start_rom + LENGTH(rom);
   __cs3_region_size_rom = LENGTH(rom);
   __cs3_region_num = 1;

  /*
   * Start of data
   */
  .data :
      {
        ram_begin = DEFINED(RAM_BUILD) ? . : . ;
        *(.cs3.region-head.ram_begin)

        __cs3_region_start_ram = .;
        *(.cs3.region-head.ram)

        KEEP(*(.jcr))
        *(.got.plt) *(.got)
        *(.shdata)
        *(.data .data.* .gnu.linkonce.d.*)
        *(.ram)
        . = ALIGN (8);
        _edata = .;
      } > REGION_DATA AT> REGION_TEXT

  .bss :
      {
        *(.shbss)
        *(.bss .bss.* .gnu.linkonce.b.*)
        *(COMMON)
        *(.ram.b)
        . = ALIGN (8);
        _end = .;
        __end = .;
      } > REGION_BSS AT> REGION_TEXT

  /* __cs3_region_end_ram is deprecated */
  __cs3_region_end_ram = __cs3_region_start_ram + LENGTH(ram);
  __cs3_region_size_ram = LENGTH(ram);
  __cs3_region_init_ram = LOADADDR (.data);
  __cs3_region_init_size_ram = _edata - ADDR (.data);
  __cs3_region_zero_size_ram = _end - _edata;
  __cs3_region_num = 1;

  /*
   * Debugging sections
   */
  .stab 0 (NOLOAD) : { *(.stab) }
  .stabstr 0 (NOLOAD) : { *(.stabstr) }
  /* DWARF debug sections.
   * Symbols in the DWARF debugging sections are relative to the beginning
   * of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }

  .note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
  .ARM.attributes 0 : { KEEP (*(.ARM.attributes)) }
  /DISCARD/ : { *(.note.GNU-stack) }
}
