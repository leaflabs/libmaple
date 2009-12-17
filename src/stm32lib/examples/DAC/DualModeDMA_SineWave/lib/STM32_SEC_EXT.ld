/*
Common part of the linker scripts for STR71x devices in EXT mode
(that is, the EXT is seen at 0)
Copyright RAISONANCE 2005
You can use, modify and distribute thisfile freely, but without any waranty.
*/



/* Sections Definitions */

SECTIONS
{
    /* the program code is stored in the .text section */
    .text :
    {
	    . = ALIGN(4);
	    
        *crt0*.o (.text)            /* Startup code */
        *startup.o (.text)         /* Startup code */
        *(.text)                   /* remaining code */
        *(.rodata)                 /* read-only data (constants) */
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)

	    . = ALIGN(4);
   	 _etext = .;
	    /* This is used by the startup in order to initialize the .data secion */
	    _sidata = _etext ;
    } >EXTMEMB0
    
 

    /* This is the initialized data section
    The program executes knowing that the data is in the RAM
    but the loader puts the initial values in the EXTMEM.
    It is one task of the startup to copy the initial values from EXTMEMB0 to RAM. */
    .data  : AT ( _etext )
    {
	    . = ALIGN(4);
        /* This is used by the startup in order to initialize the .data secion */
        _sdata = . ;
        
        *(.data)
        
	    . = ALIGN(4);
	    /* This is used by the startup in order to initialize the .data secion */
   	 _edata = . ;
    } >RAM
    
    

    /* This is the uninitialized data section */
    .bss :
    {
	    . = ALIGN(4);
        /* This is used by the startup in order to initialize the .bss secion */
        _sbss = .;
        
        *(.bss)
        *(COMMON)
	    . = ALIGN(4);
	    /* This is used by the startup in order to initialize the .bss secion */
   	 _ebss = . ;
	    
    } >RAM
    
    PROVIDE ( end = _ebss );
    PROVIDE ( _end = _ebss );
    
    /* This is the user stack section 
    This is just to check that there is enough RAM left for the User mode stack
    It should generate an error if it's full.
     */
    ._usrstack :
    {
	    . = ALIGN(4);
        _susrstack = . ;
        
        . = . + _Minimum_Stack_Size ;
        
        _eusrstack = ALIGN(4) ;
	    . = .;
    } >RAM

   
    /* this is the FLASH Bank0 */
    /* the C or assembly source must explicitly place the code or data there
    using the "section" attribute */
    .fb0text :
    {
        *(.fb0text)                   /* remaining code */
        *(.fb0rodata)                 /* read-only data (constants) */
        *(.fb0rodata*)
    } >FLASH
    
    /* this is the FLASH Bank1 */
    /* the C or assembly source must explicitly place the code or data there
    using the "section" attribute */
    .fb1text :
    {
        *(.fb1text)                   /* remaining code */
        *(.fb1rodata)                 /* read-only data (constants) */
        *(.fb1rodata*)
    } >FLASHB1
    
    /* EXTMEM Bank1 */
    .eb1text :
    {
        *(.b1text)                   /* remaining code */
        *(.b1rodata)                 /* read-only data (constants) */
        *(.b1rodata*)
    } >EXTMEMB1
    
    /* EXTMEM Bank2 */
    .eb2text :
    {
        *(.b2text)                   /* remaining code */
        *(.b2rodata)                 /* read-only data (constants) */
        *(.b2rodata*)
    } >EXTMEMB2
    
    /* EXTMEM Bank0 */
    .eb3text :
    {
        *(.b3text)                   /* remaining code */
        *(.b3rodata)                 /* read-only data (constants) */
        *(.b3rodata*)
    } >EXTMEMB3
    
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
}



