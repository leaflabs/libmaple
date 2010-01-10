# dumb dumb dumb makefile
# Project name
PROJECT=maple

# STM Library prefix
STM_SRC = stm32lib/src
STM_CONF = stm32conf/flash.conf

# ARM/GNU toolchain parameters
CC  := arm-none-eabi-gcc
CPP := arm-none-eabi-g++
LD  := arm-none-eabi-ld -v
AR  := arm-none-eabi-ar
AS  := arm-none-eabi-as
CP  := arm-none-eabi-objcopy
OD  := arm-none-eabi-objdump

BUILD_PATH = build
LIB_PATH = lib
COMM_PATH = comm

OUTDIRS = $(BUILD_PATH)/src/$(STM_SRC) \
	  $(BUILD_PATH)/src/$(LIB_PATH)\
	  $(BUILD_PATH)/src/comm \
	  $(BUILD_PATH)/src/wiring \
	  $(BUILD_PATH)/src/wiring/comm


INCLUDES = -Isrc/stm32lib/inc \
	   -Isrc/$(LIB_PATH) \
	   -Isrc/$(COMM_PATH) \
	   -Isrc/ \
	   -Isrc/wiring \
	   -Isrc/wiring/comm

# default is to upload to flash
#DEFFLAGS = VECT_TAB_BASE
CFLAGS  =  -I./ $(INCLUDES) -c \
           -Os\
           -g -mcpu=cortex-m3 -mthumb  -march=armv7-m -nostdlib \
           -ffunction-sections -fdata-sections -Wl,--gc-sections \
	   -D$(DEFFLAGS)

CPPFLAGS = -fno-rtti -fno-exceptions -Wall

#LINKER=lanchon-stm32.ld
LFLAGS  = -Tstm32conf/$(LINKER) -L stm32conf/lanchon-stm32 \
          -mcpu=cortex-m3 -mthumb -Xlinker \
          --gc-sections --print-gc-sections --march=armv7-m -Wall

CPFLAGS = -v -Obinary
ODFLAGS = -S

# main ource file
MAIN=main.c

STM32SRCS = $(STM_SRC)/stm32f10x_flash.c    \
	    $(STM_SRC)/stm32f10x_nvic.c     \
	    $(STM_SRC)/stm32f10x_rcc.c

CSRC = lib/systick.c                        \
	   lib/timers.c                     \
	   lib/adc.c 		            \
	   lib/syscalls.c 		    \
	   lib/stm32f10x_it.c 		    \
	   lib/exti.c 			    \
	   lib/gpio.c 			    \
	   lib/nvic.c 			    \
	   lib/usart.c 			    \
	   lib/util.c			    \
	   lib/usb.c                        \
	   wiring/wiring.c 		    \
	   wiring/wiring_shift.c            \
	   wiring/wiring_analog.c           \
	   wiring/time.c 		    \
	   wiring/pwm.c 		    \
	   wiring/ext_interrupts.c          \
	   wiring/wiring_digital.c

CSRC += $(STM32SRCS)

CPPSRC = wiring/wiring_math.cpp \
	 wiring/Print.cpp \
	 wiring/comm/HardwareSerial.cpp \
	 wiring/comm/HardwareUsb.cpp \
	 main.cpp

# i really have no idea what i'm doing
meep += $(CSRC)
moop = $(patsubst %, src/%, $(meep))
beep = $(CPPSRC)
boop = $(patsubst %, src/%, $(beep))

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

.PHONY: run cscope clean info


info:
	@echo "Maple library help"
	@echo "------------------:"
	@echo "Compile targets:"
	@echo "	   ram:   Compile sketch code for RAM to be loaded over the bootloader"
	@echo "	   flash: Compile sketch code for flash to be loaded over the bootloader"
	@echo "	   jtag:  Compile sketch code for flash to be loaded over JTAG"
	@echo ""
	@echo "Programming targets:"
	@echo "	   program_ram:   Upload code to RAM via bootloader"
	@echo "	   program_flash: Upload code to flash via bootloader"
	@echo "	   program_jtag:  Upload code to flash via jtag"

all: info

$(BUILD_PATH):
	mkdir -p build

$(OUTDIRS):
	@echo Making directory $@
	mkdir -p $@
	@echo

# actual build rules
$(COBJ) : $(BUILD_PATH)/%.o : %.c
	@echo $(MSG_COMPILING) $<
	@echo $(PATH)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo

$(CPPOBJ) : $(BUILD_PATH)/%.o : %.cpp
	@echo $(MSG_COMPILING) $<
	@echo $(PATH)
	$(CPP) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
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
ram: LINKER := lanchon-stm32-user-ram.ld
ram: $(BUILD_PATH)/main.bin
	@echo "RAM build"

flash: DEFFLAGS := VECT_TAB_ROM
flash: LINKER := lanchon-stm32-user-rom.ld
flash: $(BUILD_PATH)/main.bin
	@echo "Flash build"

jtag: DEFFLAGS := VECT_TAB_BASE
jtag: LINKER := lanchon-stm32.ld
jtag: $(BUILD_PATH)/main.bin
	@echo "JTAG build"

program_ram: ram 
	dfu-util -a0 -d 0110:1001 -D build/main.bin -R

program_flash: flash
	dfu-util -a1 -d 0110:1001 -D build/main.bin -R

program_jtag: jtag
	openocd -f stm32conf/flash.cfg


run: $(BUILD_PATH)/main.bin
	openocd -f stm32conf/run.cfg

cscope:
	rm -rf *.cscope
	find . -iname "*.[hcs]" | grep -v examples | xargs cscope -R -b

clean:
	rm -f *.hex *.o
	rm -rf build

