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

/* Local includes ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define BufferSize   32

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
I2S_InitTypeDef I2S_InitStructure;
SPI_InitTypeDef SPI_InitStructure;
u16 I2S2_Buffer_Tx[BufferSize] = {0x0102, 0x0304, 0x0506, 0x0708, 0x090A, 0x0B0C,
                                  0x0D0E, 0x0F10, 0x1112, 0x1314, 0x1516, 0x1718,
                                  0x191A, 0x1B1C, 0x1D1E, 0x1F20, 0x2122, 0x2324,
                                  0x2526, 0x2728, 0x292A, 0x2B2C, 0x2D2E, 0x2F30,
                                  0x3132, 0x3334, 0x3536, 0x3738, 0x393A, 0x3B3C,
                                  0x3D3E, 0x3F40};

u16 SPI2_Buffer_Tx[BufferSize] = {0x5152, 0x5354, 0x5556, 0x5758, 0x595A, 0x5B5C,
                                  0x5D5E, 0x5F60, 0x6162, 0x6364, 0x6566, 0x6768,
                                  0x696A, 0x6B6C, 0x6D6E, 0x6F70, 0x7172, 0x7374,
                                  0x7576, 0x7778, 0x797A, 0x7B7C, 0x7D7E, 0x7F80,
                                  0x8182, 0x8384, 0x8586, 0x8788, 0x898A, 0x8B8C,
                                  0x8D8E, 0x8F90};

u16 I2S3_Buffer_Rx[BufferSize];
u16 SPI3_Buffer_Rx[BufferSize];
u8 TxIdx = 0, RxIdx = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
volatile TestStatus TransferStatus3 = FAILED;
ErrorStatus HSEStartUpStatus;

/* Private functions ---------------------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
TestStatus Buffercmp(u16* pBuffer1, u16* pBuffer2, u16 BufferLength);

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

  /* I2S peripheral configuration */
  I2S_InitStructure.I2S_Standard = I2S_Standard_Phillips;
  I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16bextended;
  I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;
  I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_48k;
  I2S_InitStructure.I2S_CPOL = I2S_CPOL_Low;

  /* I2S2 Master Transmitter to I2S3 Slave Receiver communication ------------*/
  /* I2S2 configuration */
  I2S_InitStructure.I2S_Mode = I2S_Mode_MasterTx;
  I2S_Init(SPI2, &I2S_InitStructure);

  /* I2S3 configuration */
  I2S_InitStructure.I2S_Mode = I2S_Mode_SlaveRx;
  I2S_Init(SPI3, &I2S_InitStructure);

  /* Enable the I2S3 */
  I2S_Cmd(SPI3, ENABLE);

  /* Enable the I2S2 */
  I2S_Cmd(SPI2, ENABLE);

  /* Begin the communication in I2S mode */
  while (RxIdx < BufferSize)
  {
    /* Wait the Tx buffer to be empty */
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
    {}
    /* Send a data from I2S2 */
    SPI_I2S_SendData(SPI2, I2S2_Buffer_Tx[TxIdx++]);

    /* Wait the Rx buffer to be full */
    while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET)
    {}
    /* Store the I2S3 received data in the relative data table */
    I2S3_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI3);
  }

  TransferStatus1 = Buffercmp(I2S3_Buffer_Rx, I2S2_Buffer_Tx, BufferSize);
  /* TransferStatus1 = PASSED, if the data transmitted from I2S2 and received by
                               I2S3 are the same 
     TransferStatus1 = FAILED, if the data transmitted from I2S2 and received by
                               I2S3 are different */

  /* Reset TxIdx, RxIdx indexes */
  TxIdx = 0;
  RxIdx = 0;
  
  /* Switch to SPI mode communication ----------------------------------------*/
  /* SPI2 configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI2, &SPI_InitStructure);

  /* SPI3 configuration ------------------------------------------------------*/
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_RxOnly;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
  SPI_Init(SPI3, &SPI_InitStructure);

  /* Enable SPI3 */
  SPI_Cmd(SPI3, ENABLE);
  /* Enable SPI2 */
  SPI_Cmd(SPI2, ENABLE);

  /* Begin the communication in SPI mode */
  while (RxIdx < BufferSize)
  {
    /* Wait the Tx buffer to be empty */
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
    {}
    /* Send a data from SPI2 */
    SPI_I2S_SendData(SPI2, SPI2_Buffer_Tx[TxIdx++]);

    /* Wait the Rx buffer to be full */
    while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET)
    {}
    /* Store the SPI3 received data in the relative data table */
    SPI3_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI3);
  }

  TransferStatus2 = Buffercmp(SPI3_Buffer_Rx, SPI2_Buffer_Tx, BufferSize);
  /* TransferStatus2 = PASSED, if the data transmitted from SPI2 and received by
                               SPI3 are the same
     TransferStatus2 = FAILED, if the data transmitted from SPI2 and received by
                               SPI3 are different */

  /* Reset TxIdx, RxIdx indexes and receive table values */
  for (TxIdx = 0; TxIdx < BufferSize; TxIdx++)
  {
    I2S3_Buffer_Rx[TxIdx] = 0;
  }
  
  TxIdx = 0;
  RxIdx = 0;
      
  /* I2S2 Slave Transmitter to I2S3 Master Receiver communication ------------*/
  /* I2S2 configuration */
  I2S_InitStructure.I2S_Mode = I2S_Mode_SlaveTx;
  I2S_Init(SPI2, &I2S_InitStructure);

  /* I2S3 configuration */
  I2S_InitStructure.I2S_Mode = I2S_Mode_MasterRx;
  I2S_Init(SPI3, &I2S_InitStructure);

  /* Wait the Tx buffer to be empty */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
  {}
  /* Prepare the first data to be sent from the slave */
  SPI_I2S_SendData(SPI2, I2S2_Buffer_Tx[TxIdx++]);

  /* Enable the I2S2 */
  I2S_Cmd(SPI2, ENABLE);

  /* Enable the I2S3 */
  I2S_Cmd(SPI3, ENABLE);

  /* Begin the communication in I2S mode */
  while (RxIdx < BufferSize)
  {
    /* Wait the Rx buffer to be full */
    while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET)
    {}
    /* Store the I2S3 received data in the relative data table */
    I2S3_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI3);

    /* Wait the Tx buffer to be empty */
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
    {}
    /* Send a data from I2S2 */
    SPI_I2S_SendData(SPI2, I2S2_Buffer_Tx[TxIdx++]);
  }

  TransferStatus3 = Buffercmp(I2S3_Buffer_Rx, I2S2_Buffer_Tx, BufferSize);
  /* TransferStatus3 = PASSED, if the data transmitted from I2S2 and received by
                               I2S3 are the same
     TransferStatus3 = FAILED, if the data transmitted from I2S2 and received by
                               I2S3 are different */

  while (1)
  {}
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

  if (HSEStartUpStatus == SUCCESS)
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
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {}

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSYSCLKSource() != 0x08)
    {}
  }

  /* Enable peripheral clocks --------------------------------------------------*/
  /* GPIOA, GPIOB and AFIO clocks enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_AFIO, ENABLE);

  /* SPI2 and SPI3 clocks enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 | RCC_APB1Periph_SPI3, ENABLE);
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

  /* Disable the JTAG interface and enable the SWJ interface */
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

  /* Configure SPI2 pins: CK, WS and SD ---------------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure SPI3 pins: CK and SD ------------------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure SPI3 pins: WS -------------------------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configure the nested vectored interrupt controller.
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
TestStatus Buffercmp(u16* pBuffer1, u16* pBuffer2, u16 BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
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
  {}
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
