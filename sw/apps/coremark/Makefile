
coremark_SOURCES = core_list_join.c	\
		   core_main.c		\
		   core_matrix.c	\
		   core_portme.c	\
		   core_state.c		\
		   core_util.c

ELF_DEPENDS= $(coremark_SOURCES)

SW_ROOT=../..

include $(SW_ROOT)/Makefile.inc

# make core_main.elf

#coremark.elf:
#	$(Q)$(OR32_CC) $^ -o $@

%.dis: %.elf
	$(Q)$(OR32_OBJDUMP) -d $< > $@

%.bin: %.elf
	$(Q)$(OR32_OBJCOPY) -O binary $< $@

clean:
	$(Q)rm -f *.bin *.vmem *.flashin *.dis
