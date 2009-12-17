/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Main program body.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ErrorStatus HSEStartUpStatus;

#ifdef USE_STM3210B_EVAL
u16 BKPDataReg[BKP_DR_NUMBER] =
  {
    BKP_DR1, BKP_DR2, BKP_DR3, BKP_DR4, BKP_DR5, BKP_DR6, BKP_DR7, BKP_DR8,
    BKP_DR9, BKP_DR10
  };
#elif defined USE_STM3210E_EVAL
u16 BKPDataReg[BKP_DR_NUMBER] =
  {
    BKP_DR1, BKP_DR2, BKP_DR3, BKP_DR4, BKP_DR5, BKP_DR6, BKP_DR7, BKP_DR8,
    BKP_DR9, BKP_DR10, BKP_DR11, BKP_DR12, BKP_DR13, BKP_DR14, BKP_DR15, BKP_DR16,
    BKP_DR17, BKP_DR18, BKP_DR19, BKP_DR20, BKP_DR21, BKP_DR22, BKP_DR23, BKP_DR24,
    BKP_DR25, BKP_DR26, BKP_DR27, BKP_DR28, BKP_DR29, BKP_DR30, BKP_DR31, BKP_DR32,
    BKP_DR33, BKP_DR34, BKP_DR35, BKP_DR36, BKP_DR37, BKP_DR38, BKP_DR39, BKP_DR40,
    BKP_DR41, BKP_DR42
  };  
#endif /* USE_STM3210B_EVAL */

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void WriteToBackupReg(u16 FirstBackupData);
u32 CheckBackupReg(u16 FirstBackupData);

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : main
* Description    : Main program.
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
    
  /* GPIO configuration */
  GPIO_Configuration();

  /* Enable PWR and BKP clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

  /* Enable write access to Backup domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Clear Tamper pin Event(TE) pending flag */
  BKP_ClearFlag();

  /* Tamper pin active on low level */
  BKP_TamperPinLevelConfig(BKP_TamperPinLevel_Low);

  /* Enable Tamper interrupt */
  BKP_ITConfig(ENABLE);

  /* Enable Tamper pin */
  BKP_TamperPinCmd(ENABLE);
   
  /* Write data to Backup DRx registers */
  WriteToBackupReg(0xA53C);
  /* Check if the written data are correct */
  if(CheckBackupReg(0xA53C) == 0x00)
  {
    /* Turn on led connected to GPIO_LED Pin6 */
    GPIO_Write(GPIO_LED, GPIO_Pin_6);
  }
  else
  {
    /* Turn on led connected to GPIO_LED Pin7 */
    GPIO_Write(GPIO_LED, GPIO_Pin_7);
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

  /* Enable GPIO_LED clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_LED, ENABLE);
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

  /* Configure GPIO_LED Pin 6, Pin 7, Pin 8 and Pin 9 as Output push-pull ----*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIO_LED, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures NVIC and Vector Table base location.
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

  /* Enable TAMPER IRQChannel */
  NVIC_InitStructure.NVIC_IRQChannel = TAMPER_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
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

/*******************************************************************************
* Function Name  : WriteToBackupReg
* Description    : Writes data Backup DRx registers.
* Input          : FirstBackupData: data to be written to Backup data registers.
* Output         : None
* Return         : None
*******************************************************************************/
void WriteToBackupReg(u16 FirstBackupData)
{
  u32 index = 0;

  for (index = 0; index < BKP_DR_NUMBER; index++)
  {
    BKP_WriteBackupRegister(BKPDataReg[index], FirstBackupData + (index * 0x5A));
  }  
}

/*******************************************************************************
* Function Name  : CheckBackupReg
* Description    : Checks if the Backup DRx registers values are correct or not.
* Input          : FirstBackupData: data to be compared with Backup data registers.
* Output         : None
* Return         : - 0: All Backup DRx registers values are correct
*                  - Value different from 0: Number of the first Backup register
*                    which value is not correct
*******************************************************************************/
u32 CheckBackupReg(u16 FirstBackupData)
{
  u32 index = 0;

  for (index = 0; index < BKP_DR_NUMBER; index++)
  {
    if (BKP_ReadBackupRegister(BKPDataReg[index]) != (FirstBackupData + (index * 0x5A)))
    {
      return (index + 1);
    }
  }

  return 0;  
}

/*******************************************************************************
* Function Name  : IsBackupRegReset
* Description    : Checks if the Backup DRx registers are reset or not.
* Input          : None
* Output         : None
* Return         : - 0: All Backup DRx registers are reset
*                  - Value different from 0: Number of the first Backup register
*                    not reset
*******************************************************************************/
u32 IsBackupRegReset(void)
{
  u32 index = 0;

  for (index = 0; index < BKP_DR_NUMBER; index++)
  {
    if (BKP_ReadBackupRegister(BKPDataReg[index]) != 0x0000)
    {
      return (index + 1);
    }
  }

  return 0;  
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
