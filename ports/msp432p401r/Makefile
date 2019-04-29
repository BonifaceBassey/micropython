include ../../py/mkenv.mk

# qstr definitions (must come before including py.mk)
QSTR_DEFS = qstrdefsport.h

# include py core make definitions
include $(TOP)/py/py.mk

# The compiler to be used.
ifndef CROSS
$(info Please set CROSS compiler, e.g. CROSS=1)
$(error unspecified compiler)
endif

ifeq ($(CROSS), 1)
# Where to find header files that do not live in the source directory.
IPATH += driverlib
IPATH += driverlib/include
IPATH += driverlib/board_include
IPATH += driverlib/board_include/CMSIS

INC += -I.
INC += -I$(TOP)
INC += -I$(TOP)/lib/mp-readline
INC += -I$(TOP)/stmhal
INC += -I$(BUILD)

# Include the common make definitions.
include Makefile.defs
DFU = $(TOP)/tools/dfu.py
PYDFU = $(TOP)/tools/pydfu.py
endif

LIBS =

SRC_C = \
	bsp/startup_gcc.c \
	bsp/system_msp432p401r.c \
	main.c \
	src/msp432p401r_uart.c \
        src/msp432p401r_mphalport.c \
	lib/utils/printf.c \
	lib/utils/pyexec.c \
	lib/libc/string0.c \
	lib/mp-readline/readline.c \
	$(BUILD)/_frozen_mpy.c \
#lib/utils/stdout_helpers.c 

OBJ = $(PY_CORE_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o))

ifeq ($(CROSS), 1)
all: $(BUILD)/firmware.axf
else
all: $(BUILD)/firmware.elf
endif

# The rule to create the target directory.
#
#${BUILD}:
#	@mkdir -p ${BUILD}

$(BUILD)/_frozen_mpy.c: frozentest.mpy $(BUILD)/genhdr/qstrdefs.generated.h
	$(ECHO) "MISC freezing bytecode"
	$(Q)$(TOP)/tools/mpy-tool.py -f -q $(BUILD)/genhdr/qstrdefs.preprocessed.h -mlongint-impl=none $< > $@


# Rules for building the examples.
#
${BUILD}/firmware.axf: $(OBJ)
#${BUILD}/firmware.axf: ${ROOT}/driverlib/MSP432P4xx/${COMPILER}/msp432p4xx_driverlib.a
${BUILD}/firmware.axf: driverlib/build/libmsp432.a
${BUILD}/firmware.axf: bsp/build/libbsp432.a
${BUILD}/firmware.axf: msp432p401r.ld
SCATTERgcc_firmware=msp432p401r.ld
ENTRY_firmware=resetISR
CFLAGSgcc=-DTARGET_IS_MSP432P4XX
	
# Flashing
.PHONY: deploy
deploy:
	$(ECHO) "Stripping Executable $< ${BUILD}/firmware.axf"
	toolchain/bin/arm-none-eabi-strip --strip-all ${BUILD}/firmware.axf
	$(ECHO) "Writing $< to the board"
	# Flashing
	DSLite/DebugServer/bin/DSLite load -c MSP432P401R.ccxml -f build/firmware.axf


# Include the automatically generated dependency files.
#
#ifneq (${MAKECMDGOALS},clean)
#-include ${wildcard ${BUILD}/*.d} __dummy__
#endif

include $(TOP)/py/mkrules.mk
