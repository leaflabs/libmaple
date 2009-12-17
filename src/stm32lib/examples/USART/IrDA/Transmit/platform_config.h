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

/* Define the STM32F10x hardware depending on the used evaluation board */
#ifdef USE_STM3210B_EVAL
  #define RCC_APB2Periph_GPIO_RIGHT_BUTTON   RCC_APB2Periph_GPIOE  
  #define GPIO_RIGHT_BUTTON                  GPIOE    
  #define GPIO_PIN_RIGHT_BUTTON              GPIO_Pin_0 
  #define RCC_APB2Periph_GPIO_LEFT_BUTTON    RCC_APB2Periph_GPIOE
  #define GPIO_LEFT_BUTTON                   GPIOE
  #define GPIO_PIN_LEFT_BUTTON               GPIO_Pin_1    
  #define RCC_APB2Periph_GPIO_UP_BUTTON      RCC_APB2Periph_GPIOD
  #define GPIO_UP_BUTTON                     GPIOD    
  #define GPIO_PIN_UP_BUTTON                 GPIO_Pin_8
  #define RCC_APB2Periph_GPIO_DOWN_BUTTON    RCC_APB2Periph_GPIOD 
  #define GPIO_DOWN_BUTTON                   GPIOD 
  #define GPIO_PIN_DOWN_BUTTON               GPIO_Pin_14   
  #define RCC_APB2Periph_GPIO_SEL_BUTTON     RCC_APB2Periph_GPIOD
  #define GPIO_SEL_BUTTON                    GPIOD
  #define GPIO_PIN_SEL_BUTTON                GPIO_Pin_12     
#elif defined USE_STM3210E_EVAL
  #define RCC_APB2Periph_GPIO_RIGHT_BUTTON   RCC_APB2Periph_GPIOG  
  #define GPIO_RIGHT_BUTTON                  GPIOG    
  #define GPIO_PIN_RIGHT_BUTTON              GPIO_Pin_13 
  #define RCC_APB2Periph_GPIO_LEFT_BUTTON    RCC_APB2Periph_GPIOG
  #define GPIO_LEFT_BUTTON                   GPIOG
  #define GPIO_PIN_LEFT_BUTTON               GPIO_Pin_14    
  #define RCC_APB2Periph_GPIO_UP_BUTTON      RCC_APB2Periph_GPIOG
  #define GPIO_UP_BUTTON                     GPIOG    
  #define GPIO_PIN_UP_BUTTON                 GPIO_Pin_15
  #define RCC_APB2Periph_GPIO_DOWN_BUTTON    RCC_APB2Periph_GPIOD 
  #define GPIO_DOWN_BUTTON                   GPIOD 
  #define GPIO_PIN_DOWN_BUTTON               GPIO_Pin_3   
  #define RCC_APB2Periph_GPIO_SEL_BUTTON     RCC_APB2Periph_GPIOG
  #define GPIO_SEL_BUTTON                    GPIOG
  #define GPIO_PIN_SEL_BUTTON                GPIO_Pin_7 
#endif /* USE_STM3210B_EVAL */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __PLATFORM_CONFIG_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
