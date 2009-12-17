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

/* Private typedef -----------------------------------------------------------*/
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define I2C1_SLAVE_ADDRESS7    0x30
#define I2C2_SLAVE1_ADDRESS7   0x30
#define I2C2_SLAVE2_ADDRESS7   0x22
#define BufferSize             4 
#define ClockSpeed             200000

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
I2C_InitTypeDef  I2C_InitStructure;
u8 I2C1_Buffer1_Tx[BufferSize] = {1,2,3,4}, I2C1_Buffer2_Tx[BufferSize] = {5,6,7,8};
u8 I2C2_Buffer1_Rx[BufferSize], I2C2_Buffer2_Rx[BufferSize];
u8 Tx_Idx = 0, Rx_Idx = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
ErrorStatus HSEStartUpStatus;    

/* Private functions ---------------------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
TestStatus Buffercmp(u8* pBuffer1, u8* pBuffer2, u16 BufferLength);

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

  /* System clocks configuration ---------------------------------------------*/
  RCC_Configuration();

  /* NVIC configuration ------------------------------------------------------*/
  NVIC_Configuration();

  /* GPIO configuration ------------------------------------------------------*/
  GPIO_Configuration();

  /* Enable I2C1 and I2C2 ----------------------------------------------------*/
  I2C_Cmd(I2C1, ENABLE);
  I2C_Cmd(I2C2, ENABLE);

  /* I2C1 configuration ------------------------------------------------------*/
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = I2C1_SLAVE_ADDRESS7;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = ClockSpeed;
  I2C_Init(I2C1, &I2C_InitStructure);
  /* I2C2 configuration ------------------------------------------------------*/
  I2C_InitStructure.I2C_OwnAddress1 = I2C2_SLAVE1_ADDRESS7;
  I2C_Init(I2C2, &I2C_InitStructure);

  /* I2C2 second address configuration */
  I2C_OwnAddress2Config(I2C2, I2C2_SLAVE2_ADDRESS7);
  /* Enable I2C2 Dual address */
  I2C_DualAddressCmd(I2C2, ENABLE);
     
  /*----- First transmission Phase -----*/
  /* Send I2C1 START condition */
  I2C_GenerateSTART(I2C1, ENABLE);
  /* Test on I2C1 EV5 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); 
  /* Send I2C2 slave Address for write */
  I2C_Send7bitAddress(I2C1, I2C2_SLAVE1_ADDRESS7, I2C_Direction_Transmitter);
  /* Test on I2C2 EV1 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED));  
  /* Test on I2C1 EV6 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); 

  /* Send data */
  while (Rx_Idx < BufferSize)
  {
    /* Send I2C1 data */
    I2C_SendData(I2C1, I2C1_Buffer1_Tx[Tx_Idx++]);
    /* Test on I2C2 EV2 and clear it */
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_SLAVE_BYTE_RECEIVED));  
    /* Store received data on I2C2 */
    I2C2_Buffer1_Rx[Rx_Idx++] = I2C_ReceiveData(I2C2);
    /* Test on I2C1 EV8 and clear it */
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); 
  }

  /* Send I2C1 STOP Condition */
  I2C_GenerateSTOP(I2C1, ENABLE);
  /* Test on I2C2 EV4 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_SLAVE_STOP_DETECTED)); 
  /* Clear I2C2 STOPF flag */
  I2C_ClearFlag(I2C2, I2C_FLAG_STOPF);

  /* Check the corectness of written data */
  TransferStatus1 = Buffercmp(I2C1_Buffer1_Tx, I2C2_Buffer1_Rx, BufferSize);
  /* TransferStatus1 = PASSED, if the transmitted and received data
     are equal */
  /* TransferStatus1 = FAILED, if the transmitted and received data 
     are different */

  /*----- Second transmission Phase -----*/
  /* Reset counters and reception buffer */
  Tx_Idx = Rx_Idx = 0;
  /* Send I2C1 START condition */
  I2C_GenerateSTART(I2C1, ENABLE);
  /* Test on I2C1 EV5 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));  
  /* Send I2C2 slave Address for write */
  I2C_Send7bitAddress(I2C1, I2C2_SLAVE2_ADDRESS7, I2C_Direction_Transmitter);
  /* Test on I2C2 EV1 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED)); 
  /* Test on I2C1 EV6 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));  

  /* Send data */
  while (Rx_Idx < BufferSize)
  {
    /* Send I2C1 data */
    I2C_SendData(I2C1, I2C1_Buffer2_Tx[Tx_Idx++]);
    /* Test on I2C2 EV2 and clear it */
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_DUALF));
    /* Store received data on I2C2 */
    I2C2_Buffer2_Rx[Rx_Idx++] = I2C_ReceiveData(I2C2);
    /* Test on I2C1 EV8 and clear it */
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); 
  }

  /* Send I2C1 STOP Condition */
  I2C_GenerateSTOP(I2C1, ENABLE);
  /* Test on I2C2 EV4 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_SLAVE_STOP_DETECTED)); 
  /* Clear I2C2 STOPF flag */
  I2C_ClearFlag(I2C2, I2C_FLAG_STOPF);

  /* Check the corectness of written data */
  TransferStatus2 = Buffercmp(I2C1_Buffer2_Tx, I2C2_Buffer2_Rx, BufferSize);
  /* TransferStatus2 = PASSED, if the transmitted and received data
     are equal */
  /* TransferStatus2 = FAILED, if the transmitted and received data 
     are different */

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

/* Enable peripheral clocks --------------------------------------------------*/
  /* GPIOB Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  /* I2C1 and I2C2 Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1 | RCC_APB1Periph_I2C2, ENABLE);
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

  /* Configure I2C1 pins: SCL and SDA ----------------------------------------*/
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure I2C2 pins: SCL and SDA ----------------------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
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
* Function Name  : Buffercmp
* Description    : Compares two buffers.
* Input          : - pBuffer1, pBuffer2: buffers to be compared.
*                : - BufferLength: buffer's length
* Output         : None
* Return         : PASSED: pBuffer1 identical to pBuffer2
*                  FAILED: pBuffer1 differs from pBuffer2
*******************************************************************************/
TestStatus Buffercmp(u8* pBuffer1, u8* pBuffer2, u16 BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }
    
    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;  
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
