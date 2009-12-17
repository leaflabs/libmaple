/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the NVIC DMA in WFI mode Example.
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
This example shows how to enters the system to WFI mode with DMA transfer enabled
and wake-up from this mode by the DMA End of Transfer interrupt.

In the associated software, the system clock is set to 72 MHz, the DMA1 Channel5
is configured to transfer 10 data from the USART1 data register to a predefined 
buffer, DST_Buffer, and to generate an interrupt at the end of the transfer.
The USART1 receives data from Hyperterminal.
A LED1 is toggled with a frequency depending on the system
clock, this is used to indicate whether the MCU is in WFI or RUN mode. 

A falling edge on the selected EXTI Line will put the core in the WFI mode, causing the 
led pin to stop toggling.
To wake-up from WFI mode you have to send the sequence (0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
from the Hyperterminal to the USART1. These bytes will be transferred by the DMA from
the USART1 receive data register to the predefined buffer, then generates an interrupt
which exits the system from WFI mode. 
The LED1 restarts toggling and a LED2 will toggle if the buffer is correctly received 
else a LED3 is toggled.


Directory contents
==================
platform_config.h    Evaluation board specific configuration file
stm32f10x_conf.h     Library Configuration file
stm32f10x_it.c       Interrupt handlers
stm32f10x_it.h       Interrupt handlers header file
main.c               Main program


Hardware environment
====================
This example runs on STMicroelectronics STM3210B-EVAL and STM3210E-EVAL evaluation
boards and can be easily tailored to any other hardware.
To select the STMicroelectronics evaluation board used to run the example, uncomment
the corresponding line in platform_config.h file.

 + STM3210B-EVAL 
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PC.06, PC.07, PC.08
      and PC.09 pins
    - The USART1 signals (Rx, Tx) must be connected to a DB9 connector using a RS232
      transceiver.
    - Connect a null-modem female/female RS232 cable between the DB9 connector, 
      CN6 on STM3210B-EVAL board, and PC serial port.   
    - Hyperterminal configuration:
       - Word Length = 8 Bits
       - One Stop Bit
       - No parity
       - BaudRate = 9600 baud
       - flow control: None   
    - Use the Key push-button connected to pin PB.09 (EXTI Line9).
 
 + STM3210E-EVAL
    - Use LD1, LD2, LD3 and LD4 leds connected respectively to PF.06, PF0.7, PF.08
      and PF.09 pins
    - The USART1 signals (Rx, Tx) must be connected to a DB9 connector using a RS232
      transceiver.
    - Connect a null-modem female/female RS232 cable between the DB9 connector,
      CN12 on STM3210E-EVAL board, and PC serial port.   
    - Hyperterminal configuration:
       - Word Length = 8 Bits
       - One Stop Bit
       - No parity
       - BaudRate = 9600 baud
       - flow control: None 
    - Use the Key push-button connected to pin PG.08 (EXTI Line8).         

     
How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
  + stm32f10x_lib.c
  + stm32f10x_exti.c
  + stm32f10x_gpio.c
  + stm32f10x_rcc.c
  + stm32f10x_nvic.c
  + stm32f10x_flash.c
  + stm32f10x_dma.c
  + stm32f10x_usart.c
    
- Link all compiled files and load your image into target memory
- Run the example


******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
