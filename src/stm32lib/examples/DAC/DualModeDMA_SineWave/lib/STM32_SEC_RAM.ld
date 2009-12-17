/*
Common part of the linker scripts for STR71x devices in RAM mode
(that is, the RAM is seen at 0 and we assume that the loader initializes it)
Copyright RAISONANCE 2005
You can use, modify and distribute thisfile freely, but without any waranty.
*/

/* Sections Definitions */

SECTIONS
{

    /* for Cortex devices, the beginning of the startup code is stored in the .isr_vector section, which goes to start of RAM */
    .isr_vector :
    {
	. = ALIGN(4);
        KEEP(*(.isr_vector))            /* Startup code */
	. = ALIGN(4);
    } >RAM
    
    /* for some STRx devices, the beginning of the startup code is stored in the .flashtext section, which goes to FLASH */
    .flashtext :
    {
	. = ALIGN(4);
        *(.flashtext)            /* Startup code */
	. = ALIGN(4);
    } >FLASH
 
    /* the program code is stored in the .text section, which goes to RAM */
    .text :
    {
	    . = ALIGN(4);
	    
        *(.text )                   /* remaining code */
        *(.glue_7)
        *(.glue_7t)

	    . = ALIGN(4);
    } >RAM
    
    /* This is the uninitialized data section. */
    .bss :
    {
	    . = ALIGN(4);
        _sbss = .;
        
        *(.bss)
        *(COMMON)
        
	    . = ALIGN(4);
	    _ebss = . ;
	    _etext = _ebss ;
	    
    } >RAM
    

    /* read-only data (constants) */
    .rodata  :
    {
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } > FLASH
    
    
    .idata  :
    {
    	_sidata = . ;
    } > FLASH
    
    
    /* This is the initialized data section. */
    .data  :  AT ( _sidata )
    {
	    . = ALIGN(4);
        _sdata = .;
        *(.data)
	    . = ALIGN(4);
	    _edata = . ;
    } >RAM
    
    

    PROVIDE ( end = _edata );
    PROVIDE ( _end = _edata );
    
    /* This is the user stack section 
    This is just to check that there is enough RAM left for the User mode stack
    It should generate an error if it's full.
     */
    ._usrstack :
    {
	    . = ALIGN(4);
        _susrstack = . ;
        
        . = . + _Minimum_Stack_Size ;
        
	    . = ALIGN(4);
        _eusrstack = . ;
    } >RAM
    

    __exidx_start = .;
    __exidx_end = .;
    
    /* after that it's only debugging information. */

    /* remove the debugging information from the standard libraries */
    /DISCARD/ :
    {
     libc.a ( * )
     libm.a ( * )
     libgcc.a ( * )
     }

    /* Stabs debugging sections.  */
    .stab          0 : { *(.stab) }
    .stabstr       0 : { *(.stabstr) }
    .stab.excl     0 : { *(.stab.excl) }
    .stab.exclstr  0 : { *(.stab.exclstr) }
    .stab.index    0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment       0 : { *(.comment) }
    /* DWARF debug sections.
       Symbols in the DWARF debugging sections are relative to the beginning
       of the section so we begin them at 0.  */
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
/*    .debug_info     0 : { * ( EXCLUDE_FILE ( *libc.a *libm.a ) .debug_info .gnu.linkonce.wi.*) }*/
    .debug_info     0 : { * ( .debug_info .gnu.linkonce.wi.*) }
/*    .debug_abbrev   0 : { *(EXCLUDE_FILE ( *libc.a *libm.a ) .debug_abbrev) }*/
    .debug_abbrev   0 : { *(.debug_abbrev) }
/*    .debug_line     0 : { *(EXCLUDE_FILE ( *libc.a *libm.a ) .debug_line) }*/
    .debug_line     0 : { *( .debug_line) }
    /*    (*(EXCLUDE_FILE (*crtend.o *otherfile.o) .ctors))    */
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }
    /* SGI/MIPS DWARF 2 extensions */
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames  0 : { *(.debug_varnames) }
}



