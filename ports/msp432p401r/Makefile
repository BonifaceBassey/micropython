# Copyright (c) 2016, Sultan Qasim Khan
# Modified (c) 2018, Boniface Bassey

# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# Main target
PRODUCT_NAME := msp432p401r
all: $(PRODUCT_NAME)

ifeq ($(CROSS_COMPILE),)
    CROSS_COMPILE := toolchain/bin/arm-none-eabi-
endif

# Build tools
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OC = $(CROSS_COMPILE)objcopy
OD = $(CROSS_COMPILE)objdump
AR = $(CROSS_COMPILE)ar

# Header includes
DLIB_INCLUDE_DIRS := \
    driverlib/include \
    driverlib/board_include \
    driverlib/board_include/CMSIS
BSP_INCLUDE_DIRS := bsp/include
INCLUDE_DIRS := $(DLIB_INCLUDE_DIRS) $(BSP_INCLUDE_DIRS) include
DLIB_HEADERS := \
    $(shell find driverlib/include -type f) \
    $(shell find driverlib/board_include -type f)
BSP_HEADERS := \
    $(shell find bsp/include -type f)
HEADERS := \
    $(DLIB_HEADERS) \
    $(BSP_HEADERS) \
    $(shell find include -type f)

# Build flags
LANG_FLAGS      := -std=c11 -Wall -Wextra -pedantic -Wno-unused-parameter
ARM_FLAGS       := -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Os
SECTION_FLAGS   := -ffunction-sections -fdata-sections
DEFINE_FLAGS    := -D__MSP432P401R__ -DTARGET_IS_MSP432P4XX -DUSE_CMSIS_REGISTER_FORMAT
INCLUDE_FLAGS   := $(patsubst %, -I %, $(INCLUDE_DIRS))

CFLAGS = $(LANG_FLAGS) $(ARM_FLAGS) $(SECTION_FLAGS) $(DEFINE_FLAGS) $(INCLUDE_FLAGS)

LFLAGS  := --gc-sections -T msp432.ld
OCFLAGS := -Obinary
ODFLAGS	:= -S

# Static libraries
LIB_GCC_PATH    := $(shell ${CC} ${CFLAGS} -print-libgcc-file-name)
LIBC_PATH       := $(shell ${CC} ${CFLAGS} -print-file-name=libc.a)
LIBM_PATH       := $(shell ${CC} ${CFLAGS} -print-file-name=libm.a)
LIB_MSP_PATH    := driverlib/build/libmsp432.a
LIB_BSP_PATH    := bsp/build/libbsp432.a

LIB_PATHS = $(LIB_GCC_PATH) $(LIBC_PATH) $(LIBM_PATH) $(LIB_MSP_PATH) $(LIB_BSP_PATH)

# Building the driverlib
.PHONY: driverlib
driverlib: $(LIB_MSP_PATH)
DLIB_BUILD_DIR := driverlib/build
DRIVERLIB_SRCS := $(wildcard driverlib/*.c)
DRIVERLIB_OBJS := $(patsubst driverlib/%.c, $(DLIB_BUILD_DIR)/%.o, $(DRIVERLIB_SRCS))

$(DLIB_BUILD_DIR):
	mkdir -p $@

$(DLIB_BUILD_DIR)/%.o: driverlib/%.c $(DLIB_HEADERS) | $(DLIB_BUILD_DIR)
	$(CC) -c $(CFLAGS) -Dgcc $< -o $@

$(LIB_MSP_PATH): $(DRIVERLIB_OBJS) | $(DLIB_BUILD_DIR)
	$(AR) rcs $@ $^

# Building the BSP
.PHONY: bsp
bsp: $(LIB_BSP_PATH)
BSP_BUILD_DIR := bsp/build
BSP_SRCS      := $(wildcard bsp/*.c)
BSP_OBJS      := $(patsubst bsp/%.c, $(BSP_BUILD_DIR)/%.o, $(BSP_SRCS))

$(BSP_BUILD_DIR):
	mkdir -p $@

$(BSP_BUILD_DIR)/%.o: bsp/%.c $(BSP_HEADERS) | $(BSP_BUILD_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(LIB_BSP_PATH): $(BSP_OBJS) | $(BSP_BUILD_DIR)
	$(AR) rcs $@ $^

# Building the project
BUILD_DIR := build
SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

.PHONY: dirs $(PRODUCT_NAME)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: %.c $(HEADERS) | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(PRODUCT_NAME).axf: $(OBJS) $(LIB_MSP_PATH) $(LIB_BSP_PATH)
	$(LD) $(LFLAGS) -o $@ $(OBJS) $(LIB_PATHS)

$(BUILD_DIR)/$(PRODUCT_NAME): $(BUILD_DIR)/$(PRODUCT_NAME).axf
	$(OC) $(OCFLAGS) $< $@
	$(OD) $(ODFLAGS) $< > $@.lst

$(PRODUCT_NAME): build/$(PRODUCT_NAME)

# Flashing
.PHONY: load
load: $(BUILD_DIR)/$(PRODUCT_NAME).axf
	DSLite load -f $< -c MSP432P401R.ccxml

# Cleaning
.PHONY: clean clean_driverlib cleanall
clean:
	rm -rf $(BUILD_DIR) $(BSP_BUILD_DIR)

clean_driverlib:
	rm -rf $(DLIB_BUILD_DIR)

cleanall: clean clean_driverlib
