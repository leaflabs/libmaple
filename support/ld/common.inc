/*
 * Linker script for libmaple.
 *
 * Original author "lanchon" from ST forums, with modifications by LeafLabs.
 */

OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
ENTRY(_start)

/*
 * Link against libgcc, libc, and libm
 */
GROUP(libgcc.a libc.a libm.a)

/*
 * These force the linker to search for vector table symbols.
 *
 * These symbols vary by STM32 family (and also within families).
 * It's up to the build system to configure the link's search path
 * properly for the target MCU.
 */
INCLUDE vector_symbols.inc

/* STM32 vector table. */
EXTERN(__stm32_vector_table)

/* C runtime initialization function. */
EXTERN(start_c)

/* main entry point */
EXTERN(main)

/* Initial stack pointer value. */
EXTERN(__msp_init)
PROVIDE(__msp_init = ORIGIN(ram) + LENGTH(ram));

/* Reset vector and chip reset entry point */
EXTERN(_start)
PROVIDE(__exc_reset = _start);

/* Heap boundaries, for libmaple */
EXTERN(_lm_heap_start);
EXTERN(_lm_heap_end);

SECTIONS
{
    /* TODO pull out rodata and stick into separate sections  */
    .text :
      {
        _text = .;
        /*
         * STM32 vector table.  Leave this here.  Yes, really.
         */
        *(.stm32.interrupt_vector)

        /*
         * Program code and vague linking
         */
        *(.text .text.* .gnu.linkonce.t.*)
        *(.plt)
        *(.gnu.warning)
        *(.glue_7t) *(.glue_7) *(.vfp11_veneer)

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
      } > REGION_TEXT

    /*
     * End of text
     */
    .text.align :
      {
        . = ALIGN(8);
        _etext = .;
      } > REGION_TEXT

    /*
     * .ARM.exidx exception unwinding; mandated by ARM's C++ ABI
     */
    __exidx_start = .;
    .ARM.exidx :
      {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
      } > REGION_RODATA
    __exidx_end = .;

    /*
     * .data
     */
    .data :
      {
        . = ALIGN(8);
        _data = .;

        *(.got.plt) *(.got)
        *(.data .data.* .gnu.linkonce.d.*)

        . = ALIGN(8);
        _edata = .;
      } > REGION_DATA AT> REGION_RODATA

    /*
     * Read-only data
     */
    .rodata :
      {
        *(.rodata .rodata.* .gnu.linkonce.r.*)
        /* .USER_FLASH: We allow users to allocate into Flash here */
        *(.USER_FLASH)
        /* ROM image configuration; for C startup */
        . = ALIGN(4);
        _lm_rom_img_cfgp = .;
        LONG(LOADADDR(.data));
        /*
         * Heap: Linker scripts may choose a custom heap by overriding
         * _lm_heap_start and _lm_heap_end. Otherwise, the heap is in
         * internal SRAM, beginning after .bss, and growing towards
         * the stack.
         *
         * I'm shoving these here naively; there's probably a cleaner way
         * to go about this. [mbolivar]
         */
        _lm_heap_start = DEFINED(_lm_heap_start) ? _lm_heap_start : _end;
        _lm_heap_end   = DEFINED(_lm_heap_end) ? _lm_heap_end : __msp_init;
      } > REGION_RODATA

    /*
     * .bss
     */
    .bss :
      {
        . = ALIGN(8);
        _bss = .;
        *(.bss .bss.* .gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN (8);
        _ebss = .;
        _end = _ebss;
      } > REGION_BSS

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
