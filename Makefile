.DEFAULT_GOAL := sketch

BOARD ?= maple
MAPLE_TARGET ?= flash

# Useful paths
SRCROOT := $(dir)
BUILD_PATH = build
LIBMAPLE_PATH := libmaple

# Useful variables
GLOBAL_CFLAGS    = -Os -g -mcpu=cortex-m3 -mthumb -march=armv7-m -nostdlib \
                   -ffunction-sections -fdata-sections -Wl,--gc-sections

GLOBAL_CXXFLAGS := -fno-rtti -fno-exceptions -Wall


LDDIR    := support/ld
LDFLAGS  = -T$(LDDIR)/$(LDSCRIPT) -L$(LDDIR)    \
            -mcpu=cortex-m3 -mthumb -Xlinker     \
            --gc-sections --print-gc-sections --march=armv7-m -Wall

# Set up build rules and some useful templates
include support/make/build-rules.mk
include support/make/build-templates.mk

VENDOR_ID =  1EAF
PRODUCT_ID = 0003

# Force a rebuild if the maple target changed
PREV_BUILD_TYPE := $(shell cat $(BUILD_PATH)/build-type 2>/dev/null)
ifneq ($(PREV_BUILD_TYPE), $(MAPLE_TARGET))
   $(shell rm -rf $(BUILD_PATH))
endif

# Some target specific things
ifeq ($(MAPLE_TARGET), ram)
   VECT_BASE_ADDR := VECT_TAB_RAM
   LDSCRIPT := ram.ld
   UPLOAD := support/scripts/reset.py && \
	     sleep 1                  && \
	     $(DFU) -a0 -d $(VENDOR_ID):$(PRODUCT_ID) -D $(BUILD_PATH)/$(BOARD).bin -R

endif
ifeq ($(MAPLE_TARGET), flash)
   LDSCRIPT := flash.ld
   VECT_BASE_ADDR := VECT_TAB_FLASH
   UPLOAD := support/scripts/reset.py && \
	     sleep 1                  && \
	     $(DFU) -a1 -d $(VENDOR_ID):$(PRODUCT_ID) -D $(BUILD_PATH)/$(BOARD).bin -R
endif
ifeq ($(MAPLE_TARGET), jtag)
   LDSCRIPT := jtag.ld
   VECT_BASE_ADDR := VECT_TAB_BASE
   UPLOAD := \
      openocd -f support/openocd/flash.cfg
endif

# Set all submodules here
LIBMAPLE_MODULES := libmaple
LIBMAPLE_MODULES += wirish

# call each module rules.mk
$(foreach m,$(LIBMAPLE_MODULES),$(eval $(call LIBMAPLE_MODULE_template,$(m))))

# Main target
include support/make/build-targets.mk

# Fake targets
POSSIBLE_TARGETS := install sketch clean help debug cscope tags ctags ram flash jtag
.PHONY: $(POSSIBLE_TARGETS)

install: sketch
	$(UPLOAD)

sketch: MSG_INFO $(BUILD_PATH)/$(BOARD).bin

clean:
	rm -rf build

help:
	@echo ""
	@echo "  libmaple Makefile help"
	@echo "  ----------------------"
	@echo "  Compile targets:"
	@echo "      sketch:   Compile sketch code"
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
	@env - MAPLE_TARGET=ram
	@echo "Memory target set to RAM for this session"

flash:
	@env - MAPLE_TARGET=flash
	@echo "Memory target set to FLASH for this session"

jtag:
	@env - MAPLE_TARGET=jtag
	@echo "Memory target set to JTAG for this session"
