/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : WAIT2.h
**     Project     : sender_can_uart_KE06
**     Processor   : MKE06Z128VLK4
**     Component   : Wait
**     Version     : Component 01.069, Driver 01.00, CPU db: 3.00.000
**     Repository  : My Components
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-06-18, 00:01, # CodeGen: 3
**     Abstract    :
**          Implements busy waiting routines.
**     Settings    :
**          Component name                                 : WAIT2
**          SDK                                            : KSDK1
**          Manual Clock Values                            : Disabled
**          Delay100usFunction                             : Delay100US
**          RTOS                                           : Disabled
**          Watchdog                                       : Disabled
**     Contents    :
**         Wait10Cycles   - void WAIT2_Wait10Cycles(void);
**         Wait100Cycles  - void WAIT2_Wait100Cycles(void);
**         WaitCycles     - void WAIT2_WaitCycles(uint16_t cycles);
**         WaitLongCycles - void WAIT2_WaitLongCycles(uint32_t cycles);
**         Waitms         - void WAIT2_Waitms(uint16_t ms);
**         Waitus         - void WAIT2_Waitus(uint16_t us);
**         Waitns         - void WAIT2_Waitns(uint16_t ns);
**         WaitOSms       - void WAIT2_WaitOSms(void);
**
**     License   : Open Source (LGPL)
**     Copyright : Erich Styger, 2013-2016, all rights reserved.
**     Web       : www.mcuoneclipse.com
**     This an open source software implementing waiting routines using Processor Expert.
**     This is a free software and is opened for education,  research  and commercial developments under license policy of following terms:
**     * This is a free software and there is NO WARRANTY.
**     * No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
**     * Redistributions of source code must retain the above copyright notice.
** ###################################################################*/
/*!
** @file WAIT2.h
** @version 01.00
** @brief
**          Implements busy waiting routines.
*/         
/*!
**  @addtogroup WAIT2_module WAIT2 module documentation
**  @{
*/         

#ifndef __WAIT2_H
#define __WAIT2_H

/* MODULE WAIT2. */

/* Include inherited beans */
#include "KSDK1.h"

#if KSDK1_SDK_VERSION_USED == KSDK1_SDK_VERSION_NONE
/* Include shared modules, which are used for whole project */
  #include "PE_Types.h"
  #include "PE_Error.h"
  #include "PE_Const.h"
  #include "IO_Map.h"
  #include "Cpu.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


#if KSDK1_SDK_VERSION_USED != KSDK1_SDK_VERSION_NONE
  extern uint32_t SystemCoreClock; /* clock frequency variable defined system_<device>.h of the SDK */
  #define WAIT2_INSTR_CLOCK_HZ       SystemCoreClock  /* core clock frequency in Hz */
#else
  #define WAIT2_INSTR_CLOCK_HZ       CPU_CORE_CLK_HZ /* for Kinetis, use core clock as base for instruction execution */
#endif
#define WAIT2_NofCyclesMs(ms, hz)  ((ms)*((hz)/1000)) /* calculates the needed cycles based on bus clock frequency */
#define WAIT2_NofCyclesUs(us, hz)  ((us)*(((hz)/1000)/1000)) /* calculates the needed cycles based on bus clock frequency */
#define WAIT2_NofCyclesNs(ns, hz)  (((ns)*(((hz)/1000)/1000))/1000) /* calculates the needed cycles based on bus clock frequency */


#define WAIT2_WAIT_C(cycles) \
     ( (cycles)<=10 ? \
          WAIT2_Wait10Cycles() \
        : WAIT2_WaitCycles((uint16_t)cycles) \
      )                                      /*!< wait for some cycles */


void WAIT2_Wait10Cycles(void);
/*
** ===================================================================
**     Method      :  WAIT2_Wait10Cycles (component Wait)
**     Description :
**         Wait for 10 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void WAIT2_Wait100Cycles(void);
/*
** ===================================================================
**     Method      :  WAIT2_Wait100Cycles (component Wait)
**     Description :
**         Wait for 100 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void WAIT2_WaitCycles(uint16_t cycles);
/*
** ===================================================================
**     Method      :  WAIT2_WaitCycles (component Wait)
**     Description :
**         Wait for a specified number of CPU cycles (16bit data type).
**     Parameters  :
**         NAME            - DESCRIPTION
**         cycles          - The number of cycles to wait.
**     Returns     : Nothing
** ===================================================================
*/

void WAIT2_Waitms(uint16_t ms);
/*
** ===================================================================
**     Method      :  WAIT2_Waitms (component Wait)
**     Description :
**         Wait for a specified time in milliseconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ms              - How many milliseconds the function has to
**                           wait
**     Returns     : Nothing
** ===================================================================
*/

/* we are having a static clock configuration: implement as macro/inlined version */
#define WAIT2_Waitus(us)  \
        /*lint -save -e(505,506,522) Constant value Boolean, Redundant left argument to comma. */\
       (  ((WAIT2_NofCyclesUs((us),WAIT2_INSTR_CLOCK_HZ)==0)||(us)==0) ? \
          (void)0 : \
          ( ((us)/1000)==0 ? (void)0 : WAIT2_Waitms((uint16_t)((us)/1000))) \
          , (WAIT2_NofCyclesUs(((us)%1000), WAIT2_INSTR_CLOCK_HZ)==0) ? (void)0 : \
            WAIT2_WAIT_C(WAIT2_NofCyclesUs(((us)%1000), WAIT2_INSTR_CLOCK_HZ)) \
       /*lint -restore */\
       )
/*
** ===================================================================
**     Method      :  WAIT2_Waitus (component Wait)
**     Description :
**         Wait for a specified time in microseconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         us              - How many microseconds the function has to
**                           wait
**     Returns     : Nothing
** ===================================================================
*/

/* we are having a static clock configuration: implement as macro/inlined version */
#define WAIT2_Waitns(ns)  \
        /*lint -save -e(505,506,522) Constant value Boolean, Redundant left argument to comma. */\
       (  ((WAIT2_NofCyclesNs((ns), WAIT2_INSTR_CLOCK_HZ)==0)||(ns)==0) ? \
          (void)0 : \
          WAIT2_Waitus((ns)/1000) \
          , (WAIT2_NofCyclesNs((ns)%1000, WAIT2_INSTR_CLOCK_HZ)==0) ? \
              (void)0 : \
              WAIT2_WAIT_C(WAIT2_NofCyclesNs(((ns)%1000), WAIT2_INSTR_CLOCK_HZ)) \
       /*lint -restore */\
       )
/*
** ===================================================================
**     Method      :  WAIT2_Waitns (component Wait)
**     Description :
**         Wait for a specified time in nano seconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ns              - How many ns the function has to wait
**     Returns     : Nothing
** ===================================================================
*/

#define WAIT2_WaitOSms(ms) \
  WAIT2_Waitms(ms) /* no RTOS used, so use normal wait */
/*
** ===================================================================
**     Method      :  WAIT2_WaitOSms (component Wait)
**     Description :
**         If an RTOS is enabled, this routine will use a non-blocking
**         wait method. Otherwise it will do a busy/blocking wait.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#ifdef __cplusplus
}  /* extern "C" */
#endif

void WAIT2_WaitLongCycles(uint32_t cycles);
/*
** ===================================================================
**     Method      :  WAIT2_WaitLongCycles (component Wait)
**     Description :
**         Wait for a specified number of CPU cycles (32bit data type).
**     Parameters  :
**         NAME            - DESCRIPTION
**         cycles          - The number of cycles to wait.
**     Returns     : Nothing
** ===================================================================
*/

/* END WAIT2. */

#endif
/* ifndef __WAIT2_H */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
