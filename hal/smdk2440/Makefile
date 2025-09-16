include $(MAKERULE)

export TOOLCHAIN_ROOT := /home/wsyoo/crosstool/arm-softfloat-linux-gnu/gcc-3.3.2-glibc-2.3.2
export GCC_PREFIX := $(TOOLCHAIN_ROOT)/bin/arm-softfloat-linux-gnu-
export TOOLCHAIN_LIB := $(TOOLCHAIN_ROOT)/lib/gcc-lib/arm-softfloat-linux-gnu/3.3.2

clean: clean_
	rm -f $(TOP_DIR)/eos
	rm -f $(TOP_DIR)/eos.bin

eos: $(subdir_targets)
	$(LD) -o eos --start-group $(subdir_libs) core/module.a -Ttext 0x30000000 -T hal/$(HAL)/ldscript -L $(TOOLCHAIN_LIB) -lgcc --end-group -Map eos.map
	$(GCC_PREFIX)objcopy -O binary eos eos.bin
	@echo
	@echo Building EOS is complete. Type ./eos to run EOS.
