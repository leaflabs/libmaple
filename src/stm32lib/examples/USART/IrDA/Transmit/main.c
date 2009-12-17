/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Main program body
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "platform_config.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define  NOKEY  0
#define  SEL    1
#define  RIGHT  2
#define  LEFT   3
#define  UP     4
#define  DOWN   5

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
USART_InitTypeDef USART_InitStructure;
u8 MyKey = 0;
ErrorStatus HSEStartUpStatus;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
u8 ReadKey(void);

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
#ifdef DEBUG
  debug();
#endif

  /* System Clocks Configuration */
  RCC_Configuration();
       
  /* NVIC configuration */
  NVIC_Configuration();

  /* Configure the GPIO ports */
  GPIO_Configuration();

/* USART3 configuration ------------------------------------------------------*/
  /* USART3 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure the USART3 */
  USART_Init(USART3, &USART_InitStructure);
  /* Enable the USART3 */
  USART_Cmd(USART3, ENABLE);
  /* Set the USART3 prescaler */
  USART_SetPrescaler(USART3, 0x1);
  /* Configure the USART3 IrDA mode */
  USART_IrDAConfig(USART3, USART_IrDAMode_Normal);

  /* Enable the USART3 IrDA mode */
  USART_IrDACmd(USART3, ENABLE);


  while (1)
  {
    /* Read Key */
    MyKey = ReadKey();

    switch(MyKey)
    {
      case UP:
        USART_SendData(USART3, UP);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
        {
        }
        break;
      case DOWN:
        USART_SendData(USART3, DOWN);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
        {
        }
        break;
      case LEFT:
        USART_SendData(USART3, LEFT);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
        {
        }
        break;
      case RIGHT:
        USART_SendData(USART3, RIGHT);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
        {
        }
        break;
      case SEL:
        USART_SendData(USART3, SEL);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
        {
        }
        break;
      case NOKEY:
        USART_SendData(USART3, NOKEY);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
        {
        } 
        break;
      default:
        break;
    }
  }
}

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
 
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }  
  
  /* Enable GPIOC, GPIO Right Button, GPIO Left Button, GPIO UP Button
     GPIO DOWN Button, GPIO SEL Button and AFIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIO_RIGHT_BUTTON
                         | RCC_APB2Periph_GPIO_LEFT_BUTTON | RCC_APB2Periph_GPIO_UP_BUTTON
                         |RCC_APB2Periph_GPIO_DOWN_BUTTON | RCC_APB2Periph_GPIO_SEL_BUTTON
                         | RCC_APB2Periph_AFIO, ENABLE);
  /* Enable USART3 clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure the USART3 Software Pins remapping */
  GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);

  /* Configure USART3 Tx (PC.10)as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  /* Configure USART3 Rx PC.11 as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  /* Configure GPIO RIGHT Button Pin as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_RIGHT_BUTTON;
  GPIO_Init(GPIO_RIGHT_BUTTON, &GPIO_InitStructure);

  /* Configure GPIO LEFT Button Pin as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LEFT_BUTTON;
  GPIO_Init(GPIO_LEFT_BUTTON, &GPIO_InitStructure);

  /* Configure GPIO UP Button Pin as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_UP_BUTTON;
  GPIO_Init(GPIO_UP_BUTTON, &GPIO_InitStructure);

  /* Configure GPIO DOWN Button Pin as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_DOWN_BUTTON;
  GPIO_Init(GPIO_DOWN_BUTTON, &GPIO_InitStructure);

  /* Configure GPIO SEL Button Pin as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_SEL_BUTTON;
  GPIO_Init(GPIO_SEL_BUTTON, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif
}

/*******************************************************************************
* Function Name  : ReadKey
* Description    : Reads key from demoboard.
* Input          : None
* Output         : None
* Return         : Return RIGHT, LEFT, SEL, UP, DOWN or NOKEY
*******************************************************************************/
u8 ReadKey(void)
{
  /* "right" key is pressed */
  if(!GPIO_ReadInputDataBit(GPIO_RIGHT_BUTTON, GPIO_PIN_RIGHT_BUTTON))
  {
    while(GPIO_ReadInputDataBit(GPIO_RIGHT_BUTTON, GPIO_PIN_RIGHT_BUTTON) == Bit_RESET);
    return RIGHT; 
  }
  /* "left" key is pressed */
  if(!GPIO_ReadInputDataBit(GPIO_LEFT_BUTTON, GPIO_PIN_LEFT_BUTTON))
  {
    while(GPIO_ReadInputDataBit(GPIO_LEFT_BUTTON, GPIO_PIN_LEFT_BUTTON) == Bit_RESET);
    return LEFT; 
  }
  /* "up" key is pressed */
  if(!GPIO_ReadInputDataBit(GPIO_UP_BUTTON, GPIO_PIN_UP_BUTTON))
  {
    while(GPIO_ReadInputDataBit(GPIO_UP_BUTTON, GPIO_PIN_UP_BUTTON) == Bit_RESET);
    return UP; 
  }
  /* "down" key is pressed */
  if(!GPIO_ReadInputDataBit(GPIO_DOWN_BUTTON, GPIO_PIN_DOWN_BUTTON))
  {
    while(GPIO_ReadInputDataBit(GPIO_DOWN_BUTTON, GPIO_PIN_DOWN_BUTTON) == Bit_RESET);
    return DOWN; 
  }
  /* "sel" key is pressed */
  if(!GPIO_ReadInputDataBit(GPIO_SEL_BUTTON, GPIO_PIN_SEL_BUTTON))
  {
    while(GPIO_ReadInputDataBit(GPIO_SEL_BUTTON, GPIO_PIN_SEL_BUTTON) == Bit_RESET);
    return SEL; 
  }
  /* No key is pressed */
  else 
  {
    return NOKEY;
  }
}

#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
