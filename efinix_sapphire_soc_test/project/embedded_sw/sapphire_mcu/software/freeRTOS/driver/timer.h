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
* @file timer.h
*
* @brief Header file for timer functionality, including register access and control.
*        reading and writing timer registers, configuring timer settings,
*        and accessing timer values and limits.
*
******************************************************************************/
#pragma once

#include "type.h"
#include "io.h"

#define TIMER_CONFIG    0x00
#define TIMER_LIMIT     0x04
#define TIMER_VALUE     0x08

/*******************************************************************************
*
* @brief This function reads a 32-bit value from the timer configuration register.
*
* @return The value read from the timer configuration register.
*
******************************************************************************/
    readReg_u32 (timer_getConfig       , TIMER_CONFIG)
/*******************************************************************************
*
* @brief This function writes a 32-bit value to the timer configuration register.
*
* @param data The data to be written to the timer configuration register.
*
******************************************************************************/
    writeReg_u32(timer_setConfig       , TIMER_CONFIG)
/*******************************************************************************
*
* @brief This function reads a 32-bit value from the timer limit register.
*
* @return The value read from the timer limit register.
*
******************************************************************************/
    readReg_u32 (timer_getLimit        , TIMER_LIMIT)
/*******************************************************************************
*
* @brief This funciton writes a 32-bit value to the timer limit register.
*
* @param data The data to be written to the timer limit register.
*
******************************************************************************/
    writeReg_u32(timer_setLimit        , TIMER_LIMIT)

/*******************************************************************************
*
* @brief This function reads a 32-bit value from the timer value register.
*
* @return The value read from the timer value register.
*
******************************************************************************/
    readReg_u32 (timer_getValue        , TIMER_VALUE)
/*******************************************************************************
*
* @brief This function clears the value of the timer register.
*
* @param reg The base address of the timer register.
*
******************************************************************************/  
    void timer_clearValue(u32 reg){
        write_u32(0, reg + TIMER_VALUE);
    }
