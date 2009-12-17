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
#define RAM_BASE       0x20000000
#define RAM_BB_BASE    0x22000000
 
/* Private macro -------------------------------------------------------------*/
#define  Var_ResetBit_BB(VarAddr, BitNumber)    \
          (*(vu32 *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 0)
   
#define Var_SetBit_BB(VarAddr, BitNumber)       \
          (*(vu32 *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 1)

#define Var_GetBit_BB(VarAddr, BitNumber)       \
          (*(vu32 *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)))
   
/* Private variables ---------------------------------------------------------*/
ErrorStatus HSEStartUpStatus;
vu32 Var, VarAddr = 0, VarBitValue = 0;

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
   
   Var = 0x00005AA5;
   
  /* Clock configuration */
  RCC_Configuration();

  /* NVIC configuration */
  NVIC_Configuration();

/* A mapping formula shows how to reference each word in the alias region to a corresponding
bit in the bit-band region. The mapping formula is:
  bit_word_addr = bit_band_base + (byte_offset x 32) + (bit_number × 4)

where:
   - bit_word_addr: is the address of the word in the alias memory region that maps to the
                    targeted bit.
   - bit_band_base is the starting address of the alias region
   - byte_offset is the number of the byte in the bit-band region that contains the targeted bit
   - bit_number is the bit position (0-7) of the targeted bit */

/* Get the variable address --------------------------------------------------*/ 
  VarAddr = (u32)&Var; 

/* Modify variable bit using bit-band access ---------------------------------*/
  /* Modify Var variable bit 0 -----------------------------------------------*/
  Var_ResetBit_BB(VarAddr, 0);  /* Var = 0x00005AA4 */
  Var_SetBit_BB(VarAddr, 0);    /* Var = 0x00005AA5 */
  
  /* Modify Var variable bit 11 -----------------------------------------------*/
  Var_ResetBit_BB(VarAddr, 11);             /* Var = 0x000052A5 */
  /* Get Var variable bit 11 value */
  VarBitValue = Var_GetBit_BB(VarAddr, 11); /* VarBitValue = 0x00000000 */
  
  Var_SetBit_BB(VarAddr, 11);               /* Var = 0x00005AA5 */
  /* Get Var variable bit 11 value */
  VarBitValue = Var_GetBit_BB(VarAddr, 11);    /* VarBitValue = 0x00000001 */
  
  /* Modify Var variable bit 31 -----------------------------------------------*/
  Var_SetBit_BB(VarAddr, 31);               /* Var = 0x80005AA5 */
  /* Get Var variable bit 31 value */
  VarBitValue = Var_GetBit_BB(VarAddr, 31); /* VarBitValue = 0x00000001 */
    
  Var_ResetBit_BB(VarAddr, 31);             /* Var = 0x00005AA5 */
  /* Get Var variable bit 31 value */
  VarBitValue = Var_GetBit_BB(VarAddr, 31); /* VarBitValue = 0x00000000 */
        
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
