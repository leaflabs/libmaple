/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : platform_config.h
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Evaluation board specific configuration file.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line corresponding to the STMicroelectronics evaluation board
   used to run the example */
#if !defined (USE_STM3210B_EVAL) &&  !defined (USE_STM3210E_EVAL)
 //#define USE_STM3210B_EVAL
 #define USE_STM3210E_EVAL
#endif

/* Uncomment the line corresponding to the select the USART used to run 
   the example */
#define USE_USART1
//#define USE_USART2
//#define USE_USART3
//#define USE_UART4
//#define USE_UART5

#ifdef USE_USART1
  #define  USARTx                     USART1
  #define  GPIOx                      GPIOA
  #define  RCC_APB2Periph_GPIOx       RCC_APB2Periph_GPIOA
  #define  GPIO_RxPin                 GPIO_Pin_10
  #define  GPIO_TxPin                 GPIO_Pin_9
#elif defined USE_USART2 && defined USE_STM3210B_EVAL
  #define  USARTx                     USART2
  #define  RCC_APB1Periph_USARTx      RCC_APB1Periph_USART2
  #define  GPIOx                      GPIOD
  #define  RCC_APB2Periph_GPIOx       RCC_APB2Periph_GPIOD
  #define  GPIO_TxPin                 GPIO_Pin_5
  #define  GPIO_RxPin                 GPIO_Pin_6
#elif defined USE_USART2 && defined   USE_STM3210E_EVAL  
  #define  USARTx                     USART2
  #define  RCC_APB1Periph_USARTx      RCC_APB1Periph_USART2
  #define  GPIOx                      GPIOA
  #define  RCC_APB2Periph_GPIOx       RCC_APB2Periph_GPIOA
  #define  GPIO_TxPin                 GPIO_Pin_2
  #define  GPIO_RxPin                 GPIO_Pin_3
#elif defined USE_USART3
  #define  USARTx                     USART3
  #define  GPIOx                      GPIOB
  #define  RCC_APB2Periph_GPIOx       RCC_APB2Periph_GPIOB
  #define  RCC_APB1Periph_USARTx      RCC_APB1Periph_USART3
  #define  GPIO_RxPin                 GPIO_Pin_11
  #define  GPIO_TxPin                 GPIO_Pin_10
#elif defined USE_UART4
  #define  USARTx                     UART4
  #define  GPIOx                      GPIOC
  #define  RCC_APB2Periph_GPIOx       RCC_APB2Periph_GPIOC
  #define  RCC_APB1Periph_USARTx      RCC_APB1Periph_UART4
  #define  GPIO_RxPin                 GPIO_Pin_11
  #define  GPIO_TxPin                 GPIO_Pin_10
#elif defined USE_UART5
  #define  USARTx                     UART5
  #define  GPIOx                      GPIOC
  #define  RCC_APB2Periph_GPIOx       RCC_APB2Periph_GPIOC
  #define  RCC_APB1Periph_USARTx      RCC_APB1Periph_UART5
  #define  GPIO_RxPin                 GPIO_Pin_2
  #define  GPIO_TxPin                 GPIO_Pin_12
#endif

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __PLATFORM_CONFIG_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
