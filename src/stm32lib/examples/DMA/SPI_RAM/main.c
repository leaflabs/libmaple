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
#define SPI1_DR_Address    0x4001300C
#define SPI2_DR_Address    0x4000380C
#define BufferSize         32
#define CRCPolynomial      7

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
SPI_InitTypeDef    SPI_InitStructure;
DMA_InitTypeDef    DMA_InitStructure;
ErrorStatus HSEStartUpStatus;
u8 SPI1_Buffer_Rx[BufferSize], SPI2_Buffer_Rx[BufferSize];
u8 SPI1CRCValue = 0, SPI2CRCValue = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
u8 SPI1_Buffer_Tx[BufferSize] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,
                                 0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,
                                 0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,
                                 0x1C,0x1D,0x1E,0x1F,0x20};
u8 SPI2_Buffer_Tx[BufferSize] = {0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,
                                 0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,0x60,0x61,0x62,
                                 0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,
                                 0x6C,0x6D,0x6E,0x6F,0x70};
								     
/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
TestStatus Buffercmp(u8* pBuffer, u8* pBuffer1, u16 BufferLength);

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

  /* SPI1 configuration ------------------------------------------------------*/
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = CRCPolynomial;
  SPI_Init(SPI1, &SPI_InitStructure);
  
  /* SPI2 configuration ------------------------------------------------------*/
  SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
  SPI_Init(SPI2, &SPI_InitStructure);

  /* DMA1 Channel2 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel2);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)SPI1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SPI1_Buffer_Rx;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = BufferSize;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel2, &DMA_InitStructure);

  /* DMA1 Channel3 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel3);  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)SPI1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SPI1_Buffer_Tx;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  DMA_Init(DMA1_Channel3, &DMA_InitStructure);

  /* DMA1 Channel4 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel4);  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)SPI2_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SPI2_Buffer_Rx;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);

  /* DMA1 Channel5 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel5);  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)SPI2_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SPI2_Buffer_Tx;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
  DMA_Init(DMA1_Channel5, &DMA_InitStructure);

  /* Enable SPI1 DMA Tx request */
  SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
  /* Enable SPI1 DMA Rx request */
  SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE);
  /* Enable SPI2 DMA Tx request */
  SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);   
  /* Enable SPI2 DMA Rx request */
  SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Rx, ENABLE); 
 
  /* Enable SPI1 CRC calculation */
  SPI_CalculateCRC(SPI1, ENABLE);
  /* Enable SPI2 CRC calculation */
  SPI_CalculateCRC(SPI2, ENABLE);

  /* Enable SPI2 */
  SPI_Cmd(SPI2, ENABLE);
  /* Enable SPI1 */
  SPI_Cmd(SPI1, ENABLE);

  /* Enable DMA1 channel5, channel4, channel3 and channel2 */
  DMA_Cmd(DMA1_Channel2, ENABLE);
  DMA_Cmd(DMA1_Channel4, ENABLE);
  DMA_Cmd(DMA1_Channel5, ENABLE);
  DMA_Cmd(DMA1_Channel3, ENABLE);
   
  /* Transfer complete */
  while(!DMA_GetFlagStatus(DMA1_FLAG_TC2));
  while(!DMA_GetFlagStatus(DMA1_FLAG_TC4));
  while(!DMA_GetFlagStatus(DMA1_FLAG_TC5));
  while(!DMA_GetFlagStatus(DMA1_FLAG_TC3));

  /* Wait for SPI1 data reception: CRC transmitted by SPI2 */
  while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)==RESET);
  /* Wait for SPI2 data reception: CRC transmitted by SPI1 */
  while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==RESET);

  /* Check the corectness of written dada */
  TransferStatus1 = Buffercmp(SPI2_Buffer_Rx, SPI1_Buffer_Tx, BufferSize);
  TransferStatus2 = Buffercmp(SPI1_Buffer_Rx, SPI2_Buffer_Tx, BufferSize);
  /* TransferStatus1, TransferStatus2 = PASSED, if the data transmitted and received 
     are correct */
  /* TransferStatus1, TransferStatus2 = FAILED, if the data transmitted and received  
     are different */

  /* Test on the SPI1 CRCR ERROR flag */
  if ((SPI_I2S_GetFlagStatus(SPI1, SPI_FLAG_CRCERR)) != RESET)
  {
    TransferStatus1 = FAILED;
  }
  /* Test on the SPI2 CRCR ERROR flag */
  if ((SPI_I2S_GetFlagStatus(SPI2, SPI_FLAG_CRCERR)) != RESET)
  {
    TransferStatus2 = FAILED;
  } 

  /* Read SPI1 received CRC value */
  SPI1CRCValue = SPI_I2S_ReceiveData(SPI1);
  /* Read SPI2 received CRC value */
  SPI2CRCValue = SPI_I2S_ReceiveData(SPI2);

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
  
    /* PCLK2 = HCLK/2 */
    RCC_PCLK2Config(RCC_HCLK_Div2); 

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
  /* Enable DMA1 clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  /* Enable GPIOA, GPIOB and SPI1 clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_SPI1, ENABLE);
  /* Enable SPI2 Periph clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
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

  /* Configure SPI1 pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure SPI2 pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
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
* Input          : - pBuffer, pBuffer1: buffers to be compared.
*                : - BufferLength: buffer's length
* Output         : None
* Return         : PASSED: pBuffer identical to pBuffer1
*                  FAILED: pBuffer differs from pBuffer1
*******************************************************************************/
TestStatus Buffercmp(u8* pBuffer, u8* pBuffer1, u16 BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer != *pBuffer1)
    {
      return FAILED;
    }
    
    pBuffer++;
    pBuffer1++;
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
