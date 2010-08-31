.DEFAULT_GOAL := sketch

BOARD ?= maple
MEMORY_TARGET ?= flash

# USB ID for DFU upload
VENDOR_ID  := 1EAF
PRODUCT_ID := 0003

# Guess the MCU based on the BOARD (can be overridden )
ifeq ($(BOARD), maple)
   MCU := STM32F103RB
   PRODUCT_ID := 0003
endif
ifeq ($(BOARD), maple-native)
   MCU := STM32F103ZE
   PRODUCT_ID := 0003
endif

# Useful paths
SRCROOT := $(dir)
BUILD_PATH = build
LIBMAPLE_PATH := libmaple

# Useful variables
GLOBAL_CFLAGS    := -Os -g -mcpu=cortex-m3 -mthumb -march=armv7-m -nostdlib \
                    -ffunction-sections -fdata-sections -Wl,--gc-sections \
					-DBOARD_$(BOARD) -DMCU_$(MCU)
GLOBAL_CXXFLAGS := -fno-rtti -fno-exceptions -Wall -DBOARD_$(BOARD) -DMCU_$(MCU)


LDDIR    := support/ld
LDFLAGS  = -T$(LDDIR)/$(LDSCRIPT) -L$(LDDIR)    \
            -mcpu=cortex-m3 -mthumb -Xlinker     \
            --gc-sections --print-gc-sections --march=armv7-m -Wall

# Set up build rules and some useful templates
include support/make/build-rules.mk
include support/make/build-templates.mk

# Some target specific things
ifeq ($(MEMORY_TARGET), ram)
   VECT_BASE_ADDR := VECT_TAB_RAM
   LDSCRIPT := ram.ld
endif
ifeq ($(MEMORY_TARGET), flash)
   LDSCRIPT := flash.ld
   VECT_BASE_ADDR := VECT_TAB_FLASH
endif
ifeq ($(MEMORY_TARGET), jtag)
   LDSCRIPT := jtag.ld
   VECT_BASE_ADDR := VECT_TAB_BASE
endif

# Set all submodules here
LIBMAPLE_MODULES := libmaple
LIBMAPLE_MODULES += wirish

# call each module rules.mk
$(foreach m,$(LIBMAPLE_MODULES),$(eval $(call LIBMAPLE_MODULE_template,$(m))))

# Main target
include support/make/build-targets.mk

.PHONY: install sketch clean help debug cscope tags ctags ram flash jtag

# Target upload commands
UPLOAD_ram   := support/scripts/reset.py && \
                sleep 1                  && \
                $(DFU) -a0 -d $(VENDOR_ID):$(PRODUCT_ID) -D $(BUILD_PATH)/$(BOARD).bin -R
UPLOAD_flash := support/scripts/reset.py && \
                sleep 1                  && \
                $(DFU) -a1 -d $(VENDOR_ID):$(PRODUCT_ID) -D $(BUILD_PATH)/$(BOARD).bin -R
UPLOAD_jtag  := $(OPENOCD) -f support/openocd/flash.cfg

# conditionally upload to whatever the last build was
install: INSTALL_TARGET = $(shell cat $(BUILD_PATH)/build-type 2>/dev/null)
install: $(BUILD_PATH)/$(BOARD).bin
	@echo Install target: $(INSTALL_TARGET)
	$(UPLOAD_$(INSTALL_TARGET))

# Force a rebuild if the maple target changed
PREV_BUILD_TYPE = $(shell cat $(BUILD_PATH)/build-type 2>/dev/null)
build-check:
ifneq ($(PREV_BUILD_TYPE), $(MEMORY_TARGET))
	$(shell rm -rf $(BUILD_PATH))
endif

sketch: build-check MSG_INFO $(BUILD_PATH)/$(BOARD).bin

clean:
	rm -rf build

help:
	@echo ""
	@echo "  libmaple Makefile help"
	@echo "  ----------------------"
	@echo "  Compile targets (default MEMORY_TARGET=flash):"
	@echo "      ram:    Compile sketch code to ram"
	@echo "      flash:  Compile sketch code to flash"
	@echo "      jtag:   Compile sketch code to jtag"
	@echo "      sketch: Compile sketch code to target MEMORY_TARGET"
	@echo "  "
	@echo "  Programming targets:"
	@echo "      install:  Upload code to target"
	@echo "  "
	@echo "  Other targets:"
	@echo "      debug:  Start an openocd gdb server, port 3333"
	@echo "      clean: Remove all build and object files"
	@echo "      help: Show this message"
	@echo "  "

debug:
	$(OPENOCD) -f support/openocd/run.cfg

cscope:
	rm -rf *.cscope
	find . -name '*.[hcs]' -o -name '*.cpp' | xargs cscope -b

tags:
	etags `find . -name "*.c" -o -name "*.cpp" -o -name "*.h"`
	@echo "Made TAGS file for EMACS code browsing"

ctags:
	ctags-exuberant -R .
	@echo "Made tags file for VIM code browsing"

ram:
	@$(MAKE) MEMORY_TARGET=ram --no-print-directory sketch

flash:
	@$(MAKE) MEMORY_TARGET=flash --no-print-directory sketch

jtag:
	@$(MAKE) MEMORY_TARGET=jtag --no-print-directory sketch
