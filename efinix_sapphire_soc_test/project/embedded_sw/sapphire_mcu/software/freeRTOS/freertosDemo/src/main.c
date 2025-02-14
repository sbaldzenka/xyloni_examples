/*
* FreeRTOS Kernel V10.2.1
* Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the "Software"), to deal in
* the Software without restriction, including without limitation the rights to
* use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
* the Software, and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
* IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* http://www.FreeRTOS.org
* http://aws.amazon.com/freertos
*
* 1 tab == 4 spaces!
*/

/******************************************************************************
*
* @file main.c: freertosDemo
*
* @brief  This demo shows how the FreeRTOS schedular handles two program executions using
*         task and queue allocation. Generally, the FreeRTOS queue is used as a thread FIFO 
*         buffer and for intertask communication. This example creates two tasks and one queue; 
*         the queue sends and receives traffic. The receive traffic (or receive queue) blocks 
*         the program execution until it receives a matching value from the send traffic 
*         (or send queue). Tasks in the send queue sit in a loop that blocks execution for 1,000ms 
*         before sending the value 100 to the receive queue. Once the value is sent, the task 
*         loops, i.e., blocks for another 1,000ms. When the receive queue receives the value 100,
*         it begins executing its task, which sends the message "Blink" to the UART peripheral 
*         and toggles an LED on the development board.
*
******************************************************************************/

/* FreeRTOS kernel includes. */
#include <FreeRTOS.h>
#include <task.h>

#include "bsp.h"
#include "riscv.h"
#include "hal.h"
#include "gpio.h"


extern void main_blinky( void );
/* Prototypes for the standard FreeRTOS callback/hook functions implemented
within this file.  See https://www.freertos.org/a00016.html */

void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vApplicationTickHook( void );

/* Prepare hardware to run the demo. */
static void prvSetupHardware( void );

/* Send a message to the UART initialised in prvSetupHardware. */
void vSendString( const char * const pcString );

/*******************************************************************************
*
* @brief This function initialize the system and handles two program exceutions
*        using task and queue allocation. 
*
******************************************************************************/
int main( void )
{
    prvSetupHardware();
    main_blinky();
}

/*******************************************************************************
*
* @brief This function initialize the hardware setup and GPIO (LED) to run the demo. 
*
******************************************************************************/
static void prvSetupHardware( void )
{
    extern void freertos_risc_v_trap_handler();
    csr_write(mtvec, freertos_risc_v_trap_handler);

    gpio_setOutputEnable(BSP_LED_GPIO, BSP_LED_MASK);
    gpio_setOutput(BSP_LED_GPIO, 0x00000000);

    vSendString( "Hello world, this is FreeRTOS\r\n" );
}

/*******************************************************************************
*
* @brief This function toggle LED. 
*
******************************************************************************/
void vToggleLED( void )
{
static uint32_t ulLEDState = 0;
    gpio_setOutput(BSP_LED_GPIO, gpio_getOutput(BSP_LED_GPIO) ^ BSP_LED_MASK);
}

/*******************************************************************************
*
* @brief This function send a message to the UART initialised in prvSetupHardware
*
******************************************************************************/
void vSendString( const char * const pcString )
{
    bsp_printf(pcString); 
}

/*******************************************************************************
*
* @brief   This function handles memory allocation failures in FreeRTOS.
*
* @param   None.
*
* @return  None.
*
* @note    This function is called when a memory allocation failure occurs in FreeRTOS.
*          It disables interrupts, triggers a breakpoint, and enters an infinite loop.
*          This provides a way to halt the system in a controlled manner when
*          memory allocation fails.
*
******************************************************************************/
void vApplicationMallocFailedHook( void )
{
    /* vApplicationMallocFailedHook() will only be called if
    configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
    function that will get called if a call to pvPortMalloc() fails.
    pvPortMalloc() is called internally by the kernel whenever a task, queue,
    timer or semaphore is created.  It is also called by various parts of the
    demo application.  If heap_1.c or heap_2.c are used, then the size of the
    heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
    FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
    to query the size of free heap space that remains (although it does not
    provide information on how the remaining heap might be fragmented). */
    taskDISABLE_INTERRUPTS();
    __asm volatile( "ebreak" );
    for( ;; );
}

/*******************************************************************************
*
* @brief   This function serves as the idle hook for FreeRTOS.
*
* @param   None.
*
* @return  None.
*
* @note    This function is called on each iteration of the idle task when
*          configUSE_IDLE_HOOK is set to 1 in FreeRTOSConfig.h. It should be
*          ensured that no blocking operations are performed within this hook.
*          Additionally, this function should return to its caller if the
*          application uses the vTaskDelete() API, as the responsibility to
*          clean up memory allocated by the kernel to deleted tasks lies with
*          the idle task.
*
******************************************************************************/
void vApplicationIdleHook( void )
{
    /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
    to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
    task.  It is essential that code added to this hook function never attempts
    to block in any way (for example, call xQueueReceive() with a block time
    specified, or call vTaskDelay()).  If the application makes use of the
    vTaskDelete() API function (as this demo application does) then it is also
    important that vApplicationIdleHook() is permitted to return to its calling
    function, because it is the responsibility of the idle task to clean up
    memory allocated by the kernel to any task that has since been deleted. */
}


/*******************************************************************************
*
* @brief   This function handles stack overflow conditions in FreeRTOS.
*
* @param   pxTask: Handle to the task which caused the stack overflow (unused).
* @param   pcTaskName: Name of the task which caused the stack overflow (unused).
*
* @return  None.
*
* @note    This function is called when a stack overflow is detected in FreeRTOS.
*          It disables interrupts, triggers a breakpoint, and enters an infinite loop.
*          This provides a way to halt the system in a controlled manner when
*          stack overflow occurs.
*
******************************************************************************/
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */
    taskDISABLE_INTERRUPTS();
    __asm volatile( "ebreak" );
    for( ;; );
}

/*******************************************************************************
*
* @brief   This function serves as the tick hook for FreeRTOS.
*
* @param   None.
*
* @return  None.
*
* @note    This function is called on each tick interrupt generated by the
*          system timer. Its main purpose is to handle system-wide tick
*          operations or call other tick-related functions.
*
******************************************************************************/
void vApplicationTickHook( void )
{
    extern void vFullDemoTickHook( void );
}


