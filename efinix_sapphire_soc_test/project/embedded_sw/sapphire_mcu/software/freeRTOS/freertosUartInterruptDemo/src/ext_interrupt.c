////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2013-2023 Efinix Inc. All rights reserved.              
//
// This   document  contains  proprietary information  which   is        
// protected by  copyright. All rights  are reserved.  This notice       
// refers to original work by Efinix, Inc. which may be derivitive       
// of other work distributed under license of the authors.  In the       
// case of derivative work, nothing in this notice overrides the         
// original author's license agreement.  Where applicable, the           
// original license agreement is included in it's original               
// unmodified form immediately below this header.                        
//                                                                       
// WARRANTY DISCLAIMER.                                                  
//     THE  DESIGN, CODE, OR INFORMATION ARE PROVIDED “AS IS” AND        
//     EFINIX MAKES NO WARRANTIES, EXPRESS OR IMPLIED WITH               
//     RESPECT THERETO, AND EXPRESSLY DISCLAIMS ANY IMPLIED WARRANTIES,  
//     INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF          
//     MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR    
//     PURPOSE.  SOME STATES DO NOT ALLOW EXCLUSIONS OF AN IMPLIED       
//     WARRANTY, SO THIS DISCLAIMER MAY NOT APPLY TO LICENSEE.           
//                                                                       
// LIMITATION OF LIABILITY.                                              
//     NOTWITHSTANDING ANYTHING TO THE CONTRARY, EXCEPT FOR BODILY       
//     INJURY, EFINIX SHALL NOT BE LIABLE WITH RESPECT TO ANY SUBJECT    
//     MATTER OF THIS AGREEMENT UNDER TORT, CONTRACT, STRICT LIABILITY   
//     OR ANY OTHER LEGAL OR EQUITABLE THEORY (I) FOR ANY INDIRECT,      
//     SPECIAL, INCIDENTAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES OF ANY    
//     CHARACTER INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF      
//     GOODWILL, DATA OR PROFIT, WORK STOPPAGE, OR COMPUTER FAILURE OR   
//     MALFUNCTION, OR IN ANY EVENT (II) FOR ANY AMOUNT IN EXCESS, IN    
//     THE AGGREGATE, OF THE FEE PAID BY LICENSEE TO EFINIX HEREUNDER    
//     (OR, IF THE FEE HAS BEEN WAIVED, $100), EVEN IF EFINIX SHALL HAVE 
//     BEEN INFORMED OF THE POSSIBILITY OF SUCH DAMAGES.  SOME STATES DO 
//     NOT ALLOW THE EXCLUSION OR LIMITATION OF INCIDENTAL OR            
//     CONSEQUENTIAL DAMAGES, SO THIS LIMITATION AND EXCLUSION MAY NOT   
//     APPLY TO LICENSEE.                                                
//
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
*
* @file ext_interrupt.c
*
* @brief This file contain various interrupt handler function for different situation. 
*
******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"
#include "bsp.h"
#include "plic.h"
#include "riscv.h"

/******************************************************************************
*
* @brief This function handles the system crash scenario by printing a crash message
* 		 and entering an infinite loop.
*
******************************************************************************/
void crash(){
    uart_writeStr(BSP_UART_TERMINAL, "\n*** CRASH ***\n");
    while(1);
}

/******************************************************************************
*
* @brief This function initialize external interrupts for UART.
*
******************************************************************************/
void uart_interrupt_init(void){

    //  uart_status_write(uart_status_read() | 0x01);   // TX FIFO empty interrupt enable
    uart_status_write(BSP_UART_TERMINAL, uart_status_read(BSP_UART_TERMINAL) | 0x02);   // RX FIFO not empty interrupt enable
    //configure PLIC
    plic_set_threshold(BSP_PLIC, BSP_PLIC_CPU_0, 0); //cpu 0 accept all interrupts with priority above 0

    //enable SYSTEM_PLIC_USER_INTERRUPT_A_INTERRUPT rising edge interrupt
    plic_set_enable(BSP_PLIC, BSP_PLIC_CPU_0, SYSTEM_PLIC_SYSTEM_UART_0_IO_INTERRUPT, 1);
    plic_set_priority(BSP_PLIC, SYSTEM_PLIC_SYSTEM_UART_0_IO_INTERRUPT, 1);

    csr_set(mie, MIE_MEIE); //Enable external interrupts
    csr_write(mstatus, csr_read(mstatus) | MSTATUS_MPP | MSTATUS_MIE);
}


/******************************************************************************
*
* @brief This function handles external interrupt event. 
*
******************************************************************************/
void UartInterrupt_Sub()
{
    if (uart_status_read(BSP_UART_TERMINAL) & 0x00000100){

        uart_writeStr(BSP_UART_TERMINAL, "TX FIFO empty interrupt\r\n");

        uart_status_write(BSP_UART_TERMINAL, uart_status_read(BSP_UART_TERMINAL) & 0xFFFFFFFE); // TX FIFO empty interrupt Disable
        uart_status_write(BSP_UART_TERMINAL, uart_status_read(BSP_UART_TERMINAL) | 0x01); // TX FIFO empty interrupt enable

        //******Interrupt Function by User******//
    }
    else if (uart_status_read(BSP_UART_TERMINAL) & 0x00000200){

        uart_writeStr(BSP_UART_TERMINAL, "RX FIFO not empty interrupt\r\n");

        uart_status_write(BSP_UART_TERMINAL, uart_status_read(BSP_UART_TERMINAL) & 0xFFFFFFFD);             // RX FIFO not empty interrupt Disable
        uart_write(BSP_UART_TERMINAL, uart_read(BSP_UART_TERMINAL));    //Dummy Read Clear FIFO
        uart_status_write(BSP_UART_TERMINAL, uart_status_read(BSP_UART_TERMINAL) | 0x02);                   // RX FIFO not empty interrupt enable

        //******Interrupt Function by User******//
    }
}

/******************************************************************************
*
* @brief This function handles UART interrupts by claiming pending interrupts 
* 		 and processing them through UartInterrupt_Sub().
*
******************************************************************************/
void UartInterrupt(){

    uint32_t claim;
    //While there is pending interrupts
    while(claim = plic_claim(BSP_PLIC, BSP_PLIC_CPU_0)){
        switch(claim){
        case SYSTEM_PLIC_SYSTEM_UART_0_IO_INTERRUPT: UartInterrupt_Sub(); break;
        default: crash(); break;
        }
        plic_release(BSP_PLIC, BSP_PLIC_CPU_0, claim); //unmask the claimed interrupt
    }
}

/******************************************************************************
*
* @brief This function handles interrupts by claiming pending interrupts 
* 		 and processing them through UartInterrupt().
*
******************************************************************************/
void freertos_risc_v_application_interrupt_handler(void){

    int32_t mcause = csr_read(mcause);
    int32_t interrupt = mcause < 0;    //Interrupt if set, exception if cleared
    int32_t cause     = mcause & 0xF;

    if(interrupt){
        switch(cause){
        case CAUSE_MACHINE_EXTERNAL: UartInterrupt(); break;
        default: crash(); break;
        }
    } else {
        crash();
    }

}
