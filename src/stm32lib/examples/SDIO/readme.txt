/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the SDIO Example.
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
This example provides a basic example of how to use the SDIO firmware library and
an associate driver to perform read/write operations on the SD Card memory 
mounted on the STM3210E-EVAL board.
Below is a description of the different example steps:
  - Configure the SDIO according to the desired SDIO_CK clock frequency.
  - Reset the SD Card
  - Identify the SD Card
  - Initializes the SD Card
  - Get the SD Card Info
  - Select the SD Card
  - Enable the Wide Bus mode (4-bit data)
  - Erase the correponding blocks
  - Read the Erased blocks
  - Test if the corresponding Blocks are well erased: check if the EraseStatus 
    variable is equal to PASSED.
  - Set the Data Transfer Mode to DMA   
  - Write a single Block             
  - Read a single Block
  - Comapare the written Block and the read one: check if the TransferStatus1 
    variable is equal to PASSED.
  - Write multiple Blocks (2)             
  - Read multiple Blocks (2)
  - Comapare the written Blocks and the read one: check if the TransferStatus2 
    variable is equal to PASSED.  


Directory contents
==================
stm32f10x_conf.h  Library Configuration file
stm32f10x_it.c    Interrupt handlers
stm32f10x_it.h    Header for stm32f10x_it.c
sdcard.c          SD Card Driver file
sdcard.h          Header for sdcard.c
main.c            Main program


Hardware environment
====================
This example runs on STMicroelectronics STM3210E-EVAL evaluation board and can be
easily tailored to any other hardware.

Note: make sure that the Jumper 17 (JP17) is closed and Jumper 20 (JP20) is open
      in STM3210E-EVAL 


How to use it
=============
In order to make the program work, you must do the following:
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files:
  + stm32f10x_lib.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c
  + stm32f10x_sdio.c
  + stm32f10x_dma.c
  
- Link all compiled files and load your image into either RAM or Flash
- Run the example

******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
