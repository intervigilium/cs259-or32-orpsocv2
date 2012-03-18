# Coremark makefile for OpenRISC on Digilent Atlys

coremark_SOURCES= core_list_join.c \
                  core_matrix.c \
                  core_portme.c \
                  core_state.c \
                  core_util.c

ELF_DEPENDS= $(coremark_SOURCES)

# Build using: make core_main.bin
SRC_MAIN= core_main.c

# Set root
SW_ROOT=../..

# Include main makefile
include $(SW_ROOT)/Makefile.inc

ITERATIONS ?= 10
FLAGS_STR ?= \"-nostdlib\"

OR32_CFLAGS+= -DITERATIONS=$(ITERATIONS) -DFLAGS_STR=$(FLAGS_STR)

%.dis: %.elf
	$(Q)$(OR32_OBJDUMP) -d $< > $@

%.bin: %.elf
	$(Q)$(OR32_OBJCOPY) -O binary $< $@

clean:
	$(Q)rm -f *.elf *.bin *.vmem *.flashin *.dis
