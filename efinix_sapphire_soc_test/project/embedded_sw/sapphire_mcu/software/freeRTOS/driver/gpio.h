///////////////////////////////////////////////////////////////////////////////////
//  MIT License
//  
//  Copyright (c) 2023 SaxonSoc contributors
//  
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//  
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
///////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
*
* @file gpio.h
*
* @brief Header file for GPIO (General Purpose Input/Output) register access and control.
*
* Functions: 
* - gpio_getInput: reads a 32-bit value from the GPIO input register at address of 
*                  reg + offset (GPIO_INPUT).
* - gpio_getOutput: reads a 32-bit value from the GPIO output register at address of 
*                   reg + offset (GPIO_OUTPUT).
* - gpio_setOutput: Writes a 32-bit value to GPIO output register at address of 
*                   reg + offset (GPIO_OUTPUT).
* - gpio_getOutputEnable: Reads a 32-bit value from the GPIO output enable register 
*                         at address of reg + offset (GPIO_OUTPUT_ENABLE).
* - gpio_setOutputEnable: Writes a 32-bit value to the GPIO output enable register 
*                         at address of reg + offset (GPIO_OUTPUT_ENABLE).
* - gpio_setInterruptRiseEnable: Writes a 32-bit value to GPIO interrupt register 
*                                at address of reg + offset (GPIO_INTERRUPT_RISE_ENABLE).
* - gpio_setInterruptFallEnable: Writes a 32-bit value to GPIO interrupt register 
*                                at address of reg + offset (GPIO_INTERRUPT_FALL_ENABLE).
* - gpio_setInterruptHighEnable: Writes a 32-bit value to GPIO interrupt register 
*                                at address of reg + offset (GPIO_INTERRUPT_HIGH_ENABLE).
* - gpio_setInterruptLOWEnable: Writes a 32-bit value to GPIO interrupt register 
*                               at address of reg + offset (GPIO_INTERRUPT_LOW_ENABLE).
*
******************************************************************************/
#pragma once

#include "type.h"
#include "io.h"

//Offset
#define GPIO_INPUT                  0x00
#define GPIO_OUTPUT                 0x04
#define GPIO_OUTPUT_ENABLE          0x08
#define GPIO_INTERRUPT_RISE_ENABLE  0x20
#define GPIO_INTERRUPT_FALL_ENABLE  0x24
#define GPIO_INTERRUPT_HIGH_ENABLE  0x28
#define GPIO_INTERRUPT_LOW_ENABLE   0x2c

/*******************************************************************************
*
* @brief Reads a 32-bit value from the GPIO input register at address of
*        reg + offset (GPIO_INPUT).
*
* @return The value read from the GPIO input register.
*
* @note refer to readReg_u32 in io.h for detail explanation.
*
******************************************************************************/

    readReg_u32 (gpio_getInput               , GPIO_INPUT)

/*******************************************************************************
*
* @brief Reads a 32-bit value from the GPIO output register at address of
*        reg + offset (GPIO_OUTPUT).
*
* @return The value read from the GPIO output register.
*
* @note refer to readReg_u32 in io.h for detail explanation.
*
******************************************************************************/

    readReg_u32 (gpio_getOutput              , GPIO_OUTPUT)

/*******************************************************************************
*
* @brief Writes a 32-bit value to GPIO output register at address of 
*        reg + offset (GPIO_OUTPUT).
*
* @param data The data to be written to the GPIO output register.
*
* @note refer to writeReg_u32 in io.h for detail explanation.
*
******************************************************************************/

    writeReg_u32(gpio_setOutput              , GPIO_OUTPUT)

/*******************************************************************************
*
* @brief Reads a 32-bit value from the GPIO output enable register at address of
*        reg + offset (GPIO_OUTPUT_ENABLE).
*
* @return The value read from the GPIO output enable register.
*
* @note refer to readReg_u32 in io.h for detail explanation.
*
******************************************************************************/

    readReg_u32 (gpio_getOutputEnable        , GPIO_OUTPUT_ENABLE)

/*******************************************************************************
*
* @brief Writes a 32-bit value to GPIO output enable register at address of 
*        reg + offset (GPIO_OUTPUT_ENABLE).
*
* @param data The data to be written to the GPIO output enable register.
*
* @note refer to writeReg_u32 in io.h for detail explanation.
*
******************************************************************************/

    writeReg_u32(gpio_setOutputEnable        , GPIO_OUTPUT_ENABLE)

/*******************************************************************************
*
* @brief Writes a 32-bit value to GPIO interrupt register at address of 
*        reg + offset (GPIO_INTERRUPT_RISE_ENABLE).
*
* @param data The data to be written to the GPIO interrupt register.
*
* @note refer to writeReg_u32 in io.h for detail explanation.
*
******************************************************************************/

    writeReg_u32(gpio_setInterruptRiseEnable , GPIO_INTERRUPT_RISE_ENABLE)

/*******************************************************************************
*
* @brief Writes a 32-bit value to GPIO interrupt register at address of 
*        reg + offset (GPIO_INTERRUPT_FALL_ENABLE).
*
* @param data The data to be written to the GPIO interrupt register.
*
* @note refer to writeReg_u32 in io.h for detail explanation.
*
******************************************************************************/  

    writeReg_u32(gpio_setInterruptFallEnable , GPIO_INTERRUPT_FALL_ENABLE)
    
/*******************************************************************************
*
* @brief Writes a 32-bit value to GPIO interrupt register at address of 
*        reg + offset (GPIO_INTERRUPT_HIGH_ENABLE).
*
* @param data The data to be written to the GPIO interrupt register.
*
* @note refer to writeReg_u32 in io.h for detail explanation.
*
******************************************************************************/ 

    writeReg_u32(gpio_setInterruptHighEnable , GPIO_INTERRUPT_HIGH_ENABLE)

/*******************************************************************************
*
* @brief Writes a 32-bit value to GPIO interrupt register at address of 
*        reg + offset (GPIO_INTERRUPT_LOW_ENABLE).
*
* @param data The data to be written to the GPIO interrupt register.
*
* @note refer to writeReg_u32 in io.h for detail explanation.
*
******************************************************************************/
    writeReg_u32(gpio_setInterruptLowEnable  , GPIO_INTERRUPT_LOW_ENABLE)
