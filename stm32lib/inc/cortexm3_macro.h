#if 0
/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : cortexm3_macro.h
* Author             : MCD Application Team
* Version            : V2.0.2
* Date               : 07/11/2008
* Description        : Header file for cortexm3_macro.s.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CORTEXM3_MACRO_H
#define __CORTEXM3_MACRO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_type.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void __WFI(void);
void __WFE(void);
void __SEV(void);
void __ISB(void);
void __DSB(void);
void __DMB(void);
void __SVC(void);
u32 __MRS_CONTROL(void);
void __MSR_CONTROL(u32 Control);
u32 __MRS_PSP(void);
void __MSR_PSP(u32 TopOfProcessStack);
u32 __MRS_MSP(void);
void __MSR_MSP(u32 TopOfMainStack);
void __RESETPRIMASK(void);
void __SETPRIMASK(void);
u32 __READ_PRIMASK(void);
void __RESETFAULTMASK(void);
void __SETFAULTMASK(void);
u32 __READ_FAULTMASK(void);
void __BASEPRICONFIG(u32 NewPriority);
u32 __GetBASEPRI(void);
u16 __REV_HalfWord(u16 Data);
u32 __REV_Word(u32 Data);

#endif /* __CORTEXM3_MACRO_H */
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/

/******************** (C) COPYRIGHT 2008 Andreas Fritiofson ********************
* File Name          : cortexm3_macro.h
* Author             : Andreas Fritiofson
* Version            : V1.0
* Date               : 30/04/2008
* Description        : Instruction wrappers for special Cortex-M3 instructions.
********************************************************************************
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CORTEXM3_MACRO_H
#define __CORTEXM3_MACRO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_type.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
static inline void __WFI(void) {
    asm volatile ( "WFI \n" );
}
static inline void __WFE(void) {
    asm volatile ( "WFE \n" );
}
static inline void __SEV(void) {
    asm volatile ( "SEV \n" );
}
static inline void __ISB(void) {
    asm volatile ( "ISB \n" );
}
static inline void __DSB(void) {
    asm volatile ( "DSB \n" );
}
static inline void __DMB(void) {
    asm volatile ( "DMB \n" );
}
static inline void __SVC(void) {
    asm volatile ( "SVC 0x01 \n" );
}
static inline u32 __MRS_CONTROL(void) {
    u32 x;
    asm volatile ( "MRS %0, control \n" : "=r" (x));
    return x;
}
static inline void __MSR_CONTROL(u32 Control) {
    asm volatile (
            "MSR control, %0 \n"
            "ISB \n"
            : : "r" (Control));
}
static inline u32 __MRS_PSP(void) {
    u32 x;
    asm volatile ( "MRS %0, psp \n" : "=r" (x));
    return x;
}
static inline void __MSR_PSP(u32 TopOfProcessStack) {
    asm volatile ( "MSR psp, %0 \n" : : "r" (TopOfProcessStack));
}
static inline u32 __MRS_MSP(void) {
    u32 x;
    asm volatile ( "MRS %0, msp \n" : "=r" (x));
    return x;
}
static inline void __MSR_MSP(u32 TopOfMainStack) {
    asm volatile ( "MSR msp, %0 \n" : : "r" (TopOfMainStack));
}
static inline void __SETPRIMASK(void) {
    asm volatile ( "CPSID i \n" );
}
static inline void __RESETPRIMASK(void) {
    asm volatile ( "CPSIE i \n" );
}
static inline void __SETFAULTMASK(void) {
    asm volatile ( "CPSID f \n" );
}
static inline void __RESETFAULTMASK(void) {
    asm volatile ( "CPSIE f \n" );
}
static inline void __BASEPRICONFIG(u32 NewPriority) {
    asm volatile ( "MSR basepri, %0 \n" : : "r" (NewPriority));
}
static inline u32 __GetBASEPRI(void) {
    u32 x;
    asm volatile ( "MRS %0, basepri_max \n" : "=r" (x));
    return x;
}
static inline u16 __REV_HalfWord(u16 Data) {
    u16 x;
    asm volatile ( "REV16 %0, %1 \n" : "=r" (x) : "r" (Data));
    return x;
}
static inline u32 __REV_Word(u32 Data) {
    u32 x;
    asm volatile ( "REV %0, %1 \n" : "=r" (x) : "r" (Data));
    return x;
}

#endif /* __CORTEXM3_MACRO_H */

/******************* (C) COPYRIGHT 2008 Andreas Fritiofson *****END OF FILE****/

