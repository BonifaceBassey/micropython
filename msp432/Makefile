include ../py/mkenv.mk

# qstr definitions (must come before including py.mk)
QSTR_DEFS = qstrdefsport.h

# include py core make definitions
include ../py/py.mk

# Defines the part type that this project uses.
DEVICE=__MSP432P401R__

# The base directory for MSPWare.
ROOT=drivers

#flash tool directory
UNIFLASH=uniflash_3.4

# The compiler to be used.
ifndef CROSS
$(info Please set CROSS compiler, e.g. CROSS=1)
$(error unspecified compiler)
endif

ifeq ($(CROSS), 1)
# Where to find header files that do not live in the source directory.
IPATH=drivers
IPATH+=drivers/inc/
IPATH+=drivers/inc/CMSIS/
IPATH+=drivers/driverlib/MSP432P4xx

INC += -I.
INC += -I..
INC += -I../lib/mp-readline
INC += -I../stmhal
INC += -I$(BUILD)

# Include the common make definitions.
include Makefile.defs
DFU = ../tools/dfu.py
PYDFU = ../tools/pydfu.py
endif
LIBS =

SRC_C = startup_msp432p401r_${COMPILER}.c \
	system_msp432p401r.c \
	main.c \
	board.c \
        msp432_mphal.c \
	modpyb.c \
	led.c	\
	switch.c	\
	lib/utils/printf.c \
	lib/utils/pyexec.c \
	lib/libc/string0.c \
	lib/mp-readline/readline.c \
	$(BUILD)/_frozen_mpy.c	\
		
OBJ = $(PY_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o))

# List of sources for qstr extraction
SRC_QSTR += modpyb.c \
 	    led.c \
            switch.c \

# Append any auto-generated sources that are needed by sources listed in
# SRC_QSTR
SRC_QSTR_AUTO_DEPS +=

#
# The default rule, which causes the firmware to be built.
#
ifeq ($(CROSS), 1)
all: ${BUILD}
all: $(BUILD)/firmware.axf
else
all: $(BUILD)/firmware.elf
endif

# The rule to create the target directory.
#
${BUILD}:
	@mkdir -p ${BUILD}

$(BUILD)/_frozen_mpy.c: frozentest.mpy $(BUILD)/genhdr/qstrdefs.generated.h
	$(ECHO) "MISC freezing bytecode"
	$(Q)../tools/mpy-tool.py -f -q $(BUILD)/genhdr/qstrdefs.preprocessed.h -mlongint-impl=none $< > $@


# Rules for building the examples.
#
${BUILD}/firmware.axf: $(OBJ)
${BUILD}/firmware.axf: ${ROOT}/driverlib/MSP432P4xx/${COMPILER}/msp432p4xx_driverlib.a
${BUILD}/firmware.axf: msp432p401r.ld
SCATTERgcc_firmware=msp432p401r.ld
ENTRY_firmware=resetISR
CFLAGSgcc=-DTARGET_IS_MSP432P4XX

deploy:
	$(ECHO) "Writing $< to the board"
	${UNIFLASH}/./uniflash.sh -ccxml ${UNIFLASH}/msp432_config.ccxml -program ${BUILD}/firmware.axf


# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${BUILD}/*.d} __dummy__
endif

include ../py/mkrules.mk



