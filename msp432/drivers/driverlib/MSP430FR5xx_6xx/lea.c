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
#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_LEA_SC__

#include "lea.h"

void LEA_init(uint32_t stackPointer,
              bool enableExecutonInLPM,
              bool enableInterruptInLPM)
{
    /* Reset LEA control registers. */
    LEASCCNF0 = 0;
    LEASCCNF1 = 0;
    LEASCCNF2 = 0;

    /* Enable execution in LPM if selected. */
    if(enableExecutonInLPM)
    {
        LEASCCNF0 |= LEASCLPR;
    }

    /* Enable interrupts in LPM if selected. */
    if(enableInterruptInLPM)
    {
        LEASCCNF0 |= LEASCILPM;
    }

    /* Initialize LEA stack pointer. */
    if(stackPointer == 0)
    {
        LEASCCNF2 |= LEASCMT >> 2;      // default to top of memory
    }
    else
    {
        LEASCCNF2 |= stackPointer >> 2; // set user requested pointer
    }

    /* Initialize result and destination registers to zero. */
    LEASCPMS1 = 0;
    LEASCPMS0 = 0;
    LEASCPMDST = 0;

    return;
}

void LEA_terminate(void)
{
    /* Put LEA into reset. */
    LEASCCNF0 |= LEASCSWRST;

    return;
}

void LEA_enable(void)
{
    /* Enable LEA by setting command enable. */
    LEASCPMCTL |= LEASCCMDEN;

    return;
}

void LEA_disable(void)
{
    /* Disable LEA by clearing command enable. */
    LEASCPMCTL &= ~LEASCCMDEN;

    return;
}

void LEA_enableInterrupt(uint16_t mask)
{
    /* Enable the requested LEA interrupts. */
    LEASCIE |= mask;

    return;
}

void LEA_disableInterrupt(uint16_t mask)
{
    /* Disable the requested LEA interrupts. */
    LEASCIE &= ~mask;

    return;
}

uint16_t LEA_getInterruptStatus(uint16_t mask)
{
    /* Get the requested interrupt status. */
    return (LEASCIFG & mask);
}

void LEA_clearInterrupt(uint16_t mask)
{
    /* Clear the requested interrupt flags. */
    LEASCIFG = mask;

    return;
}

void LEA_setInterruptFlag(uint16_t mask)
{
    /* Set the requested interrupt flags. */
    LEASCIFGSET = mask;

    return;
}

bool LEA_isBusy(void)
{
    /* Check if LEA is busy. */
    return (LEASCCNF1 & LEASCBUSY);
}

bool LEA_isFree(void)
{
    /* Check if LEA is free using the FREES event flag. */
    return (LEASCCNF0 & LEASCFREES);
}

bool LEA_isResultReady(void)
{
    /* Check if the result is ready using the DONES event flag. */
    return (LEASCCNF0 & LEASCDONES);
}

uint32_t LEA_getResult(void)
{
    /* Return the 32-bit LEA result. */
    return (LEASCPMDST);
}

void LEA_invokeCommand(LEA_command command,
                       void *params,
                       uint16_t mode)
{
    uint16_t interruptState;

    /* Save interrupt state and disable interrupts. */
    interruptState = __get_interrupt_state();
    __disable_interrupt();

    /* Load source arguments to LEA. */
    if(command == LEA_moveLongList)
    {
        /* Special handling for LEA_moveLongList command. */
        LEASCPMS0 = ((LEA_moveLongListParams *)params)->input;      //input1
        LEASCPMS1 = ((LEA_moveLongListParams *)params)->vectorSize; //vectorSize
    }
    else if(command == LEA_polynomialScalar)
    {
        /* Special handling for LEA_polynomialScalar command. */
        LEASCPMS0 = ((LEA_polynomialScalarParams *)params)->input;  //input
        LEASCPMS1 = LEA_CONVERT_ADDRESS(params) + 1;                //params
    }
    else
    {
        /* Default handling for other commands. */
        LEASCPMS0 = (uint32_t)((uint16_t *)params)[0];  //input1
        LEASCPMS1 = LEA_CONVERT_ADDRESS(params) + 1;    //params
    }

    /* Invoke the requested command with interrupt. */
    LEASCPMCB = (uint32_t)command | (uint32_t)mode;

    /* Restore interrupt state. */
    __set_interrupt_state(interruptState);

    return;
}

void LEA_enterLpmWithInterrupts(uint16_t mode)
{
    uint16_t interruptState;

    /* Save interrupt state and disable interrupts. */
    interruptState = __get_interrupt_state();
    __disable_interrupt();

    /*
     * Check if LEA is busy before entering low power mode. Do not enter
     * low power mode if LEA is inactive and cannot generate an interrupt.
     */
    if(LEA_isBusy())
    {
        __bis_SR_register(GIE + mode);
    }

    /* Restore interrupt state. */
    __set_interrupt_state(interruptState);

    return;
}

#endif
