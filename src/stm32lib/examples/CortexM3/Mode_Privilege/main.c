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
#include "stm32f10x_lib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SP_PROCESS_SIZE             0x200  /* Process stack size */
#define SP_PROCESS                  0x02   /* Process stack */
#define SP_MAIN                     0x00   /* Main stack */
#define THREAD_MODE_PRIVILEGED      0x00   /* Thread mode has privileged access */
#define THREAD_MODE_UNPRIVILEGED    0x01   /* Thread mode has unprivileged access */

/* Private macro -------------------------------------------------------------*/ 
/* Private variables ---------------------------------------------------------*/
ErrorStatus HSEStartUpStatus;
vu8 PSPMemAlloc[SP_PROCESS_SIZE];
vu32 Index = 0, PSPValue = 0, CurrentStack = 0, ThreadMode = 0;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);

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
   
  /* Clock configuration */
  RCC_Configuration();

  /* NVIC configuration */
  NVIC_Configuration();

    
/* Switch Thread mode Stack from Main to Process -----------------------------*/
  /* Initialize memory reserved for Process Stack */
  for(Index = 0; Index < SP_PROCESS_SIZE; Index++)
  {
    PSPMemAlloc[Index] = 0x00;
  }

  /* Set Process stack value */ 
  __MSR_PSP((u32)PSPMemAlloc + SP_PROCESS_SIZE);
  
  /* Select Process Stack as Thread mode Stack */
  __MSR_CONTROL(SP_PROCESS);

  /* Get the Thread mode stack used */
  if((__MRS_CONTROL() & 0x02) == SP_MAIN)
  {
    /* Main stack is used as the current stack */
	CurrentStack = SP_MAIN;
  }
  else
  {
    /* Process stack is used as the current stack */
	CurrentStack = SP_PROCESS;
	
	/* Get process stack pointer value */
	PSPValue = __MRS_PSP();	
  }
  
/* Switch Thread mode from privileged to unprivileged ------------------------*/
  /* Thread mode has unprivileged access */
  __MSR_CONTROL(THREAD_MODE_UNPRIVILEGED | SP_PROCESS);
  /* Unprivileged access mainly affect ability to:
      - Use or not use certain instructions such as MSR fields
	  - Access System Control Space (SCS) registers such as NVIC and SysTick */

  /* Check Thread mode privilege status */
  if((__MRS_CONTROL() & 0x01) == THREAD_MODE_PRIVILEGED)
  {
    /* Thread mode has privileged access  */
	ThreadMode = THREAD_MODE_PRIVILEGED;
  }
  else
  {
    /* Thread mode has unprivileged access*/
	ThreadMode = THREAD_MODE_UNPRIVILEGED;
  }

/* Switch back Thread mode from unprivileged to privileged -------------------*/  
  /* Try to switch back Thread mode to privileged (Not possible, this can be
     done only in Handler mode) */
  __MSR_CONTROL(THREAD_MODE_PRIVILEGED | SP_PROCESS);

  /* Generate a system call exception, and in the ISR switch back Thread mode
    to privileged */
  __SVC();

  /* Check Thread mode privilege status */
  if((__MRS_CONTROL() & 0x01) == THREAD_MODE_PRIVILEGED)
  {
    /* Thread mode has privileged access  */
	ThreadMode = THREAD_MODE_PRIVILEGED;
  }
  else
  {
    /* Thread mode has unprivileged access*/
	ThreadMode = THREAD_MODE_UNPRIVILEGED;
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

    /* Flash 0 wait state */
    FLASH_SetLatency(FLASH_Latency_0);
 
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK */
    RCC_PCLK1Config(RCC_HCLK_Div1);

    /* Select HSE as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);

    /* Wait till HSE is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x04)
    {
    }
  }
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

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
