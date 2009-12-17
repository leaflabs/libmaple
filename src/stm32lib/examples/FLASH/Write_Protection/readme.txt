/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the FLASH Write_Protection Example.
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
This example provides a description of how to enable and disable the write protection
for the STM32F10x FLASH:

- Enable Write protection: 
  To enable the Write Protection, uncomment the line "#define WriteProtection_Enable"
  in main.c file.
  
  To protect a set of pages, the user has to call the function FLASH_EnableWriteProtection.
  The parameter of this function will define the number of pages to be protected.
  To load the new option byte values, a system Reset is necessary, for this, the
  function NVIC_GenerateSystemReset() is used.
 
- Disable Write protection:
  To disable the Write Protection, uncomment the line "#define WriteProtection_Disable"
  in main.c file.

  To disable the write protection of the STM32F10x Flash, an erase of the Option 
  Bytes is necessary. This operation is done by the function FLASH_EraseOptionBytes.
  To load the new option byte values, a system Reset is necessary, for this, the
  function NVIC_GenerateSystemReset() is used.

If the desired pages are not write protected, an erase and a write operation are
performed.


Directory contents
==================
platform_config.h    Evaluation board specific configuration file
stm32f10x_conf.h     Library Configuration file
stm32f10x_it.h       Interrupt handlers header file
stm32f10x_it.c       Interrupt handlers
main.c               Main program

Note: "#define _FLASH_PROG" should be uncommented in the stm32f10x_conf.h file
 

Hardware environment
====================
This example runs on STMicroelectronics STM3210B-EVAL and STM3210E-EVAL evaluation
boards and can be easily tailored to any other hardware.
To select the STMicroelectronics evaluation board used to run the example, uncomment
the corresponding line in platform_config.h file.

  
How to use it
=============
In order to make the program work, you must do the following:
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files:
  + stm32F10x_lib.c
  + stm32F10x_flash.c
  + stm32F10x_rcc.c
  + stm32F10x_nvic.c

- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
