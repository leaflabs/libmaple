/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Description of the USART Hyperterminal Hardware Flow Control
*                      Example.
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
This example provides a description of how to use the USART with hardware flow
control and communicate with the Hyperterminal.
First, the USART2 sends the TxBuffer to the hyperterminal and still waiting for
a string from the hyperterminal that you must enter which must end by '\r'
character (keypad ENTER button). The communication will end if received data exceed
255 without sending the '\r' character. Each byte received is retransmitted to the
Hyperterminal.
The string that you have entered is stored in the RxBuffer array. The receive
buffer have a RxBufferSize bytes as maximum.

The USART2 is configured as follow:
    - BaudRate = 115200 baud  
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control enabled (RTS and CTS signals)
    - Receive and transmit enabled


Directory contents
==================
platform_config.h    Evaluation board specific configuration file
stm32f10x_conf.h     Library Configuration file
stm32f10x_it.h       Interrupt handlers header file
stm32f10x_it.c       Interrupt handlers
main.c               Main program


Hardware environment
====================
This example runs on STMicroelectronics STM3210B-EVAL and STM3210E-EVAL evaluation
boards and can be easily tailored to any other hardware.
To select the STMicroelectronics evaluation board used to run the example, uncomment
the corresponding line in platform_config.h file.

 + STM3210B-EVAL 
    - Connect a null-modem female/female RS232 cable between CN5 and PC serial 
      port.
    - Note: in this case USART2 Tx, Rx, RTS and CTS pins are remapped by software
            on PD.05, PD.06, PD.04 and PD.03 respectively. 
 
 + STM3210E-EVAL
    - Connect a null-modem female/female RS232 cable between CN8 and PC serial 
      port.
    - Make sure the Jumper 4 (JP4) is in position 2<-->3.    

 + Hyperterminal configuration:
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - BaudRate = 115200 baud
    - flow control: Hardware 

    
How to use it
=============
In order to make the program work, you must do the following :
- Create a project and setup all your toolchain's start-up files
- Compile the directory content files and required Library files :
  + stm32f10x_lib.c
  + stm32f10x_usart.c
  + stm32f10x_gpio.c
  + stm32f10x_nvic.c
  + stm32f10x_rcc.c
  + stm32f10x_flash.c
    
- Link all compiled files and load your image into target memory
- Run the example

******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE******
