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

/*****************************************************************************
*
* @file io.h 
*
* @brief Header file contains basic read and write function with different data types.
*
* Functions:
* - read_u32: Reads a 32-bit unsigned integer value from a memory address.
* - read_u16: Reads a 16-bit unsigned integer value from a memory address.
* - read_u8 : Reads a 8-bit unsigned integer value from a memory address.
* - write_u32: Writes a 32-bit unsigned integer value to a memory address.
* - write_u16: Writes a 16-bit unsigned integer value to a memory address.
* - write_u8 : Writes a 8-bit unsigned integer value to a memory address.
* - writeReg_u32: Defines a function for writing a 32-bit unsigned integer value
*                 to a register at a specific offset from a base address.
* - readReg_u32: Defines a function for reading a 32-bit unsigned integer value
*                from a register at a specific offset from a base address.
*
******************************************************************************/

#pragma once
#include "type.h"
#include "soc.h"

/*******************************************************************************
*
* @brief   This function reads a 32-bit unsigned integer value from a memory address.
*
* @param   address is the memory address from which to read the value.
*
* @return  The 32-bit unsigned integer value read from the specified address.
*
* @note    The memory location pointed to by the address may change unexpectedly,
*          so the 'volatile' keyword is used to prevent the compiler from
*          optimizing away or reordering the read operation.
*
******************************************************************************/
    static inline u32 read_u32(u32 address){
        return *((volatile u32*) address);
    }
    
/*******************************************************************************
*
* @brief   This function writes a 32-bit unsigned integer value to a memory address.
*
* @param   data is the 32-bit unsigned integer value to be written.
* @param   address is the memory address where the value will be written.
*
* @return  None.
*
* @note    The memory location pointed to by the address may change unexpectedly,
*          so the 'volatile' keyword is used to prevent the compiler from
*          optimizing away or reordering the write operation.
*
******************************************************************************/

    static inline void write_u32(u32 data, u32 address){
        *((volatile u32*) address) = data;
    }

    
/*******************************************************************************
*
* @brief   This function reads a 16-bit unsigned integer value from a memory address.
*
* @param   address is the memory address from which to read the value.
*
* @return  The 16-bit unsigned integer value read from the specified address.
*
* @note    The memory location pointed to by the address may change unexpectedly,
*          so the 'volatile' keyword is used to prevent the compiler from
*          optimizing away or reordering the read operation.
*
******************************************************************************/
    static inline u16 read_u16(u32 address){
        return *((volatile u16*) address);
    }

/*******************************************************************************
*
* @brief   This function writes a 16-bit unsigned integer value to a memory address.
*
* @param   data is the 16-bit unsigned integer value to be written.
* @param   address is the memory address where the value will be written.
*
* @return  None.
*
* @note    The memory location pointed to by the address may change unexpectedly,
*          so the 'volatile' keyword is used to prevent the compiler from
*          optimizing away or reordering the write operation.
*
******************************************************************************/
    static inline void write_u16(u16 data, u32 address){
        *((volatile u16*) address) = data;
    }

/*******************************************************************************
*
* @brief   This function reads a 8-bit unsigned integer value from a memory address.
*
* @param   address is the memory address from which to read the value.
*
* @return  The 8-bit unsigned integer value read from the specified address.
*
* @note    The memory location pointed to by the address may change unexpectedly,
*          so the 'volatile' keyword is used to prevent the compiler from
*          optimizing away or reordering the read operation.
*
******************************************************************************/
    static inline u8 read_u8(u32 address){
        return *((volatile u8*) address);
    }
    
/*******************************************************************************
* 
* @brief   This function writes a 8-bit unsigned integer value to a memory address.
*
* @param   data is the 8-bit unsigned integer value to be written.
* @param   address is the memory address where the value will be written.
*
* @return  None.
*
* @note    The memory location pointed to by the address may change unexpectedly,
*          so the 'volatile' keyword is used to prevent the compiler from
*          optimizing away or reordering the write operation.
*
******************************************************************************/
    static inline void write_u8(u8 data, u32 address){
        *((volatile u8*) address) = data;
    }
    
/*******************************************************************************
*
* @brief   This function writes a 32-bit unsigned integer value to a memory address.
*
* @param   address is the memory address where the value will be written.
* @param   data is the 32-bit unsigned integer value to be written.
*
* @return  None.
*
* @note    The memory location pointed to by the address may change unexpectedly,
*          so the 'volatile' keyword is used to prevent the compiler from
*          optimizing away or reordering the write operation.
*
******************************************************************************/
    static inline void write_u32_ad(u32 address, u32 data){ // is this same as write_u32?
        *((volatile u32*) address) = data;
    }
    
/*******************************************************************************
*
* @brief  This macro defines a function for writing a 32-bit unsigned integer value
*         to a register at a specific offset from a base address.
*
* @param   name is the name of the function to be defined.
* @param   offset is the offset value added to the base address.
*
* @return  None.
*
* @note    The macro expands into a static inline function that takes two
*          arguments: 'reg' (the base address of the register) and 'value'
*          (the 32-bit unsigned integer value to be written to the register).
*          The function internally calls the 'write_u32' function to perform
*          the write operation to the register at the address 'reg + offset'.
*
******************************************************************************/
    #define writeReg_u32(name, offset) \
    static inline void name(u32 reg, u32 value){ \
        write_u32(value, reg + offset); \
    } \
  
  
/*******************************************************************************
*
* @brief   This macro defines a function for reading a 32-bit unsigned integer value
*          from a register at a specific offset from a base address.
*
* @param   name is the name of the function to be defined.
* @param   offset is the offset value added to the base address.
*
* @return  The 32-bit unsigned integer value read from the register.
*
* @note    The macro expands into a static inline function that takes one
*          argument: 'reg' (the base address of the register). The function
*          internally calls the 'read_u32' function to read the value from
*          the register at the address 'reg + offset' and returns it.
*
******************************************************************************/
    #define readReg_u32(name, offset) \
    static inline u32 name(u32 reg){ \
        return read_u32(reg + offset); \
    } 
