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
//! \brief  Driver for the LEA_SC module.
//! \file   lea.h
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup lea_api
//! @{
//
//*****************************************************************************

#ifndef __MSP430WARE_LEA_H__
#define __MSP430WARE_LEA_H__

#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_LEA_SC__

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
//! \brief Convert MSP430 address to internal LEA address mapping.
//
//*****************************************************************************
#define LEA_CONVERT_ADDRESS(x)  ((uint16_t)(((uint32_t)(x) >> 2) & 0xffff))

//*****************************************************************************
//
//! \brief Interrupt enable bits used to provide a mask when enabling or
//! disabling LEA interrupts.
//!
//! These values can be passed to the mask parameter of the functions
//! LEA_enableInterrupt() and LEA_disableInterrupt().
//
//*****************************************************************************
#define LEA_COMMAND_COMPLETE_INTERRUPT                  LEASCPMCMDIE
#define LEA_SCALAR_DATA_INCONSISTENCY_INTERRUPT         LEASCSDIIE
#define LEA_ADDRESS_OUT_OF_RANGE_INTERRUPT              LEASCOORIE
#define LEA_COMMAND_OVERFLOW_INTERRUPT                  LEASCCOVLIE
#define LEA_ALL_INTERRUPTS                              (LEASCPMCMDIE | \
                                                         LEASCSDIIE | \
                                                         LEASCOORIE | \
                                                         LEASCCOVLIE)

//*****************************************************************************
//
//! \brief Interrupt flags used to provide a mask when enabling or disabling
//! LEA interrupts.
//!
//! These values can be passed to the mask parameter of the functions
//! LEA_getInterruptStatus(), LEA_setInterruptFlags() LEA_clearInterrupt().
//
//*****************************************************************************
#define LEA_COMMAND_COMPLETE_INTERRUPT_FLAG             LEASCPMCMDIFG
#define LEA_SCALAR_DATA_INCONSISTENCY_INTERRUPT_FLAG    LEASCSDIIFG
#define LEA_ADDRESS_OUT_OF_RANGE_INTERRUPT_FLAG         LEASCOORIFG
#define LEA_COMMAND_OVERFLOW_INTERRUPT_FLAG             LEASCCOVLIFG
#define LEA_ALL_INTERRUPT_FLAGS                         (LEASCPMCMDIFG | \
                                                         LEASCSDIIFG | \
                                                         LEASCOORIFG | \
                                                         LEASCCOVLIFG)

//*****************************************************************************
//
//! \brief Interrupt flags used to provide a mask when enabling or disabling
//! LEA interrupts.
//!
//! These values can be passed to the mode parameter of the functions
//! LEA_suspendCommand(), LEA_resumeCommand() and LEA_invokeCommand().
//
//*****************************************************************************
#define LEA_INVOKE_WITHOUT_INTERRUPTS                   LEASCITFLG0
#define LEA_INVOKE_WITH_INTERRUPTS                      LEASCITFLG1

//*****************************************************************************
//
//! \brief The following values can be passed in the command argument of the
//! LEA_invokeCommand() function to invoke a specific LEA command.
//
//*****************************************************************************
typedef enum LEA_command
{
    LEA_mac = LEASCCMD__MAC,
    LEA_max = LEASCCMD__MAX,
    LEA_min = LEASCCMD__MIN,
    LEA_maxUnsigned = LEASCCMD__MAXUNSIGNED,
    LEA_minUnsigned = LEASCCMD__MINUNSIGNED,
    LEA_addMatrix = LEASCCMD__ADDMATRIX,
    LEA_subMatrix = LEASCCMD__SUBMATRIX,
    LEA_mpyMatrix = LEASCCMD__MPYMATRIX,
    LEA_macMatrix = LEASCCMD__MACMATRIX,
    LEA_maxMatrix = LEASCCMD__MAXMATRIX,
    LEA_minMatrix = LEASCCMD__MINMATRIX,
    LEA_mpyMatrixRow = LEASCCMD__MPYMATRIXROW,
    LEA_mpyComplexMatrix = LEASCCMD__MPYCOMPLEXMATRIX,
    LEA_macComplexMatrix = LEASCCMD__MACCOMPLEXMATRIX,
    LEA_macComplexConjugateMatrix = LEASCCMD__MACCOMPLEXCONJUGATEMATRIX,
    LEA_maxUnsignedMatrix = LEASCCMD__MAXUNSIGNEDMATRIX,
    LEA_minUnsignedMatrix = LEASCCMD__MINUNSIGNEDMATRIX,
    LEA_addLongMatrix = LEASCCMD__ADDLONGMATRIX,
    LEA_subLongMatrix = LEASCCMD__SUBLONGMATRIX,
    LEA_mpyLongMatrix = LEASCCMD__MPYLONGMATRIX,
    LEA_macLongMatrix = LEASCCMD__MACLONGMATRIX,
    LEA_maxLongMatrix = LEASCCMD__MAXLONGMATRIX,
    LEA_minLongMatrix = LEASCCMD__MINLONGMATRIX,
    LEA_maxUnsignedLongMatrix = LEASCCMD__MAXUNSIGNEDLONGMATRIX,
    LEA_minUnsignedLongMatrix = LEASCCMD__MINUNSIGNEDLONGMATRIX,
    LEA_polynomial = LEASCCMD__POLYNOMIAL,
    LEA_polynomialLong = LEASCCMD__POLYNOMIALLONG,
    LEA_polynomialScalar = LEASCCMD__POLYNOMIALSCALAR,
    LEA_fir = LEASCCMD__FIR,
    LEA_firComplex = LEASCCMD__FIRCOMPLEX,
    LEA_firLong = LEASCCMD__FIRLONG,
    LEA_firComplexLong = LEASCCMD__FIRCOMPLEXLONG,
    LEA_iir = LEASCCMD__IIR,
    LEA_biquadWithBiasAndMinMax = LEASCCMD__BIQUADWITHBIASANDMINMAX,
    LEA_goertzel = LEASCCMD__GOERTZEL,
    LEA_fft = LEASCCMD__FFT,
    LEA_fftComplexAutoScaling = LEASCCMD__FFTCOMPLEXAUTOSCALING,
    LEA_fftComplexFixedScaling = LEASCCMD__FFTCOMPLEXFIXEDSCALING,
    LEA_fftLong = LEASCCMD__FFTLONG,
    LEA_fftComplexLong = LEASCCMD__FFTCOMPLEXLONG,
    LEA_bitReverseComplexEven = LEASCCMD__BITREVERSECOMPLEXEVEN,
    LEA_bitReverseComplexOdd = LEASCCMD__BITREVERSECOMPLEXODD,
    LEA_bitReverseComplexLongEven = LEASCCMD__BITREVERSECOMPLEXLONGEVEN,
    LEA_bitReverseComplexLongOdd = LEASCCMD__BITREVERSECOMPLEXLONGODD,
    LEA_moveLongList = LEASCCMD__MOVELONGLIST,
    LEA_deinterleaveEvenEven = LEASCCMD__DEINTERLEAVEEVENEVEN,
    LEA_deinterleaveEvenOdd = LEASCCMD__DEINTERLEAVEEVENODD,
    LEA_deinterleaveOddEven = LEASCCMD__DEINTERLEAVEODDEVEN,
    LEA_deinterleaveOddOdd = LEASCCMD__DEINTERLEAVEODDODD,
    LEA_deinterleaveLong = LEASCCMD__DEINTERLEAVELONG
} LEA_command;

//*****************************************************************************
//
//! \brief This function initializes the LEA peripheral and initializes the LEA
//! functions for use.
//!
//! This function must be called before any other function in the library and
//! initializes the LEA peripheral for operation.
//!
//! The stack pointer must point to the top of the allocated LEA stack and will
//! be decremented when the LEA_suspend command is invoked. Each LEA_suspend
//! command will save 104 bytes of context data to the stack and it is the
//! responsibility of the application to allocate a stack size large enough for
//! the worst case command nesting. If the LEA_suspend command is not invoked
//! the stack will not be used by LEA and the stack size will effectively be
//! zero. Passing an address of zero will initialize the stack pointer to the
//! top of LEA memory.
//!
//! The application will need to enable LEA execution and LEA interrupts in LPM
//! using the enableExecutionInLPM and enableInterruptInLPM arguments
//! respectively if the application requires LEA operation and interrupts in
//! low power modes.
//!
//! Before invoking any commands the application must call LEA_enable() to
//! enable LEA to accept commands.
//!
//! \param stackPointer         LEA stack pointer address , zero will use the
//!                             LEA memory top register for initialization.
//! \param enableExecutonInLPM  If true, LEA will continue to execute when the
//!                             CPU is in LPM.
//! \param enableInterruptInLPM If true, LEA will interrupt CPU when the
//!                             command completes in LPM.
//!
//! \return None
//
//*****************************************************************************
extern void LEA_init(uint32_t stackPointer,
                     bool enableExecutonInLPM,
                     bool enableInterruptInLPM);

//*****************************************************************************
//
//! \brief This function terminates any running LEA operations and disables the
//! module operation.
//!
//! This function will terminate LEA operations and disable the peripheral. In
//! order to use the LEA peripheral again LEA_init() must be called to
//! reinitialize LEA.
//!
//! If the application would simply like to disable or enable commands from
//! being accepted by the LEA module LEA_disable() and LEA_enable() can be used
//! to perform a soft disable that does not require LEA to be initialized
//! again.
//!
//! \return None
//
//*****************************************************************************
extern void LEA_terminate(void);

//*****************************************************************************
//
//! \brief Enables individual LEA interrupt sources.
//!
//! Enables the indicated LEA interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor. This function does not clear interrupt flags.
//!
//! \param mask     The bit mask of the interrupt sources to be enabled.
//!                 Mask is the logical OR of any of the following:
//!                     - \b LEA_COMMAND_COMPLETE_INTERRUPT
//!                     - \b LEA_SCALAR_DATA_INCONSISTENCY_INTERRUPT
//!                     - \b LEA_ADDRESS_OUT_OF_RANGE_INTERRUPT
//!                     - \b LEA_COMMAND_OVERFLOW_INTERRUPT
//!                     - \b LEA_ALL_INTERRUPTS
//!
//! \return None
//
//*****************************************************************************
extern void LEA_enableInterrupt(uint16_t mask);

//*****************************************************************************
//
//! \brief Disables individual LEA interrupt sources.
//!
//! Disables the indicated LEA interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor. This function does not clear interrupt flags.
//!
//! \param mask     The bit mask of the interrupt sources to be disabled.
//!                 Mask is the logical OR of any of the following:
//!                     - \b LEA_COMMAND_COMPLETE_INTERRUPT
//!                     - \b LEA_SCALAR_DATA_INCONSISTENCY_INTERRUPT
//!                     - \b LEA_ADDRESS_OUT_OF_RANGE_INTERRUPT
//!                     - \b LEA_COMMAND_OVERFLOW_INTERRUPT
//!                     - \b LEA_ALL_INTERRUPTS
//!
//! \return None
//
//*****************************************************************************
extern void LEA_disableInterrupt(uint16_t mask);

//*****************************************************************************
//
//! \brief Gets the current LEA interrupt status.
//!
//! This returns the interrupt status for LEA based on which flag is passed.
//!
//! \param mask     The masked interrupt flag status to be returned.
//!                 Mask is the logical OR of any of the following:
//!                     - \b LEA_COMMAND_COMPLETE_INTERRUPT_FLAG
//!                     - \b LEA_SCALAR_DATA_INCONSISTENCY_INTERRUPT_FLAG
//!                     - \b LEA_ADDRESS_OUT_OF_RANGE_INTERRUPT_FLAG
//!                     - \b LEA_COMMAND_OVERFLOW_INTERRUPT_FLAG
//!                     - \b LEA_ALL_INTERRUPT_FLAGS
//!
//! \return         Logical OR of any of the following:
//!                     - \b LEA_COMMAND_COMPLETE_INTERRUPT_FLAG
//!                     - \b LEA_SCALAR_DATA_INCONSISTENCY_INTERRUPT_FLAG
//!                     - \b LEA_ADDRESS_OUT_OF_RANGE_INTERRUPT_FLAG
//!                     - \b LEA_COMMAND_OVERFLOW_INTERRUPT_FLAG
//!                     - \b LEA_ALL_INTERRUPT_FLAGS
//!                 \n indicating the status of the masked flags
//
//*****************************************************************************
extern uint16_t LEA_getInterruptStatus(uint16_t mask);

//*****************************************************************************
//
//! \brief Clears LEA interrupt sources.
//!
//! The LEA interrupt source is cleared, so that it no longer asserts.
//!
//! \param mask     The bit mask of the interrupt sources to be cleared.
//!                 Mask is the logical OR of any of the following:
//!                     - \b LEA_COMMAND_COMPLETE_INTERRUPT_FLAG
//!                     - \b LEA_SCALAR_DATA_INCONSISTENCY_INTERRUPT_FLAG
//!                     - \b LEA_ADDRESS_OUT_OF_RANGE_INTERRUPT_FLAG
//!                     - \b LEA_COMMAND_OVERFLOW_INTERRUPT_FLAG
//!                     - \b LEA_ALL_INTERRUPT_FLAGS
//!
//! \return None
//
//*****************************************************************************
extern void LEA_clearInterrupt(uint16_t mask);

//*****************************************************************************
//
//! \brief Set LEA interrupt sources.
//!
//! The LEA interrupt source is set from software to trigger the LEA interrupt
//! service routine.
//!
//! \param mask     The bit mask of the interrupt sources to be set.
//!                 Mask is the logical OR of any of the following:
//!                     - \b LEA_COMMAND_COMPLETE_INTERRUPT_FLAG
//!                     - \b LEA_SCALAR_DATA_INCONSISTENCY_INTERRUPT_FLAG
//!                     - \b LEA_ADDRESS_OUT_OF_RANGE_INTERRUPT_FLAG
//!                     - \b LEA_COMMAND_OVERFLOW_INTERRUPT_FLAG
//!                     - \b LEA_ALL_INTERRUPT_FLAGS
//!
//! \return None
//
//*****************************************************************************
extern void LEA_setInterruptFlag(uint16_t mask);

//*****************************************************************************
//
//! \brief Enables LEA for operation.
//!
//! \return None
//
//*****************************************************************************
extern void LEA_enable(void);

//*****************************************************************************
//
//! \brief Halts operation and disables LEA.
//!
//! \return None
//
//*****************************************************************************
extern void LEA_disable(void);

//*****************************************************************************
//
//! \brief Check to see if LEA is busy executing a command.
//!
//! This function can be used by the application to check the status of the LEA
//! peripheral. If LEA is busy the application can wait or call the
//! LEA_suspendCommand() function before issuing another command.
//!
//! For commands that return a result such as LEA_polynomialScalar LEA will
//! signal that it is no longer busy, however the result must be picked up
//! before invoking a new command. For these commands LEA_isResultReady()
//! should be used to check if the result is ready to be read by the
//! application using the LEA_getResult() function.
//!
//! \return bool    Returns true when LEA is busy.
//
//*****************************************************************************
extern bool LEA_isBusy(void);

//*****************************************************************************
//
//! \brief Check to see if LEA is free to accept a new command.
//!
//! This function can be used by the application to check the status of the LEA
//! peripheral. The return will be true when LEA is not busy and there is no
//! result pending.
//!
//! \return bool    Returns true when LEA is free.
//
//*****************************************************************************
extern bool LEA_isFree(void);

//*****************************************************************************
//
//! \brief Check to see if the previous command has completed and the result is
//! ready to be read.
//!
//! This function can be used by the application to check if the command has
//! completed and the result is ready. This function only applies to commands
//! that return a result such as LEA_polynomialScalar. The result can be read
//! using the LEA_getResult() function after which this function will return
//! false and LEA will enter the free state.
//!
//! \return bool    Returns true when the result is ready.
//
//*****************************************************************************
extern bool LEA_isResultReady(void);

//*****************************************************************************
//
//! \brief This function returns the result of a LEA command.
//!
//! This function can be used by the application to get the 32-bit result of a
//! command in cases where LEA returns a value such as the LEA_polynomialScalar
//! command. Upon reading the result LEA_isResultReady() will return false and
//! LEA will enter the free state.
//!
//! Application code can use the LEA_isResultReady() function to check if the
//! command has completed before reading the result.
//!
//! \return uint32_t    32-bit LEA result.
//
//*****************************************************************************
extern uint32_t LEA_getResult(void);

//*****************************************************************************
//
//! \brief This function will invoke a specified LEA command with or without
//! interrupts.
//!
//! This function will configure LEA to execute a specific command passed
//! by the command argument. The params argument must point to a parameter
//! structure that resides in LEA RAM with type matching the command requested.
//! The application can request the command to set interrupt flags using the
//! mode argument. This is recommended in scenarios where the application polls
//! using the LEA_isResultReady() or LEA_isBusy() function to avoid setting
//! interrupt flags.
//!
//! It is recommended to call the LEA_isFree() function first to check that
//! LEA is not busy and there is no result pending that could be overwritten.
//!
//! Some commands can accidentally trigger the out of range interrupt flag based
//! on the location of the data arrays and increment parameters. The command
//! will still complete with the correct result in all scenarios. Refer to the
//! device users guide for complete details on effected commands and conditions.
//! If the out of range interrupt is not enabled or needed the flag can
//! effectively be ignored.
//!
//! \param command  is the LEA command to invoke.
//! \param params   is the LEA parameter structure that matches the command
//!                 being invoked.
//! \param mode     is the interrupt mode to invoke the command with.
//!
//! \return None
//
//*****************************************************************************
extern void LEA_invokeCommand(LEA_command command,
                              void *params,
                              uint16_t mode);

//*****************************************************************************
//
//! \brief This function will enter low power modes with interrupts enabled.
//!
//! This function will check if LEA is busy before entering low power mode
//! (LPM) with interrupts enabled. This sequence is necessary to ensure that
//! the CPU only enters sleep modes when LEA is active and can generate an
//! interrupt. When using a debugger it is possible that the debugger allows
//! LEA to run asynchronous from the CPU and complete commands earlier than
//! expected. To prevent the CPU from entering a permanent sleep state it is
//! recommended to use this function instead of the standard __bis_SR_register
//! intrinsic when using the LEA module with LPM. To enter LPM0 the application
//! should pass LPM0_bits as the mode arguments.
//!
//! \param mode     is the low power mode to enter.
//!
//! \return None
//
//*****************************************************************************
extern void LEA_enterLpmWithInterrupts(uint16_t mode);

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_mac command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in Q15 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t input2;        /**< LEA RAM address to input2 vector containing values in Q15 format */
    uint16_t output;        /**< LEA RAM address to output vector  containing values in IQ31 format*/
    uint16_t reserved2;     /**< reserved */
} LEA_macParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_max command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in int16_t format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t output;        /**< LEA RAM address to output vector which is of size two. output[0] will have max value; output[1] will have index to max value */
} LEA_maxParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_mi command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in int16_t format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t output;        /**< LEA RAM address to output vector which is of size two. output[0] will have min value; output[1] will have index to min value */
} LEA_minParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_maxUnsigned command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in uint16_t format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t output;        /**< LEA RAM address to output vector which is of size two. output[0] will have max value; output[1] will have index to max value */
} LEA_maxUnsignedParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_minUnsigned command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in uint16_t format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t output;        /**< LEA RAM address to output vector which is of size two. output[0] will have max value; output[1] will have index to max value */
} LEA_minUnsignedParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_addMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in signed, unsigned or Q15 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t input2;        /**< LEA RAM address to input2 vector containing values in signed, unsigned or Q15 format */
    uint16_t output;        /**< LEA RAM address to output vector */
    uint16_t input1Offset;  /**< offset for input1 pointer after every 2 sets of 16-bits additions */
    uint16_t input2Offset;  /**< offset for input2 pointer after every 2 sets of 16-bits additions */
    uint16_t outputOffset;  /**< offset for output pointer after every 2 sets of 16-bits additions */
} LEA_addMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_subMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in signed, unsigned or Q15 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t input2;        /**< LEA RAM address to input2 vector containing values in signed, unsigned or Q15 format */
    uint16_t output;        /**< LEA RAM address to output vector */
    uint16_t input1Offset;  /**< offset for input1 pointer after every 2 sets of 16-bits subtractions */
    uint16_t input2Offset;  /**< offset for input2 pointer after every 2 sets of 16-bits subtractions */
    uint16_t outputOffset;  /**< offset for output pointer after every 2 sets of 16-bits subtractions */
} LEA_subMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_mpyMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in Q15 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t input2;        /**< LEA RAM address to input2 vector containing values in Q15 format */
    uint16_t output;        /**< LEA RAM address to output vector */
    uint16_t input1Offset;  /**< offset for input1 pointer after every 16-bit multiplication */
    uint16_t input2Offset;  /**< offset for input2 pointer after every 16-bit multiplication */
    uint16_t outputOffset;  /**< offset for output pointer after every 16-bit multiplication */
} LEA_mpyMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_macMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in IQ16 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t input2;        /**< LEA RAM address to input2 vector containing values in IQ16 format */
    uint16_t output;        /**< LEA RAM address to output vector containing values in IQ16 format*/
    uint16_t input1Offset;  /**< offset for input1 pointer after every 16-bit multiply accumulate */
    uint16_t input2Offset;  /**< offset for input2 pointer after every 16-bit multiply accumulate */
    uint16_t outputOffset;  /**< offset for output pointer after every 16-bit multiply accumulate */
} LEA_macMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_maxMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in int16_t format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t input1Offset;  /**< offset for input1 pointer after every max  */
    uint16_t output;        /**< LEA RAM address to output vector which is of size two. output[0] will have max value; output[1] will have index to max value */
    uint16_t reserved2;     /**< reserved */
} LEA_maxMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_minMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in int16_t format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t input1Offset;  /**< offset for input1 pointer after every min calculation  */
    uint16_t output;        /**< LEA RAM address to output vector which is of size two. output[0] will have min value; output[1] will have index to min value */
    uint16_t reserved2;     /**< reserved */
} LEA_minMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_mpyMatrixRow command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;    /**< LEA RAM address to input vector containing values in Q15 format */
    uint16_t reserved1; /**< padding */
    uint16_t rowSize;   /**< If PxN * NxM matrix multiplication, rowSize=N */
    uint16_t colSize;   /**< If PxN * NxM matrix multiplication, colSize=M */
    uint16_t colVector; /**< column vector */
    uint16_t output;    /**< output vector */
} LEA_mpyMatrixRowParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_mpyComplexMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in cplxIQ31 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t input2;        /**< LEA RAM address to input2 vector containing values in cplxIQ31 format */
    uint16_t output;        /**< LEA RAM address to output vector containing values in cplxIQ31 format */
    uint16_t input1Offset;  /**< offset for input1 pointer after every set of cplxIQ31 multiplication */
    uint16_t input2Offset;  /**< offset for input2 pointer after every set of cplxIQ31 multiplication */
    uint16_t outputOffset;  /**< offset for output pointer after every set of cplxIQ31 multiplication */
} LEA_mpyComplexMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_macComplexMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in cplxQ15 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t input2;        /**< LEA RAM address to input2 vector containing values in cplxQ15 format */
    uint16_t output;        /**< LEA RAM address to output vector containing values in cplxIQ31 format*/
    uint16_t input1Offset;  /**< offset for input1 pointer after every 32-bit multiply accumulate */
    uint16_t input2Offset;  /**< offset for input2 pointer after every 32-bit multiply accumulate */
    uint16_t reserved;
} LEA_macComplexMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_macComplexConjugateMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in cplxIQ31 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t input2;        /**< LEA RAM address to input2 vector containing values in cplxIQ31 format */
    uint16_t output;        /**< LEA RAM address to output vector containing values in cplxIQ31 format */
    uint16_t input1Offset;  /**< offset for input1 pointer after every set of cplxIQ31 multiplication */
    uint16_t input2Offset;  /**< offset for input2 pointer after every set of cplxIQ31 multiplication */
    uint16_t reserved2;     /**< reserved */
} LEA_macComplexConjugateMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_maxUnsignedMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in uint16_t format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t input1Offset;  /**< offset for input1 pointer after every max  */
    uint16_t output;        /**< LEA RAM address to output vector which is of size two. output[0] will have max value; output[1] will have index to max value */
    uint16_t reserved2;     /**< reserved */
} LEA_maxUnsignedMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_minUnsignedMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in uint16_t format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t input1Offset;  /**< offset for input1 pointer after every min calculation  */
    uint16_t output;        /**< LEA RAM address to output vector which is of size two. output[0] will have max value; output[1] will have index to max value */
    uint16_t reserved2;     /**< reserved */
} LEA_minUnsignedMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_addLongMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in signed, unsigned or IQ31 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t input2;        /**< LEA RAM address to input2 vector containing values in signed, unsigned or IQ31 format */
    uint16_t output;        /**< LEA RAM address to output vector */
    uint16_t input1Offset;  /**< offset for input1 pointer after every 32-bit additions */
    uint16_t input2Offset;  /**< offset for input2 pointer after every 32-bit additions */
    uint16_t outputOffset;  /**< offset for output pointer after every 32-bit additions */
} LEA_addLongMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_subLongMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in signed, unsigned or IQ31 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t input2;        /**< LEA RAM address to input2 vector containing values in signed, unsigned or IQ31 format */
    uint16_t output;        /**< LEA RAM address to output vector */
    uint16_t input1Offset;  /**< offset for input1 pointer after every 32-bit subtractions */
    uint16_t input2Offset;  /**< offset for input2 pointer after every 32-bit subtractions */
    uint16_t outputOffset;  /**< offset for output pointer after every 32-bit subtractions */
} LEA_subLongMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_mpyLongMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in IQ31 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t input2;        /**< LEA RAM address to input2 vector containing values in IQ31 format */
    uint16_t output;        /**< LEA RAM address to output vector containing values in IQ31 format */
    uint16_t input1Offset;  /**< offset for input1 pointer after every set of 32bit multiplication */
    uint16_t input2Offset;  /**< offset for input2 pointer after every set of 32bit multiplication */
    uint16_t outputOffset;  /**< offset for output pointer after every set of 32bit multiplication */
} LEA_mpyLongMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_macLongMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in IQ31 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t input2;        /**< LEA RAM address to input2 vector containing values in IQ31 format */
    uint16_t output;        /**< LEA RAM address to output vector containing values in IQ31 format*/
    uint16_t input1Offset;  /**< offset for input1 pointer after every 32-bit multiply accumulate */
    uint16_t input2Offset;  /**< offset for input2 pointer after every 32-bit multiply accumulate */
    uint16_t reserved;
} LEA_macLongMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_maxLongMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in int32_t format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t output;        /**< LEA RAM address to output vector which is of size two. output[0] will have max value; output[1] will have index to max value */
    uint16_t input1Offset;  /**< offset for input1 pointer after every max  */
    uint16_t reserved2;     /**< reserved */
} LEA_maxLongMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_minLongMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in int32_t format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t output;        /**< LEA RAM address to output vector which is of size two. output[0] will have max value; output[1] will have index to max value */
    uint16_t input1Offset;  /**< offset for input1 pointer after every min calculation  */
    uint16_t reserved2;     /**< reserved */
} LEA_minLongMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_maxUnsignedLongMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in uint32_t format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t output;        /**< LEA RAM address to output vector which is of size two. output[0] will have max value; output[1] will have index to max value */
    uint16_t input1Offset;  /**< offset for input1 pointer after every max  */
    uint16_t reserved2;     /**< reserved */
} LEA_maxUnsignedLongMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_minUnsignedLongMatrix command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input1 vector containing values in uint32_t format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t output;        /**< LEA RAM address to output vector which is of size two. output[0] will have max value; output[1] will have index to max value */
    uint16_t input1Offset;  /**< offset for input1 pointer after every min calculation  */
    uint16_t reserved2;     /**< reserved */
} LEA_minUnsignedLongMatrixParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_polynomial command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input vector containing values in Q15 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t output;        /**< LEA RAM address to output vector containing values in Q15 format */
    uint16_t coeffs;        /**< LEA RAM address to coefficients in Q15 format */
    uint16_t order;         /**< polynomial order */
    uint32_t scaleFactor;   /**< polynomial scale factor */
} LEA_polynomialParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_polynomialScalar command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint32_t input;         /**< Scalar input in Q31 format */
    uint16_t coeffs;        /**< LEA RAM address to coefficients in Q131 format */
    uint16_t order;         /**< polynomial order */
    uint16_t scaleFactor;   /**< polynomial integer scale factor */
    uint16_t reserved1;     /**< reserved */
} LEA_polynomialScalarParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_polynomialLong command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input vector containing values in Q31 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t output;        /**< LEA RAM address to output vector containing values in Q31 format */
    uint16_t coeffs;        /**< LEA RAM address to coefficients in Q131 format */
    uint16_t order;         /**< polynomial order */
    uint16_t scaleFactor;   /**< polynomial scale factor */
    uint16_t reserved2;     /**< reserved */
} LEA_polynomialLongParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_fir command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;                /**< LEA RAM address to input1 vector containing values in Q15 format */
    uint16_t reserved1;             /**< reserved */
    uint16_t vectorSize;            /**< Output vector size */
    uint16_t coeffs;                /**< Filter coefficients in Q15 format */
    uint16_t output;                /**< LEA RAM address to output vector  containing values in Q15 format */
    uint16_t filterLength;          /**< Filter length, a multiple of two */
    uint16_t circularBufferMask;    /**< When set to value other than 0xff circular buffering is enabled */
    uint16_t reserved2;             /**< reserved */
} LEA_firParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_firComplex command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;                /**< LEA RAM address to input1 vector containing values in cplxQ15 format */
    uint16_t reserved1;             /**< reserved */
    uint16_t vectorSize;            /**< Output vector size */
    uint16_t coeffs;                /**< Filter coefficients in cplxQ15 format */
    uint16_t output;                /**< LEA RAM address to output vector containing values in cplxQ15 format */
    uint16_t filterLength;          /**< Filter length, a multiple of two */
    uint16_t circularBufferMask;    /**< When set to value other than 0xff circular buffering is enabled */
    uint16_t reserved2;             /**< padding */
} LEA_firComplexParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_firLong command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;                /**< LEA RAM address to input1 vector containing values in IQ31 format */
    uint16_t reserved1;             /**< reserved */
    uint16_t vectorSize;            /**< Output vector size */
    uint16_t coeffs;                /**< Filter coefficients in IQ31 format */
    uint16_t output;                /**< LEA RAM address to output vector  containing values in IQ31 format */
    uint16_t filterLength;          /**< Filter length, a multiple of two */
    uint16_t circularBufferMask;    /**< When set to value other than 0xff circular buffering is enabled */
    uint16_t reserved2;             /**< padding */
} LEA_firLongParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_firComplexLong command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;                /**< LEA RAM address to input1 vector containing values in cplxIQ31 format */
    uint16_t reserved1;             /**< reserved */
    uint16_t vectorSize;            /**< Output vector size */
    uint16_t coeffs;                /**< Filter coefficients in cplxIQ31 format */
    uint16_t output;                /**< LEA RAM address to output vector containing values in cplxIQ31 format */
    uint16_t filterLength;          /**< Filter length, a multiple of two */
    uint16_t circularBufferMask;    /**< When set to value other than 0xff circular buffering is enabled */
    uint16_t reserved2;             /**< padding */
} LEA_firComplexLongParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_iir command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input vector containing values in Q15 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t output;        /**< LEA RAM address to output vector containing values in Q15 format */
    uint16_t state;         /**< IIR state/ Size of state array is 4 * sizeof(int16_t) */
    uint16_t coeffs;        /**< filter coefficients */
    uint16_t direction;     /**< +1 for incremental access of input Vector, -1 for decremental access */
} LEA_iirParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_biquadWithBiasAndMinMax command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input vector containing values in Q15 format */
    uint16_t reserved1;     /**< padding */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t output;        /**< LEA RAM address to output vector containing values in Q15 format */
    uint16_t stateQ1;       /**< state value to be passed from one invocation to the next */
    uint16_t stateQ2;       /**< state value to be passed from one invocation to the next */
    uint16_t Bias;          /**< Bias value for filter */
    int16_t A0;             /**< a0 coefficient value */
    int16_t A1;             /**< a1 coefficient value */
    int16_t A2;             /**< a2 coefficient value */
    int16_t A3;             /**< a3 coefficient value */
    int16_t B0;             /**< b0 coefficient value */
    int16_t B1;             /**< b1 coefficient value */
    int16_t B2;             /**< b2 coefficient value */
    uint16_t reserved2;     /**< padding */
    uint16_t Min;           /**< Min value output */
    uint16_t reserved3;     /**< padding */
    uint16_t Max;           /**< Max value output */
} LEA_biquadWithBiasAndMinMaxParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_goertzel command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input vector containing values in Q15 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t output;        /**< LEA RAM address to output vector containing values in Q15 format */
    int16_t coeffCos;       /**< cos coefficient */
    int16_t coeffSin;       /**< sin coefficient */
} LEA_goertzelParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_fft command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input vector containing values in Q15 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t log2Size;      /**< log2 of vectorSize */
} LEA_fftParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_fftComplexFixedScaling command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input vector containing values in cplxQ15 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSizeBy2; /**< Input vector size divided by two */
    uint16_t log2Size;      /**< log2(vectorSize) */
} LEA_fftComplexFixedScalingParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_fftComplexAutoScaling command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input vector containing values in cplxQ15 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSizeBy2; /**< Input vector size divided by two */
    uint16_t log2Size;      /**< log2(vectorSize) */
} LEA_fftComplexAutoScalingParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_fftLong command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input vector containing values in IQ31 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t log2Size;      /**< log2 of vectorSize */
} LEA_fftLongParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_fftComplexLong command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;        /**< LEA RAM address to input vector containing values in cplxIQ31 format */
    uint16_t reserved1;     /**< reserved */
    uint16_t vectorSize;    /**< Input vector size */
    uint16_t log2Size;      /**< log2(vectorSize) */
} LEA_fftComplexLongParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_bitReverseComplexEven command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;            /**< LEA RAM address to input vector containing values in cplxQ15 format */
    uint16_t reserved1;         /**< reserved */
    uint16_t sqrtVectorSize;    /**< square root of vector size */
    uint16_t reserved2;         /**< reserved */
} LEA_bitReverseComplexEvenParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_bitReverseComplexOdd command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;            /**< LEA RAM address to input vector containing values in cplxQ15 format */
    uint16_t reserved1;         /**< reserved */
    uint16_t sqrtVectorSizeBy2; /**< square root of vector size divided by two */
    uint16_t reserved2;         /**< reserved */
} LEA_bitReverseComplexOddParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_bitReverseComplexLongEven command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;            /**< LEA RAM address to input vector containing values in cplxIQ31 format */
    uint16_t reserved1;         /**< reserved */
    uint16_t sqrtVectorSize;    /**< square root of vector size */
    uint16_t reserved2;         /**< reserved */
} LEA_bitReverseComplexLongEvenParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_bitReverseComplexLongOdd command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;            /**< LEA RAM address to input vector containing values in cplxIQ31 format */
    uint16_t reserved1;         /**< reserved */
    uint16_t sqrtVectorSizeBy2; /**< square root of vector size */
    uint16_t reserved2;         /**< reserved */
} LEA_bitReverseComplexLongOddParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_moveList command command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input;             /**< LEA RAM address for input vector of src and dst pairs */
    uint16_t vectorSize;        /**< Input vector size */
} LEA_moveLongListParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_deinterleaveEvenEven command command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;            /**< LEA RAM address to input1 vector containing values in int16_t format */
    uint16_t reserved1;         /**< reserved */
    uint16_t vectorSize;        /**< Input vector size */
    uint16_t interleaveDepth;   /**< interleave depth */
    uint16_t output;            /**< LEA RAM address to output vector containing values in int16_t format */
    uint16_t reserved;
} LEA_deinterleaveEvenEvenParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_deinterleaveEvenOdd command command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;            /**< LEA RAM address to input1 vector containing values in int16_t format */
    uint16_t reserved1;         /**< reserved */
    uint16_t vectorSize;        /**< Input vector size */
    uint16_t interleaveDepth;   /**< interleave depth */
    uint16_t output;            /**< LEA RAM address to output vector containing values in int16_t format */
    uint16_t reserved;
} LEA_deinterleaveEvenOddParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_deinterleaveOddEven command command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;            /**< LEA RAM address to input1 vector containing values in int16_t format */
    uint16_t reserved1;         /**< reserved */
    uint16_t vectorSize;        /**< Input vector size */
    uint16_t interleaveDepth;   /**< interleave depth */
    uint16_t output;            /**< LEA RAM address to output vector containing values in int16_t format */
    uint16_t reserved;
} LEA_deinterleaveOddEvenParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_deinterleaveOddOdd command command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;            /**< LEA RAM address to input1 vector containing values in int16_t format */
    uint16_t reserved1;         /**< reserved */
    uint16_t vectorSize;        /**< Input vector size */
    uint16_t interleaveDepth;   /**< interleave depth */
    uint16_t output;            /**< LEA RAM address to output vector containing values in int16_t format */
    uint16_t reserved2;         /**< reserved */
} LEA_deinterleaveOddOddParams;

//*****************************************************************************
//
//! \brief Parameter structure that should be paired with the
//! LEA_deinterleaveLong command command when using LEA_invokeCommand().
//
//*****************************************************************************
typedef struct
{
    uint16_t input1;            /**< LEA RAM address to input1 vector containing values in int32_t format */
    uint16_t reserved1;         /**< reserved */
    uint16_t vectorSize;        /**< Input vector size */
    uint16_t interleaveDepth;   /**< interleave depth */
    uint16_t output;            /**< LEA RAM address to output vector containing values in int32_t format */
    uint16_t reserved;
} LEA_deinterleaveLongParams;

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
#endif // __MSP430WARE_LEA_H__

//*****************************************************************************
//
//! Close the doxygen group for lea_api
//! @}
//
//*****************************************************************************
