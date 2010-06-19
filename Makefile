# dumb dumb dumb makefile
# Project name
PROJECT=maple

# ARM/GNU toolchain parameters
CC  := arm-none-eabi-gcc
CPP := arm-none-eabi-g++
LD  := arm-none-eabi-ld -v
AR  := arm-none-eabi-ar
AS  := arm-none-eabi-as
CP  := arm-none-eabi-objcopy
OD  := arm-none-eabi-objdump

# Platform detection
ARCH = $(shell uname -m)
OS = $(shell uname)

VENDOR_ID =  1EAF
PRODUCT_ID = 0003

# Modify this if necessary
DFU = dfu-util

BUILD_PATH = build
LIB_PATH   = libmaple

OUTDIRS    = $(BUILD_PATH)/$(LIB_PATH)         \
	     $(BUILD_PATH)/wirish              \
	     $(BUILD_PATH)/wirish/comm         \
	     $(BUILD_PATH)/$(LIB_PATH)/usb     \
	     $(BUILD_PATH)/$(LIB_PATH)/usb/usb_lib



INCLUDES   = -I$(LIB_PATH)                     \
	     -I./  			       \
	     -Iwirish                          \
	     -Iwirish/comm                     \
	     -I$(LIB_PATH)/usb                 \
	     -I$(LIB_PATH)/usb/usb_lib

CFLAGS     = $(INCLUDES) -c                    \
             -Os                               \
             -g -mcpu=cortex-m3 -mthumb  -march=armv7-m -nostdlib \
             -ffunction-sections -fdata-sections -Wl,--gc-sections \
	     -D$(DEFFLAGS)

CXXFLAGS = -fno-rtti -fno-exceptions -Wall

LDDIR=support/ld
LFLAGS  = -T$(LDDIR)/$(LDSCRIPT) -L$(LDDIR)    \
          -mcpu=cortex-m3 -mthumb -Xlinker     \
          --gc-sections --print-gc-sections --march=armv7-m -Wall

CPFLAGS = -v -Obinary
ODFLAGS = -S

CSRC = libmaple/systick.c                \
       libmaple/timers.c                 \
       libmaple/adc.c 	                 \
       libmaple/syscalls.c 	         \
       libmaple/exc.c                    \
       libmaple/exti.c 	                 \
       libmaple/gpio.c 	                 \
       libmaple/nvic.c 	                 \
       libmaple/usart.c 	         \
       libmaple/util.c	                 \
       libmaple/rcc.c                    \
       libmaple/flash.c                  \
       libmaple/spi.c                    \
       wirish/wirish.c 	                 \
       wirish/wirish_shift.c             \
       wirish/wirish_analog.c            \
       wirish/time.c 		         \
       wirish/pwm.c 		         \
       wirish/ext_interrupts.c           \
       wirish/wirish_digital.c           \
       libmaple/usb/usb.c		 \
       libmaple/usb/usb_callbacks.c      \
       libmaple/usb/usb_hardware.c       \
       libmaple/usb/descriptors.c        \
       libmaple/usb/usb_lib/usb_core.c   \
       libmaple/usb/usb_lib/usb_init.c   \
       libmaple/usb/usb_lib/usb_int.c    \
       libmaple/usb/usb_lib/usb_mem.c    \
       libmaple/usb/usb_lib/usb_regs.c   \

CPPSRC = wirish/wirish_math.cpp          \
	 wirish/Print.cpp 		 \
	 wirish/comm/HardwareSerial.cpp  \
	 wirish/comm/HardwareSPI.cpp 	 \
	 wirish/usb_serial.cpp 	         \
	 wirish/cxxabi-compat.cpp 	 \
   	 main.cpp

# i really have no idea what i'm doing
meep += $(CSRC)
moop = $(patsubst %, %, $(meep))
beep = $(CPPSRC)
boop = $(patsubst %, %, $(beep))

# English
MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = -------- begin --------
MSG_ETAGS = Created TAGS File
MSG_END = --------  end  --------
MSG_SIZE = Program Image Size:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling C:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:
MSG_FLASH = Creating load file for Flash:


_COBJ =  $(moop:.c=.o)
_CPPOBJ =  $(boop:.cpp=.o)
COBJ = $(patsubst %, $(BUILD_PATH)/%,$(_COBJ))
CPPOBJ = $(patsubst %, $(BUILD_PATH)/%,$(_CPPOBJ))

.PHONY: run cscope clean info program_ram program_flash program_jtag

info:
	@echo ""
	@echo "libmaple Makefile help"
	@echo "----------------------"
	@echo "Compile targets:"
	@echo "  ram:    Compile sketch code for RAM to be loaded over the bootloader"
	@echo "  flash:  Compile sketch code for flash to be loaded over the bootloader"
	@echo "  jtag:   Compile sketch code for flash to be loaded over JTAG"
	@echo ""
	@echo "Programming targets:"
	@echo "  program_ram:   Upload code to RAM via bootloader"
	@echo "  program_flash: Upload code to flash via bootloader"
	@echo "  program_jtag:  Upload code to flash via jtag"

all: info

tags:
	etags `find . -name "*.c" -o -name "*.cpp" -o -name "*.h"`
	@echo "Made TAGS file for EMACS code browsing"

ctags:
	ctags-exuberant -R .
	@echo "Made tags file for VIM code browsing"

$(BUILD_PATH):
	mkdir -p build

$(OUTDIRS):
	@echo Making directory $@
	mkdir -p $@
	@echo

# actual build rules
$(COBJ) : $(BUILD_PATH)/%.o : %.c
	@echo $(MSG_COMPILING) $<
	$(CC) $(CFLAGS) -c $< -o $@
	@echo

$(CPPOBJ) : $(BUILD_PATH)/%.o : %.cpp
	@echo $(MSG_COMPILING) $<
	$(CPP) $(CFLAGS) $(CXXFLAGS) -c $< -o $@
	@echo

# targets
$(BUILD_PATH)/$(PROJECT).out: $(OUTDIRS) $(COBJ) $(CPPOBJ)
	@echo Linking
	@echo CPP OBJ: $(CPPOBJ)
	@echo
	@echo C OBJ: $(COBJ)
	@echo
	$(CC) $(LFLAGS) -o $(BUILD_PATH)/$(PROJECT).out $(COBJ) $(CPPOBJ)
	@echo

$(BUILD_PATH)/main.bin: $(BUILD_PATH)/$(PROJECT).out
	$(CP) $(CPFLAGS) $(BUILD_PATH)/$(PROJECT).out $(BUILD_PATH)/main.bin
	$(OD) $(ODFLAGS) $(BUILD_PATH)/$(PROJECT).out > $(BUILD_PATH)/$(PROJECT).d
	@echo
	find $(BUILD_PATH) -iname *.o | xargs arm-none-eabi-size -t
	@echo
	@echo "Final Size:"
	arm-none-eabi-size $<

ram: DEFFLAGS := VECT_TAB_RAM
ram: LDSCRIPT := ram.ld
ram: $(BUILD_PATH)/main.bin
	@echo "RAM build"

flash: DEFFLAGS := VECT_TAB_FLASH
flash: LDSCRIPT := flash.ld
flash: $(BUILD_PATH)/main.bin
	@echo "Flash build"

jtag: DEFFLAGS := VECT_TAB_BASE
jtag: LDSCRIPT := jtag.ld
jtag: $(BUILD_PATH)/main.bin
	@echo "JTAG build"

program_ram: ram 
	support/scripts/reset.py
	sleep 1
	$(DFU) -a0 -d $(VENDOR_ID):$(PRODUCT_ID) -D build/main.bin -R

program_flash: flash
	support/scripts/reset.py
	sleep 1
	$(DFU) -a1 -d $(VENDOR_ID):$(PRODUCT_ID) -D build/main.bin -R

program_jtag: jtag
	openocd -f support/openocd/flash.cfg


run: $(BUILD_PATH)/main.bin
	openocd -f support/openocd/run.cfg

cscope:
	rm -rf *.cscope
	find . -name '*.[hcs]' -o -name '*.cpp' | xargs cscope -b

clean:
	rm -f *.hex *.o
	rm -rf build

