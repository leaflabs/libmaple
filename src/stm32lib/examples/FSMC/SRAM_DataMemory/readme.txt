/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the FSMC SRAM_DataMemory Example.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

Example description
===================
This example shows how to use the external SRAM mounted on STM3210E-EVAL board as
program data memory and internal SRAM for Stack.


Directory contents
==================
stm32f10x_conf.h      Library Configuration file
stm32f10x_it.c        Interrupt handlers
stm32f10x_it.h        Header for stm32f10x_it.c  
main.c                Main program
stm32f10x_vector.s    STM32F10x vector table for RVMDK toolchain. 


Hardware environment
====================
This example runs on STMicroelectronics STM3210E-EVAL evaluation board.

    
How to use it
=============
In order to make the program work, you must do the following:
- Create a project and setup all your toolchain's start-up files:
 + RVMDK
    - in Project->Options->Target window, select 'RAM1'and enter 0x68000000 as
      start address with size of 0x100000 (IRAM1 must be un-checked)
    - use the "stm32f10x_vector.s" provided within this example directory                  

 + EWARM4
    - use "lnkarm_flash_extsram.xcl" as linker file
    - uncomment "#define DATA_IN_ExtSRAM " in the "stm32f10x_vector.c" file

 + EWARM5
    - use "stm32f10x_flash_extsram.icf" as linker file
    - uncomment "#define DATA_IN_ExtSRAM " in the "stm32f10x_vector.c" file

 + RIDE
    - In the Application options -> script menu, set "Use Default Script File" 
        to "No" and use "stm32f10x_flash_extsram.ld" as Script File.
    - uncomment "#define DATA_IN_ExtSRAM " in the "stm32f10x_vector.c" file
    
 + HiTOP
     - in project->settings->project->tool settings->linker, use "linkextsram" 
       as linker file. With this linker, the external SRAM is used for both
       program data and Stack.
     - in  cstart_thum2.asm file, change "DATA_IN_ExtSRAM  .equ    0"  
       by "DATA_IN_ExtSRAM  .equ   1"

- Compile the directory content files and required Library files:
  + stm32f10x_lib.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c
  + stm32f10x_fsmc.c
  
- Link all compiled files and load your image into target memory
- Run the example

******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
