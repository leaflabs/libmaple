/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the binary directory.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

Description
===================
This directory contains a set of sources files that build the application to be
loaded into the NOR memory mounted on STM3210E-EVAL board.

The GPIO IOToggle example provided within the STM32F10x Firmware library is used
as illustration. In this example four LEDs connected to the PF.06, PF.07, PF.08
and PF.09 pins are toggled in an infinite loop.


Directory contents
==================                 
stm32f10x_conf.h        Library Configuration file
stm32f10x_it.c          Interrupt handlers
stm32f10x_it.h          Header for stm32f10x_it.c  
main.c                  Main program
FLASH_NOR.ini           NOR Initialization File for RVMDK toolchain. 
STM3210E-EVAL_NOR.FLM   STM3210E-EVAL board NOR flasher for RVMDK toolchain.


Hardware environment
====================
This example runs on STMicroelectronics STM3210E-EVAL evaluation board and can be
easily tailored to any other hardware.

   
How to use it
=============
In order to make the program work, you must do the following:
- Create a project and setup all your toolchain's start-up files:
 + RVMDK
    - copy "STM3210E-EVAL_NOR.FLM" file under "C:\Keil\ARM\Flash" directory
    - in Project->Options->Target window, select 'ROM1', enter 0x64000000 as
      start address with size of 0x1000000 ans check "Startup" option (IROM1 must be un-checked)
    - in Project->Options->Linker window, enter 0x64000000 as R/O base address                    
    - in Project->Options->Utilities window, select "Use Target Driver for Flash Programming"
        - Click on 'Settings' button then select "STM3210E_EVAL NOR Flash" as
          Programming Algorithms (start:0x64000000, size:0x1000000)
        - in "Init File" select "FLASH_NOR.ini" provided within this example directory        

 + EWARM4
    - use "lnkarm_nor.xcl" as linker file
    - in project->options ->debugger-> setup , the "run to main" option should be 
      un-checked
    - in project->options ->debugger->download click on "edit" button("Use flash 
      loader(s)" option must be checked)
        - select the default flash loader then click on "edit" button
        - check the "Relocate" option and enter 0x64000000 as Base address
        - check "override default flash loader path" option and use "FlashSTM32F10x_NOR.d79" 
          as flash loader

 + EWARM5
    - use "stm32f10x_nor.icf" as linker file
    - in project->options ->debugger-> setup , the "run to main" option should be 
      un-checked
    - in project->options ->debugger->download click on "edit" button("Use flash 
      loader(s)" option must be checked)
        - select the default flash loader then click on "edit" button
        - check the "Relocate" option and enter 0x64000000 as Base address
        - check "override default flash loader path" option and use "FlashSTM32F10x_NOR.out" 
          as flash loader

 + HiTOP
   - in project->settings->project->tool settings ->linker, use "linknor.lnk" 
     as linker file.
   - run the script Flash_Nor (click on the button Flash_Nor from the toolbar menu) 
     before loading the image into target.

- Compile the directory content files and required Library files:
  + stm32f10x_lib.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_flash.c
  
- Link all compiled files and load your image into NOR memory

******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
