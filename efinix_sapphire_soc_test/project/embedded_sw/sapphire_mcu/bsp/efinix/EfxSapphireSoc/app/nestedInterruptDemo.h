 /*******************************************************************************
*
* @file nestedInterruptDemo.h
*
* @brief Header file defines timer controller and interrupt depending on the 
*        availability of the current system.
*
*******************************************************************************/
 
 #pragma once

#ifdef SYSTEM_USER_TIMER_0_CTRL
#define SYSTEM_PLIC_TIMER_INTERRUPTS_0 SYSTEM_PLIC_SYSTEM_USER_TIMER_0_INTERRUPTS_0
#define TIMER_CTRL_0 SYSTEM_USER_TIMER_0_CTRL 
#endif

#ifdef SYSTEM_USER_TIMER_1_CTRL
#define SYSTEM_PLIC_TIMER_INTERRUPTS_1 SYSTEM_PLIC_SYSTEM_USER_TIMER_1_INTERRUPTS_0
#define TIMER_CTRL_1 SYSTEM_USER_TIMER_1_CTRL 
#endif
