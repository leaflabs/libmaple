/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The  above copyright  notice and  this permission  notice  shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file scb.h
 * @brief System control block header
 */

#include "libmaple_types.h"

#ifndef _SCB_H_
#define _SCB_H_

/*
 * Register map and base pointer
 */

/** System control block register map type */
typedef struct scb_reg_map {
    __io uint32 CPUID;   /**< CPU ID Base Register */
    __io uint32 ICSR;    /**< Interrupt Control State Register */
    __io uint32 VTOR;    /**< Vector Table Offset Register */
    __io uint32 AIRCR;   /**< Application Interrupt / Reset Control Register */
    __io uint32 SCR;     /**< System Control Register */
    __io uint32 CCR;     /**< Configuration and Control Register */
    __io uint8  SHP[12]; /**< System Handler Priority Registers
                              (4-7, 8-11, 12-15) */
    __io uint32 SHCSR;   /**< System Handler Control and State Register */
    __io uint32 CFSR;    /**< Configurable Fault Status Register */
    __io uint32 HFSR;    /**< Hard Fault Status Register */
    /* DFSR is not documented by ST in PM0056 (as of Revision 4), but
     * there's a 4 byte hole in the SCB register map docs right where
     * it belongs.  Since it's specified as "always implemented" in
     * the ARM v7-M ARM, I'm assuming its absence is a bug in the ST
     * doc, but I haven't proven it. [mbolivar] */
    __io uint32 DFSR;    /**< Debug Fault Status Register */
    __io uint32 MMFAR;   /**< Mem Manage Address Register */
    __io uint32 BFAR;    /**< Bus Fault Address Register */
#if 0
    /* The following registers are implementation-defined according to
     * ARM v7-M, and I can't find evidence of their existence in ST's
     * docs.  I'm removing them.  Feel free to yell at me if they do
     * exist. [mbolivar]
     */
    __io uint32 AFSR;    /**< Auxiliary Fault Status Register */
    __io uint32 PFR[2];  /**< Processor Feature Register */
    __io uint32 DFR;     /**< Debug Feature Register */
    __io uint32 AFR;     /**< Auxiliary Feature Register */
    __io uint32 MMFR[4]; /**< Memory Model Feature Register */
    __io uint32 ISAR[5]; /**< ISA Feature Register */
#endif
} scb_reg_map;

/** System control block register map base pointer */
#define SCB_BASE                        ((struct scb_reg_map*)0xE000ED00)

/*
 * Register bit definitions
 */

/* No SCB_REG_FIELD_BIT macros as the relevant addresses are not in a
 * bit-band region. */

/* CPUID base register (SCB_CPUID) */

#define SCB_CPUID_IMPLEMENTER           (0xFF << 24)
#define SCB_CPUID_VARIANT               (0xF << 20)
#define SCB_CPUID_CONSTANT              (0xF << 16)
#define SCB_CPUID_PARTNO                (0xFFF << 4)
#define SCB_CPUID_REVISION              0xF

/* Interrupt control state register (SCB_ICSR) */

#define SCB_ICSR_NMIPENDSET             BIT(31)
#define SCB_ICSR_PENDSVSET              BIT(28)
#define SCB_ICSR_PENDSVCLR              BIT(27)
#define SCB_ICSR_PENDSTSET              BIT(26)
#define SCB_ICSR_PENDSTCLR              BIT(25)
#define SCB_ICSR_ISRPENDING             BIT(22)
#define SCB_ICSR_VECTPENDING            (0x3FF << 12)
#define SCB_ICSR_RETOBASE               BIT(11)
#define SCB_ICSR_VECTACTIVE             0xFF

/* Vector table offset register (SCB_VTOR) */

#define SCB_VTOR_TBLOFF                 (0x1FFFFF << 9)

/* Application interrupt and reset control register (SCB_AIRCR) */

#define SCB_AIRCR_VECTKEYSTAT           (0x5FA << 16)
#define SCB_AIRCR_VECTKEY               (0x5FA << 16)
#define SCB_AIRCR_ENDIANNESS            BIT(15)
#define SCB_AIRCR_PRIGROUP              (0x3 << 8)
#define SCB_AIRCR_SYSRESETREQ           BIT(2)
#define SCB_AIRCR_VECTCLRACTIVE         BIT(1)
#define SCB_AIRCR_VECTRESET             BIT(0)

/* System control register (SCB_SCR) */

#define SCB_SCR_SEVONPEND               BIT(4)
#define SCB_SCR_SLEEPDEEP               BIT(2)
#define SCB_SCR_SLEEPONEXIT             BIT(1)

/* Configuration and Control Register (SCB_CCR) */

#define SCB_CCR_STKALIGN                BIT(9)
#define SCB_CCR_BFHFNMIGN               BIT(8)
#define SCB_CCR_DIV_0_TRP               BIT(4)
#define SCB_CCR_UNALIGN_TRP             BIT(3)
#define SCB_CCR_USERSETMPEND            BIT(1)
#define SCB_CCR_NONBASETHRDENA          BIT(0)

/* System handler priority registers (SCB_SHPRx) */

#define SCB_SHPR1_PRI6                  (0xFF << 16)
#define SCB_SHPR1_PRI5                  (0xFF << 8)
#define SCB_SHPR1_PRI4                  0xFF

#define SCB_SHPR2_PRI11                 (0xFF << 24)

#define SCB_SHPR3_PRI15                 (0xFF << 24)
#define SCB_SHPR3_PRI14                 (0xFF << 16)

/* System Handler Control and state register (SCB_SHCSR) */

#define SCB_SHCSR_USGFAULTENA           BIT(18)
#define SCB_SHCSR_BUSFAULTENA           BIT(17)
#define SCB_SHCSR_MEMFAULTENA           BIT(16)
#define SCB_SHCSR_SVCALLPENDED          BIT(15)
#define SCB_SHCSR_BUSFAULTPENDED        BIT(14)
#define SCB_SHCSR_MEMFAULTPENDED        BIT(13)
#define SCB_SHCSR_USGFAULTPENDED        BIT(12)
#define SCB_SHCSR_SYSTICKACT            BIT(11)
#define SCB_SHCSR_PENDSVACT             BIT(10)
#define SCB_SHCSR_MONITORACT            BIT(8)
#define SCB_SHCSR_SVCALLACT             BIT(7)
#define SCB_SHCSR_USGFAULTACT           BIT(3)
#define SCB_SHCSR_BUSFAULTACT           BIT(1)
#define SCB_SHCSR_MEMFAULTACT           BIT(0)

/* Configurable fault status register (SCB_CFSR) */

#define SCB_CFSR_DIVBYZERO              BIT(25)
#define SCB_CFSR_UNALIGNED              BIT(24)
#define SCB_CFSR_NOCP                   BIT(19)
#define SCB_CFSR_INVPC                  BIT(18)
#define SCB_CFSR_INVSTATE               BIT(17)
#define SCB_CFSR_UNDEFINSTR             BIT(16)
#define SCB_CFSR_BFARVALID              BIT(15)
#define SCB_CFSR_STKERR                 BIT(12)
#define SCB_CFSR_UNSTKERR               BIT(11)
#define SCB_CFSR_IMPRECISERR            BIT(10)
#define SCB_CFSR_PRECISERR              BIT(9)
#define SCB_CFSR_IBUSERR                BIT(8)
#define SCB_CFSR_MMARVALID              BIT(7)
#define SCB_CFSR_MSTKERR                BIT(4)
#define SCB_CFSR_MUNSTKERR              BIT(3)
#define SCB_CFSR_DACCVIOL               BIT(1)
#define SCB_CFSR_IACCVIOL               BIT(0)

/* Hard Fault Status Register (SCB_HFSR) */

#define SCB_HFSR_DEBUG_VT               BIT(31)
#define SCB_CFSR_FORCED                 BIT(30)
#define SCB_CFSR_VECTTBL                BIT(1)

/* Debug Fault Status Register */

/* Not specified by PM0056, but required by ARM.  The bit definitions
 * here are based on the names given in the ARM v7-M ARM. */

#define SCB_DFSR_EXTERNAL               BIT(4)
#define SCB_DFSR_VCATCH                 BIT(3)
#define SCB_DFSR_DWTTRAP                BIT(2)
#define SCB_DFSR_BKPT                   BIT(1)
#define SCB_DFSR_HALTED                 BIT(0)

#endif
