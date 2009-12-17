/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the NVIC VectorTable_Relocation Example.
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
This example describes how to use the NVIC firmware library to set the CortexM3 
vector table in a specific address other than default.

This can be used to build program which will be loaded into Flash memory by an
application previously programmed from the Flash memory base address. 
Such application can be In-Application Programming (IAP, through USART) or
Device Firmware Upgrade (DFU, through USB).
These applications are available for download from the ST microcontrollers 
website: www.st.com/stm32

The associated program implements a "Delay" function based on SysTick end of count
interrupt, and toggles four leds with timing defined by the "Delay" function.

When using the IAP to load your porgram, the vector table must be relocated at
address 0x08002000.
When using the DFU to load your porgram, the vector table must be relocated at
address 0x08003000.


Directory contents
==================
 + \linker           
    + \EWARMv4               
       + lnkarm_flash_offset.xcl       XLINK command file template for EWARM4
    + \EWARMv5               
       + stm32f10x_flash_offset.icf    ILINK command file template for EWARM5
    + \RIDE               
       + stm32f10x_flash.ld            linker script for RIDE
    + \HiTOP               
       + STM32F10x_offset.lsl          linker file for HiTOP
       + link_offset                   script for HiTOP
                                          
 + platform_config.h    Evaluation board specific configuration file
 + stm32f10x_conf.h     Library Configuration file
 + stm32f10x_it.c       Interrupt handlers
 + stm32f10x_it.h       Interrupt handlers header file
 + main.c               Main program
 + main.h               Header for main.c


Hardware environment
====================
This example runs on STMicroelectronics STM3210B-EVAL and STM3210E-EVAL evaluation
boards and can be easily tailored to any other hardware.
To select the STMicroelectronics evaluation board used to run the example, uncomment
the corresponding line in platform_config.h file.

 + STM3210B-EVAL 
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PC.06, PC.07, PC.08
      and PC.09 pins
 
 + STM3210E-EVAL
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PF.06, PF0.7, PF.08
      and PF.09 pins

    
How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files:
 + RVMDK
    - in the project option menu, select 'Target' window and enter 0x08002000 
      as IROM start address
    - in the project option menu, select 'Linker' window and enter 0x08002000 
      as R/O base address                    

 + EWARM4
    - use "lnkarm_flash_offset.xcl" as linker file
    
 + EWARM5
    - use "stm32f10x_flash_offset.icf" as linker file

 + RIDE
    - In the Application options -> script menu, set "Use Default Script File" 
      to "No" and use "stm32f10x_flash_offset.ld" as Script File. 
      This linker is configured for STM32 High-density devices. To use it with
      Medium-density devices, this linker should be updated as follows: 
        - line39: RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 20K
        - line40: FLASH (rx) : ORIGIN = 0x8002000, LENGTH = 128K-0x2000
        - line49: _estack = 0x20005000;
              
 + HiTOP
    - copy the "link_offset" and "STM32F10x_offset.lsl" files under "Settings" 
      folder which is created by default by HiTOP.
    - in project->settings->project->tool settings ->linker, 
      use "link_offset.lnk" as linker file.     
      This linker is configured for STM32 High-density devices. To use it with
      Medium-density devices, this linker should be updated as follows: 
        - line2: #define __ROM_SIZE               128k
        - line5: #define __RAM_SIZE               20k
        
- Compile the directory content files and required Library files:
  + stm32f10x_lib.c
  + stm32f10x_systick.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c

- In the main.c and linker files, the vector table is relocated at address 0x08002000.
  You can modify this address depending on the requirement of your application. 
    
- Rebuild all files 

- Convert the program image to a binary file, *.bin, then you can download and
  run it using the IAP or DFU application.

NOTE:
 - Medium-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 32 and 128 Kbytes.
 - High-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 256 and 512 Kbytes.

******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
