/*******************************************************************************
*
* @file i2cMcp4725.h
*
* @brief Header file for defining necessary parameter for accessing MCP4725 DAC module.
*
******************************************************************************/

#pragma once

#define SYSTEM_I2C_0_IO_CTRL
#define PLIC_I2C_INTERRUPT SYSTEM_PLIC_SYSTEM_I2C_0_IO_INTERRUPT
#define CORE_HZ SYSTEM_CLINT_HZ
