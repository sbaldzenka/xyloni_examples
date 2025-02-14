/*******************************************************************************
 *
 * @file start.h
 *
 * @brief Header file containing an external function declaration for SMP (Symmetric Multiprocessing) unlocking
 *
 * Functions:
 * - smp_unlock: External function declaration for unlocking SMP with a user-defined main function
 *
 ******************************************************************************/

#pragma once

extern void smp_unlock(void (*userMain)(u32, u32, u32) );