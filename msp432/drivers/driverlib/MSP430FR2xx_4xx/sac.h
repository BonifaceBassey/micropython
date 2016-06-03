/* --COPYRIGHT--,BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
//*****************************************************************************
//
// sac.h - Driver for the SAC Module.
//
//*****************************************************************************

#ifndef __MSP430WARE_SAC_H__
#define __MSP430WARE_SAC_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_SACx_CONFIG_1__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// The following are values that can be passed to the positiveInput parameter
// for functions: SAC_OA_init().
//
//*****************************************************************************
#define SAC_OA_POSITIVE_INPUT_SOURCE_EXTERNAL                               0x0
#define SAC_OA_POSITIVE_INPUT_SOURCE_DAC                                  PSEL0
#define SAC_OA_POSITIVE_INPUT_SOURCE_PAIR_OA                              PSEL1
#define SAC_OA_POSITIVE_INPUT_SOURCE_DISCONNECTED                           0xF

//*****************************************************************************
//
// The following are values that can be passed to the negativeInput parameter
// for functions: SAC_OA_init().
//
//*****************************************************************************
#define SAC_OA_NEGATIVE_INPUT_SOURCE_EXTERNAL                               0x0
#define SAC_OA_NEGATIVE_INPUT_SOURCE_PGA                                  NSEL0
#define SAC_OA_NEGATIVE_INPUT_SOURCE_DISCONNECTED                           0xF

//*****************************************************************************
//
// The following are values that can be passed to the powerMode parameter for
// functions: SAC_OA_selectPowerMode().
//
//*****************************************************************************
#define SAC_OA_POWER_MODE_HIGH_SPEED_HIGH_POWER                             0x0
#define SAC_OA_POWER_MODE_LOW_SPEED_LOW_POWER                              OAPM

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Initializes SAC OA with positive input and negative input
//!
//! This function initializes SAC OA with positive input and negative input.
//!
//! \param baseAddress is the base address of the SAC module.
//! \param positiveInput selects the positive input source
//!        Valid values are:
//!        - \b SAC_OA_POSITIVE_INPUT_SOURCE_EXTERNAL [Default]
//!        - \b SAC_OA_POSITIVE_INPUT_SOURCE_DAC
//!        - \b SAC_OA_POSITIVE_INPUT_SOURCE_PAIR_OA
//!        - \b SAC_OA_POSITIVE_INPUT_SOURCE_DISCONNECTED
//!        \n Modified bits are \b PSEL and \b PMUXEN of \b SACxOA register.
//! \param negativeInput selects the positive input source
//!        Valid values are:
//!        - \b SAC_OA_NEGATIVE_INPUT_SOURCE_EXTERNAL [Default]
//!        - \b SAC_OA_NEGATIVE_INPUT_SOURCE_PGA
//!        - \b SAC_OA_NEGATIVE_INPUT_SOURCE_DISCONNECTED
//!        \n Modified bits are \b NSEL and \b NMUXEN of \b SACxOA register.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_OA_init(uint16_t baseAddress,
                        uint16_t positiveInput,
                        uint16_t negativeInput);

//*****************************************************************************
//
//! \brief Selects power mode for OA
//!
//! This function selects power mode for OA.
//!
//! \param baseAddress is the base address of the SAC module.
//! \param powerMode selects TRI power mode.
//!        Valid values are:
//!        - \b SAC_OA_POWER_MODE_HIGH_SPEED_HIGH_POWER [Default]
//!        - \b SAC_OA_POWER_MODE_LOW_SPEED_LOW_POWER
//!        \n Modified bits are \b OAPM of \b SACxOA register.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_OA_selectPowerMode(uint16_t baseAddress,
                                   uint16_t powerMode);

//*****************************************************************************
//
//! \brief Enables OA
//!
//! This will enables OA for normal mode.
//!
//! \param baseAddress is the base address of the SAC module.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_OA_enable(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Disables OA
//!
//! This will disable OA and OA outputs high impedance.
//!
//! \param baseAddress is the base address of the SAC module.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_OA_disable(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Enables the SAC all modules
//!
//! This will enable SAC all modules.
//!
//! \param baseAddress is the base address of the SAC module.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_enable(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Disables the SAC all modules
//!
//! This will disable SAC all modules.
//!
//! \param baseAddress is the base address of the SAC module.
//!
//! \return None
//
//*****************************************************************************
extern void SAC_disable(uint16_t baseAddress);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
#endif // __MSP430WARE_SAC_H__
