// define rom size
#define __ROM_SIZE               512k
#define __ROM_ADDR               0x08002000
// define ram size
#define __RAM_SIZE               64k
#define __RAM_ADDR               0x20000000

#define __NR_OF_VECTORS          42
#define __VECTOR_TABLE_SIZE      (__NR_OF_VECTORS * 4)
#define __VECTOR_TABLE_ROM_ADDR  0x08002000
#define _Vectors                 0x08002000

#define _ENTRYADDR               (0x08002001 + __VECTOR_TABLE_SIZE + 80) /* xB0 */ 

#define _START                   max(_ENTRYADDR, 0x08002165)

#define __RESET                  0x08002004

#define __STACK                  0x400
#define __STACKADDR              (__RAM_ADDR + __RAM_SIZE - __STACK)
#define __HEAP                   2k

#define __TABLE_RAM_SIZE         20
#define __TABLE_RAM_ADDR         (__STACKADDR - __STACK - __TABLE_RAM_SIZE)


#define __MEMORY

#define __PROCESSOR_MODE         0x10            /* User mode */
#define __IRQ_BIT                0x80            /* IRQ interrupts disabled */
#define __FIQ_BIT                0x40            /* FIQ interrupts disabled */
#define __APPLICATION_MODE       (__PROCESSOR_MODE | __IRQ_BIT | __FIQ_BIT)


architecture ARM
{
   endianness
   {
      little;
      big;
   }
   space linear
   {
      id = 1;
      mau = 8;
      align = 4;
      map (size = 4G, dest = bus:local_bus);

      copytable
      (
         align = 4,
         copy_unit = 1,
         dest = linear
      );
      start_address
      (
         // It is not strictly necessary to define a run_addr for _START
         // because hardware starts execution at address 0x0 which should
         // be the vector table with a jump to the relocatable _START, but
         // an absolute address can prevent the branch to be out-of-range.
         // Or _START may be the entry point at reset and the reset handler
         // copies the vector table to address 0x0 after some ROM/RAM memory
         // re-mapping. In that case _START should be at a fixed address
         // in ROM, specifically the alias of address 0x0 before memory
         // re-mapping.
         run_addr = _START,
         symbol = "_START"
      );

      stack "stack"
      (

         align = 4,
         min_size = __STACK,
         grows = high_to_low
      );
      heap "heap"
      (
         align = 4,
         min_size=__HEAP
      );
      section_layout
      {
         "_lc_ub_vector_table" = __VECTOR_TABLE_ROM_ADDR;
         "_lc_ue_vector_table" = __VECTOR_TABLE_ROM_ADDR + __VECTOR_TABLE_SIZE + 8;
//         "_lc_ub_table" = __TABLE_RAM_ADDR;
//         "_lc_ue_table" = __TABLE_RAM_ADDR + __TABLE_RAM_SIZE;
         "_lc_ub_vector_table_copy" := "_lc_ub_vector_table";
         "_lc_ue_vector_table_copy" := "_lc_ue_vector_table";

         group ( ordered, run_addr=__VECTOR_TABLE_ROM_ADDR )
         {
            select ".text.vector";
            
         }
         
#ifdef __HEAPADDR
         group ( ordered, run_addr=__HEAPADDR )
         {
            select "heap";
         }
#endif
         group ( ordered, run_addr=__STACKADDR)
         {
            select "stack";
         }
      }
   }
   bus local_bus
      {
         mau = 8;
         width = 32;
      }
}
///////////////////////////////////////////////////////////////////


memory flash
{
    mau = 8;
    type = rom;
    size = __ROM_SIZE;
    map ( size = __ROM_SIZE, dest_offset = __ROM_ADDR, dest = bus:ARM:local_bus );
}

memory sram
{
    mau = 8;
    type = ram;
    size = __RAM_SIZE;
    map ( size = __RAM_SIZE, dest_offset = __RAM_ADDR, dest = bus:ARM:local_bus );
}
