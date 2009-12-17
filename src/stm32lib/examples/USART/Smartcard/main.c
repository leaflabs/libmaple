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

/* Private define ------------------------------------------------------------*/
#define T0_PROTOCOL           0x00 /* T0 PROTOCOL */
#define SETUP_LENGHT          20 
#define HIST_LENGHT           20
#define SC_Receive_Timeout    0x4000 /* direction to reader */

/* Private typedef -----------------------------------------------------------*/
/* ATR STRUCTURE - ANSWER TO RESET */
typedef  struct 
{
  u8 TS; /* Bit Convention */
  u8 T0; /* high nibble = N. of setup byte; low nibble = N. of historical byte */
  u8 T[SETUP_LENGHT]; /* setup array */
  u8 H[HIST_LENGHT]; /* historical array */
  u8 Tlenght; /* setup array dimension */
  u8 Hlenght; /* historical array dimension */
} SC_ATR;

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
USART_InitTypeDef USART_InitStructure;
USART_ClockInitTypeDef USART_ClockInitStructure; 
SC_ATR  SC_A2R;
vu32 index = 0, Counter = 0;
volatile TestStatus ATRDecodeStatus = FAILED;
vu32 CardInserted = 0, CardProtocol = 1;
ErrorStatus HSEStartUpStatus;
vu8 DST_Buffer[50]= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void EXTI_Configuration(void);
void NVIC_Configuration(void);
u8 SC_decode_Answer2reset(vu8 *card);

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

  /* Configure the EXTI Controller */
  EXTI_Configuration();


/* USART3 configuration -------------------------------------------------------*/
  /* USART3 configured as follow:
        - Word Length = 9 Bits
        - 0.5 Stop Bit
        - Even parity
        - BaudRate = 12096 baud
        - Hardware flow control disabled (RTS and CTS signals)
        - Tx and Rx enabled
        - USART Clock enabled
        - USART CPOL Low
        - USART CPHA on first edge
        - USART Last Bit Clock Enabled
  */

  /* USART Clock set to 4.5MHz (PCLK1 = 36 MHZ / 8) */
  USART_SetPrescaler(USART3, 0x04);
  /* USART Guard Time set to 2 Bit */
  USART_SetGuardTime(USART3, 0x2);
  
  USART_ClockInitStructure.USART_Clock = USART_Clock_Enable;
  USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
  USART_ClockInitStructure.USART_CPHA = USART_CPHA_1Edge;
  USART_ClockInitStructure.USART_LastBit = USART_LastBit_Enable;
  USART_ClockInit(USART3, &USART_ClockInitStructure);

  USART_InitStructure.USART_BaudRate = 12096;
  USART_InitStructure.USART_WordLength = USART_WordLength_9b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1_5;
  USART_InitStructure.USART_Parity = USART_Parity_Even;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART3, &USART_InitStructure);  

  /* Enable the USART3 Parity Error Interrupt */
  USART_ITConfig(USART3, USART_IT_PE, ENABLE);

  /* Enable USART3 */
  USART_Cmd(USART3, ENABLE);

  /* Enable the NACK Transmission */
  USART_SmartCardNACKCmd(USART3, ENABLE);

  /* Enable the Smartcard Interface */
  USART_SmartCardCmd(USART3, ENABLE);


  /* Loop while no Smartcard is detected */  
  while(CardInserted == 0)
  {
  }

  /* Read Smartcard ATR response */ 
  for(index = 0; index < 40; index++, Counter = 0)
  {
    while((USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET) && (Counter != SC_Receive_Timeout))
    {
      Counter++;
    }

    if(Counter != SC_Receive_Timeout)
    {
      DST_Buffer[index] = USART_ReceiveData(USART3);
    }
  }

  /* Decode ATR */
  CardProtocol = SC_decode_Answer2reset(DST_Buffer);

  /* Test if the inserted card is ISO7816-3 T=0 compatible */
  if(CardProtocol == 0)
  {
    /* Inserted card is ISO7816-3 T=0 compatible */
    ATRDecodeStatus = PASSED;
  }
  else 
  { 
    /* Inserted Smartcard is not ISO7816-3 T=0 compatible */
    ATRDecodeStatus = FAILED;
  } 

  while (1)
  {   
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
    
  /* Enable GPIO_3_5V, GPIOB, GPIO_CMDVCC, GPIO_RESET, GPIO_OFF and AFIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_3_5V | RCC_APB2Periph_GPIOB | RCC_APB2Periph_RESET | 
                         RCC_APB2Periph_CMDVCC | RCC_APB2Periph_OFF | RCC_APB2Periph_AFIO, ENABLE);

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

  /* Configure USART3 CK(PB12) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure USART3 Tx (PB10) as alternate function open-drain */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure Smartcard Reset  */
  GPIO_InitStructure.GPIO_Pin = SC_RESET;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIO_RESET, &GPIO_InitStructure);

  /* Set RSTIN HIGH */  
  GPIO_SetBits(GPIO_RESET, SC_RESET);

  /* Configure Smartcard 3/5V  */
  GPIO_InitStructure.GPIO_Pin = SC_3_5V;
  GPIO_Init(GPIO_3_5V, &GPIO_InitStructure);

  /* Select 5 V */  
  GPIO_SetBits(GPIO_3_5V, SC_3_5V);

  /* Configure Smartcard CMDVCC  */
  GPIO_InitStructure.GPIO_Pin = SC_CMDVCC;
  GPIO_Init(GPIO_CMDVCC, &GPIO_InitStructure);

  /* Select Smartcard CMDVCC */ 
  GPIO_SetBits(GPIO_CMDVCC, SC_CMDVCC);

  /* Select Smartcard OFF */
  GPIO_InitStructure.GPIO_Pin = SC_OFF;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIO_OFF, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : EXTI_Configuration
* Description    : Configures the External Interrupts controller.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI_Configuration(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;

  /* Smartcard OFF */
  GPIO_EXTILineConfig(SC_PortSource, SC_PinSource);

  EXTI_StructInit(&EXTI_InitStructure);
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_Line = SC_EXTI;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Clear SC EXTI Line Pending Bit */
  EXTI_ClearITPendingBit(SC_EXTI);
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures the nested vectored interrupt controller.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif

  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  /* Clear the SC_EXTI IRQ Pending Bit */
  NVIC_ClearIRQChannelPendingBit(SC_EXTI_IRQ);

  NVIC_InitStructure.NVIC_IRQChannel = SC_EXTI_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : SC_decode_Answer2reset
* Description    : Decode the Card ATR Response.
* Input          : - card: pointer to the buffer containing the Card ATR.
* Output         : None
* Return         : Card protocol
*******************************************************************************/
u8 SC_decode_Answer2reset(vu8 *card)
{
  u32 i = 0, flag = 0, buf = 0, protocol = 0;

  SC_A2R.TS = 0;
  SC_A2R.T0 = 0;
  for (i = 0; i < SETUP_LENGHT; i++)
  {
    SC_A2R.T[i] = 0;
  }
  for (i = 0;i < HIST_LENGHT; i++)
  {
    SC_A2R.H[i] = 0;
  }
  SC_A2R.Tlenght = 0;
  SC_A2R.Hlenght = 0;

  SC_A2R.TS = card[0]; /* INITIAL CHARACTER */
  SC_A2R.T0 = card[1]; /* FORMAT CHARACTER */

  SC_A2R.Hlenght = SC_A2R.T0 & 0x0F;

  if((SC_A2R.T0 & 0x80) == 0x80) flag = 1;

  for(i = 0; i < 4; i++) 	
  {
    SC_A2R.Tlenght = SC_A2R.Tlenght + (((SC_A2R.T0 & 0xF0) >> (4 + i)) & 0x1);
  }

  for(i = 0; i < SC_A2R.Tlenght; i++)
  {
    SC_A2R.T[i] = card[i + 2];
  }

  protocol = SC_A2R.T[SC_A2R.Tlenght - 1] & 0x0F; 

  while(flag) 
  {
    if ((SC_A2R.T[SC_A2R.Tlenght-1] & 0x80)== 0x80)
    {
      flag = 1;
    }
    else
    {
      flag = 0;
    }
    buf = SC_A2R.Tlenght;
    SC_A2R.Tlenght = 0;

    for(i = 0; i < 4; i++)
    {
      SC_A2R.Tlenght = SC_A2R.Tlenght + (((SC_A2R.T[buf - 1] & 0xF0) >> (4 + i)) & 0x1);
    }
    for(i = 0; i < SC_A2R.Tlenght; i++)
    {
      SC_A2R.T[buf + i] = card[i + 2 + buf];
    }
    SC_A2R.Tlenght += buf;
  }

  for(i = 0;i < SC_A2R.Hlenght; i++)
  {
    SC_A2R.H[i] = card[i + 2 + SC_A2R.Tlenght];
  }
  
  return ((u8)protocol);
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
