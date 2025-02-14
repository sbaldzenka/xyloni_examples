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
* @file main.c: freertosDemo2
*
* @brief  This demo shows how FreeRTOS schedular handles two program executions using a
*         binary semaphore. The semaphore holds the hardware resource until one of the 
*         tasks execute, which then releases it to the next task. If the hardware resource 
*         is running a task, no other task can use that resource. In this example, two tasks 
*         use the same UART peripheral to print messages. By using a semaphore, the two tasks
*         have alternate access to the UART peripheral.
*
******************************************************************************/

/* FreeRTOS kernel includes. */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include "bsp.h"
#include "riscv.h"
#include "hal.h"
#include "gpio.h"

SemaphoreHandle_t xBinarySemaphore;

void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vApplicationTickHook( void );

/* Prepare hardware to run the demo. */
static void prvSetupHardware( void );

/* Tasks to demo semaphore */
static void UartTask1 ( void *pvParameters );
static void UartTask2 ( void *pvParameters );

/* Send a message to the UART initialised in prvSetupHardware. */
void vSendString( const char * const pcString );

/*******************************************************************************
*
* @brief   This main function serves as the main entry point for the application
*          where it initializes hardware, creates tasks, and starts the FreeRTOS
*          scheduler. It also creates a binary semaphore and gives it to allow one
*          of the tasks to proceed.
*
******************************************************************************/
int main( void )
{
    prvSetupHardware();
    xBinarySemaphore = xSemaphoreCreateBinary();
    xTaskCreate(UartTask1, "UART1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(UartTask2, "UART2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xSemaphoreGive(xBinarySemaphore);
    
    vTaskStartScheduler();

    for( ;; );
}

/*******************************************************************************
*
* @brief This function initialize the hardware setup to run the demo. 
*
******************************************************************************/
static void prvSetupHardware( void )
{
    extern void freertos_risc_v_trap_handler();
    csr_write(mtvec, freertos_risc_v_trap_handler);

    vSendString( "Hello world, this is FreeRTOS\r\n" );
}

/*******************************************************************************
*
* @brief This function execute program using binary semaphore.
*
******************************************************************************/
static void UartTask1(void *pvParameters)
{
    /*Uncomment semaphore functions below to check on output
     without interfere from sempahore*/
    while(1)
    {
        xSemaphoreTake(xBinarySemaphore,portMAX_DELAY);
        vSendString( "Inside uart task 1 loop\r\n");
        xSemaphoreGive(xBinarySemaphore);
        vTaskDelay(1);
    }
}

/*******************************************************************************
*
* @brief This function execute program using binary semaphore.
*
******************************************************************************/
static void UartTask2(void *pvParameters)
{
    /*Uncomment semaphore functions below to check on output
     without interfere from sempahore*/
    while(1)
    {
        xSemaphoreTake(xBinarySemaphore,portMAX_DELAY);
        vSendString( "Inside uart task 2 loop\r\n");
        xSemaphoreGive(xBinarySemaphore);
        vTaskDelay(1);
    }
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
* This function handles stack overflow conditions in FreeRTOS.
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

