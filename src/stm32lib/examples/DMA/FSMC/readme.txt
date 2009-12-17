/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the DMA FSMC Example.
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
This example provides a description of how to use two DMA channels to transfer a 
word data buffer from Flash memory to external SRAM memory and to recuperate the written
data from external SRAM to be stored in internal SRAM.
DMA2 Channel5 is configured to transfer, word by word, the contents of a 32-word data 
buffer stored in Flash memory to the external SRAM memory interfaced by FSMC. The start
of transfer is triggered by software. DMA2	Channel5 memory-to-memory transfer is enabled.
Source and destination address incrementing is also enabled. The transfer is started by
setting the Channel enable bit for DMA2 Channel5. A polling on the Transfer Complete flag
is done to check the end of transfer. The DMA2 Channel5 Transfer complete flag is then cleared.
DMA1 Channel3 is configured to transfer, byte by byte, the contents of the first 128Bytes
of external SRAM to the internal SRAM memory. The start of transfer is triggered by software.
DMA1 Channel3 memory-to-memory transfer is enabled. Source and destination address
incrementing is also enabled. The transfer is started by setting the Channel enable bit for
DMA1 Channel3. A polling on the Transfer Complete flag is done to check the end of transfer.
the DMA1 Channel3 Transfer complete flag is then cleared.
A comparison between the source and destination buffers is done to check that all data have been
correctly transferred.


Directory contents
==================
stm32f10x_conf.h  Library Configuration file
stm32f10x_it.c    Interrupt handlers
stm32f10x_it.h    Interrupt handlers header file
main.c            Main program
fsmc_sram.c       FSMC SRAM driver
fsmc_sram.h       Header for the fsmc_sram.c file


Hardware environment
====================
This example runs on STMicroelectronics STM3210E-EVAL evaluation board and can be 
easily tailored to any other hardware (with high density devices only).

      
How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
  + stm32f10x_lib.c
  + stm32f10x_dma.c
  + stm32f10x_rcc.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c  
  + stm32f10x_fsmc.c
  + stm32f10x_gpio.c

- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
