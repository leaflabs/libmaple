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
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define StartAddr  ((u32)0x08006000)
#define EndAddr    ((u32)0x08008000)
 
/* Uncomment this line to Enable Write Protection */
//#define WriteProtection_Enable
/* Uncomment this line to Disable Write Protection */
#define WriteProtection_Disable

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/  
u32 EraseCounter, Address;
u16 Data;
vu32 WRPR_Value = 0xFFFFFFFF, ProtectedPages = 0x0;
vu8 NbrOfPage;
volatile FLASH_Status FLASHStatus;
volatile TestStatus MemoryProgramStatus;
ErrorStatus HSEStartUpStatus;

/* Private function prototypes -----------------------------------------------*/
void NVIC_Configuration(void);
void RCC_Configuration(void);
    
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

  FLASHStatus = FLASH_COMPLETE;
  MemoryProgramStatus = PASSED;  
  Data = 0x1753;
  EraseCounter = 0x0;
  
  /* RCC Configuration */
  RCC_Configuration();  
  
  /* NVIC Configuration */
  NVIC_Configuration();

  /* Unlock the Flash Program Erase controller */  
  FLASH_Unlock();

  /* Define the number of page to be erased */
  NbrOfPage = (EndAddr - StartAddr) / FLASH_PAGE_SIZE;
  
  FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP|FLASH_FLAG_PGERR |FLASH_FLAG_WRPRTERR);

  /* Get pages write protection status */
  WRPR_Value = FLASH_GetWriteProtectionOptionByte();
  ProtectedPages = WRPR_Value & 0x000000C0;

#ifdef WriteProtection_Disable
  if (ProtectedPages == 0x00)
  {/* Pages are write protected */

    /* Disable the write protection */
    FLASHStatus = FLASH_EraseOptionBytes();

    /* Generate System Reset to load the new option byte values */
    NVIC_GenerateSystemReset();
  }
#else
 #ifdef WriteProtection_Enable
  
  if (ProtectedPages != 0x00)
  {/* Pages not write protected */
    #ifdef USE_STM3210B_EVAL
    /* Enable the pages write protection */
    FLASHStatus = FLASH_EnableWriteProtection(FLASH_WRProt_Pages24to27 |FLASH_WRProt_Pages28to31);    
    #else   
    /* Enable the pages write protection */
    FLASHStatus = FLASH_EnableWriteProtection(FLASH_WRProt_Pages12to13 |FLASH_WRProt_Pages14to15);
    #endif
    /* Generate System Reset to load the new option byte values */
    NVIC_GenerateSystemReset();
  }
 #endif
#endif
  
  /* If Pages are not write protected, perform erase and program operations
     Else nothing */
  if (ProtectedPages != 0x00)
  {
    /* Clear All pending flags */
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP|FLASH_FLAG_PGERR |FLASH_FLAG_WRPRTERR);	

    /* erase the FLASH pages */
    for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
    {
      FLASHStatus = FLASH_ErasePage(StartAddr + (FLASH_PAGE_SIZE * EraseCounter));
    }
  
    /* FLASH Half Word program of data 0x1753 at addresses defined by  StartAddr and EndAddr */
    Address = StartAddr;

    while((Address < EndAddr) && (FLASHStatus == FLASH_COMPLETE))
    {
      FLASHStatus = FLASH_ProgramHalfWord(Address, Data);
      Address = Address + 2;
    }

    /* Check the corectness of written data */
    Address = StartAddr;

    while((Address < EndAddr) && (MemoryProgramStatus != FAILED))
    {
      if((*(vu16*) Address) != Data)
      {
        MemoryProgramStatus = FAILED;
      }
      Address += 2;
    }
 
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

  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
