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
/**
* @file bsp.h
*
* @brief Header file for bsp printing related with different support such as floating point support, etc. 
*
* The available functions are:
* - _putchar: Outputs a single character.
* - _putchar_s: Outputs a null-terminated string
* -  bsp_print: Prints a null-terminated string followed by a newline character ('\n').
* -  bsp_printHex: Prints a 32-bit hexadecimal value.
* -  bsp_printHex_lower: Prints a 32-bit hexadecimal value in lower case.
* -  bsp_printHexByte: Prints a single byte in hexadecimal format. 
* -  bsp_printReg: Prints a register name followed by its hexadecimal value.
*
* @note bsp_printf can be accessed through either semihosting function or bsp function. 
*
******************************************************************************/
#pragma once

//#include <stdarg.h>
//#include <stdint.h>
#include "soc.h"
#include "uart.h"
#include "clint.h"
#include "io.h"
#include "type.h"
#include "semihosting.h"

#define BSP_PLIC SYSTEM_PLIC_CTRL
#define BSP_PLIC_CPU_0 SYSTEM_PLIC_SYSTEM_CORES_0_EXTERNAL_INTERRUPT
#define BSP_CLINT SYSTEM_CLINT_CTRL
#define BSP_CLINT_HZ SYSTEM_CLINT_HZ
#define BSP_UART_TERMINAL SYSTEM_UART_0_IO_CTRL

//backward compability 
#define BSP_MACHINE_TIMER SYSTEM_CLINT_CTRL
#define BSP_MACHINE_TIMER_HZ SYSTEM_CLINT_HZ 
#define machineTimer_setCmp(p, cmp) clint_setCmp(p, cmp, 0);
#define machineTimer_getTime(p) clint_getTime(p);
#define machineTimer_uDelay(usec, hz, reg) clint_uDelay(usec, hz, reg);

#define bsp_init() {}
#define bsp_uDelay(usec) clint_uDelay(usec, SYSTEM_CLINT_HZ, SYSTEM_CLINT_CTRL);

// Freertos specifics
#define configMTIME_BASE_ADDRESS        (BSP_CLINT + 0xBFF8)
#define configMTIMECMP_BASE_ADDRESS     (BSP_CLINT + 0x4000)
#define configCPU_CLOCK_HZ              ( ( uint32_t ) ( BSP_CLINT_HZ ) )
#define BSP_LED_GPIO                    SYSTEM_GPIO_0_IO_CTRL
#define BSP_LED_MASK                    0xf

/*******************************************************************************
* @brief Configuration options for printf functions.
*
* The available printf implementations are:
* 1. bsp_print, bsp_printHex, bsp_printHexDigit, bsp_printHexByte, bsp_printReg,
*    bsp_putString, and bsp_putChar: Not recommended for new designs.
* 2. bsp_printf: Supports char, string, decimal, and hexadecimal specifiers.
*    Provides print_float and print_dec functions. Uses medium RAM resources.
* 3. bsp_printf_full: Full support for printf, including flags and precisions.
*    Uses the most RAM resources.
*
* Configuration options:
* - ENABLE_BSP_PRINT: Enable backward-compatible printf.
* - ENABLE_BSP_PRINTF: Enable small unified printf.
* - ENABLE_BSP_PRINTF_FULL: Enable full unified printf.
* - ENABLE_SEMIHOSTING_PRINT: Enable semihosting printf.
* - ENABLE_FLOATING_POINT_SUPPORT: Enable support for floating point printing.
* - ENABLE_FP_EXPONENTIAL_SUPPORT: Enable support for exponential floating point printing.
* - ENABLE_PTRDIFF_SUPPORT: Enable support for pointer difference. 
* - ENABLE_LONG_LONG_SUPPORT: Enable support for long long data type.
* - ENABLE_BRIDGE_FULL_TO_LITE: Enable bridging bsp_printf_full to bsp_printf.
* - ENABLE_PRINTF_WARNING: Print warning when the specifier is not supported.
*
*******************************************************************************/
#define ENABLE_BSP_PRINT                    1 // backward compatible printf //Default: Enable
#define ENABLE_BSP_PRINTF                   1 // small unified printf       //Default: Enable
#define ENABLE_BSP_PRINTF_FULL              0 // full unified printf        //Default: Disable
#define ENABLE_SEMIHOSTING_PRINT            1 // Enable semihosting         //Default: Disable

//Printf Supports Enable
#define ENABLE_FLOATING_POINT_SUPPORT       SYSTEM_CORES_0_FPU  // Enable the supports for floating point printing. Only applicable for BSP_PRINTF and BSP_PRINTF_FULL    // Default: Disable
#define ENABLE_FP_EXPONENTIAL_SUPPORT       0 // Supports Floating point print with exponential. Only applicable for BSP_PRINTF_FULL                    // Default: Disable
#define ENABLE_PTRDIFF_SUPPORT              0 // Supports pointer difference                                                                            // Default: Disable
#define ENABLE_LONG_LONG_SUPPORT            0 // Supports long long data type                                                                           // Default: Disable

// use bsp_printf_full as bsp_printf
#define ENABLE_BRIDGE_FULL_TO_LITE          1 // If this is enabled, bsp_printf_full can be called with bsp_printf. Enabling both ENABLE_BSP_PRINTF and ENABLE_BSP_PRINTF_FULL, bsp_printf_full will be remained as bsp_printf_full. Default: Enable
#define ENABLE_PRINTF_WARNING               1 // Print warning when the specifier not supported. Default: Enable

//backward compability
#if(ENABLE_SEMIHOSTING_PRINT)
#define bsp_putChar(c) bsp_printf_c(c);
#define bsp_putString(s) bsp_printf_s(s);
#else
#define bsp_putChar(c) uart_write(BSP_UART_TERMINAL, c);
#define bsp_putString(s) uart_writeStr(BSP_UART_TERMINAL, s);
#endif

/*******************************************************************************
* @brief This function is used to output a single character.
*
* This function outputs a single character either using semihosting (if enabled)
* or using the board support package (BSP) function bsp_putChar().
*
* @param character: The character to be output.
*
* @note If semihosting printing is enabled (ENABLE_SEMIHOSTING_PRINT == 1),
*       the character is output using the semihosting function sh_writec().
*       Otherwise, the character is output using the BSP function bsp_putChar().
*
*******************************************************************************/
    static void _putchar(char character){
        #if (ENABLE_SEMIHOSTING_PRINT == 1)
            sh_writec(character);
        #else
            bsp_putChar(character);
        #endif // (ENABLE_SEMIHOSTING_PRINT == 1)
    }

/*******************************************************************************
* @brief This function is used to outputs a null-terminated string. 
*
* @param p: A pointer to the null-terminated string to be output.
*
* @note If semihosting printing is enabled (ENABLE_SEMIHOSTING_PRINT == 1),
*       the character is output using the semihosting function sh_write0().
*       Otherwise, the character is output using the BSP function _putChar().
*
*******************************************************************************/
    static void _putchar_s(char *p)
    {
    #if (ENABLE_SEMIHOSTING_PRINT == 1)
        sh_write0(p);
    #else
        while (*p)
            _putchar(*(p++));
    #endif // (ENABLE_SEMIHOSTING_PRINT == 1)
    }

/*******************************************************************************
* @brief This function is used to prints a 32-bit hexadecimal value to the console.
*
* @param val: The 32-bit hexadecimal value to be printed.
*
* @note The function iterates over each nibble (4 bits) of the value and prints the corresponding hexadecimal character.
*
*******************************************************************************/
    //bsp_printHex is used in BSP_PRINTF
    static void bsp_printHex(uint32_t val)
    {
        uint32_t digits;
        digits =8;

        for (int i = (4*digits)-4; i >= 0; i -= 4) {
            _putchar("0123456789ABCDEF"[(val >> i) % 16]);
        }
    }

/*******************************************************************************
* @brief This function is used to prints a 32-bit hexadecimal value in lowercase to the console.
*
* @param val: The 32-bit hexadecimal value to be printed.
*
* @note The function iterates over each nibble (4 bits) of the value and prints the corresponding hexadecimal character.
*
*******************************************************************************/
    static void bsp_printHex_lower(uint32_t val)
        {
            uint32_t digits;
            digits =8;

            for (int i = (4*digits)-4; i >= 0; i -= 4) {
                _putchar("0123456789abcdef"[(val >> i) % 16]);

            }
        }

/*******************************************************************************
*
* @brief This function prints a null-terminated string followed by a newline character ('\n') 
*        and a carriage return character ('\r') to the console if ENABLE_BSP_PRINT is set to 1. 
*
* @param data: Pointer to the null-terminated string to be printed.
*
* @note The function iterates over each nibble (4 bits) of the value and prints the corresponding hexadecimal character.
*
*******************************************************************************/
#if (ENABLE_BSP_PRINT)
    static void bsp_print(uint8_t * data) {
        _putchar_s((char*)data);
        _putchar('\n');
        _putchar('\r');
    }
/*******************************************************************************
* @brief This function prints a single hexadecimal digit to the console if ENABLE_BSP_PRINT is set to 1. 
*
* @param digit: The hexadecimal digit to be printed.
*
* @note If the digit is less than 10, it is printed as a character ('0' to '9').
*  Otherwise, it is printed as a character ('A' to 'F') corresponding to the hexadecimal value.
*
*******************************************************************************/
    static void bsp_printHexDigit(uint8_t digit){
        _putchar(digit < 10 ? '0' + digit : 'A' + digit - 10);
    }
/*******************************************************************************
* @brief This function prints a single byte in hexadecimal format to the console.
*
* @param byte: The byte to be printed.
*
* @note The byte is split into two hexadecimal digits, and each digit is printed separately.
*
*******************************************************************************/
    static void bsp_printHexByte(uint8_t byte){
        bsp_printHexDigit(byte >> 4);
        bsp_printHexDigit(byte & 0x0F);
    }

/*******************************************************************************
* @brief This function prints a register name followed by its hexadecimal value to the console.
*
* @param s: The string containing the register name.
* @param  data: The value of the register to be printed.
*
* @note This function first prints the register name using bsp_print, then prints the hexadecimal
*   value of the register using bsp_printHex.
*
*******************************************************************************/
    static void bsp_printReg(char* s, u32 data)
    {
        _putchar_s(s);
        bsp_printHex(data);
    }

#endif

#if (ENABLE_BSP_PRINTF)
    #include "print.h"
#endif //#if (ENABLE_BSP_PRINTF)

#if (ENABLE_BSP_PRINTF_FULL)
#if (!ENABLE_FLOATING_POINT_SUPPORT)
    #define PRINTF_DISABLE_SUPPORT_FLOAT 1
#endif //#if (ENABLE_FLOATING_POINT_SUPPORT)
#if (!ENABLE_FP_EXPONENTIAL_SUPPORT)
    #define PRINTF_DISABLE_SUPPORT_EXPONENTIAL 1
#endif //#if (ENABLE_FLOATING_POINT_SUPPORT)
#if (!ENABLE_PTRDIFF_SUPPORT)
    #define PRINTF_DISABLE_SUPPORT_PTRDIFF_T 1
#endif //#if (ENABLE_PTRDIFF_SUPPORT)
#if (!ENABLE_LONG_LONG_SUPPORT)
    #define PRINTF_DISABLE_SUPPORT_LONG_LONG 1
#endif //#if (ENABLE_LONG_LONG_SUPPORT)
#if(ENABLE_BRIDGE_FULL_TO_LITE)
#if (!ENABLE_BSP_PRINTF)
    #define bsp_printf bsp_printf_full
#endif // #if (!ENABLE_BSP_PRINTF)
#endif //#if(ENABLE_BRIDGE_EFX_TO_BSP)
#include "print_full.h"
#endif //#if (ENABLE_BSP_PRINTF_FULL)


