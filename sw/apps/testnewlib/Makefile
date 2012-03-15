
testnewlib_SOURCES = testnewlib.c

ELF_DEPENDS= $(coremark_SOURCES)

SW_ROOT=../..

include $(SW_ROOT)/Makefile.inc

# make testnewlib.elf

%.dis: %.elf
	$(Q)$(OR32_OBJDUMP) -d $< > $@

%.bin: %.elf
	$(Q)$(OR32_OBJCOPY) -O binary $< $@

clean:
	$(Q)rm -f *.bin *.vmem *.flashin *.dis
