/*
 * Linker configuration file for MSP432.
 *
 * Copyright (c) 2016, Sultan Qasim Khan
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

_STACK_SIZE = 2K;
_INTVECS_BASE = 0x00000000;

MEMORY
{
    FLASH                 (RX) : ORIGIN = 0x00000000, LENGTH = 0x00040000
    FLASH_OTP             (RX) : ORIGIN = 0x00200000, LENGTH = 0x00004000
    SRAM                  (RWX): ORIGIN = 0x20000000, LENGTH = 0x00010000
}

SECTIONS
{
    .intvecs (_INTVECS_BASE) : AT (_INTVECS_BASE) {
        KEEP (*(.intvecs))
    } > FLASH

    .text : {
        CREATE_OBJECT_SYMBOLS
        KEEP (*(.text))
        *(.text.*)
        . = ALIGN(4);
        KEEP (*(.ctors))
        . = ALIGN(4);
        KEEP (*(.dtors))
        . = ALIGN(4);
        __init_array_start = .;
        KEEP (*(.init_array*))
        __init_array_end = .;
        . = ALIGN(4);
        *(.init)
        *(.fini*)
        . = ALIGN(4);
    } > FLASH AT> FLASH

    .rodata : {
        *(.rodata)
        *(.rodata.*)
        . = ALIGN(4);
    } > FLASH AT> FLASH

    .ARM.exidx : {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > FLASH AT> FLASH

    .ARM.extab : {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > FLASH AT> FLASH

    __etext = .;

    .vtable : {
        KEEP (*(.vtable))
        . = ALIGN(4);
    } > SRAM

    .data : {
        __data_load__ = LOADADDR (.data);
        __data_start__ = .;
        KEEP (*(.data))
        KEEP (*(.data*))
        . = ALIGN(4);
        __data_end__ = .;
    } > SRAM AT> FLASH

    .bss : {
        __bss_start__ = .;
        *(.shbss)
        KEEP (*(.bss))
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > SRAM AT> SRAM

    .heap : {
        __heap_bottom = .;
        . += ORIGIN(SRAM) + LENGTH(SRAM) - __heap_bottom - _STACK_SIZE;
        . = ALIGN(8);
        __heap_top = .;
    } > SRAM AT> SRAM

    .stack (NOLOAD) : {
        __stack_bottom = .;
        . += _STACK_SIZE;
        . = ALIGN(8);
        __stack_top = .;
    } > SRAM AT> SRAM
}
