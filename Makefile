# dumb dumb dumb makefile
# Project name
PROJECT=maple

# STM Library prefix
STM_SRC = stm32lib/src
STM_CONF = stm32conf/flash.conf

# ARM/GNU toolchain parameters
CC  = arm-none-eabi-gcc
CPP = arm-none-eabi-g++
LD  = arm-none-eabi-ld -v
AR  = arm-none-eabi-ar
AS  = arm-none-eabi-as
CP  = arm-none-eabi-objcopy
OD  = arm-none-eabi-objdump

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

CFLAGS  =  -I./ $(INCLUDES) -c \
           -Os\
           -g -mcpu=cortex-m3 -mthumb  -march=armv7-m -nostdlib \
           -ffunction-sections -fdata-sections -Wl,--gc-sections


CPPFLAGS = -fno-rtti -fno-exceptions -Wall

LFLAGS  = -Tstm32conf/lanchon-stm32.ld -L stm32conf/lanchon-stm32 \
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
	   lib/usart.c 			    \
	   wiring/wiring.c 		    \
	   wiring/wiring_shift.c            \
	   wiring/wiring_analog.c           \
	   wiring/time.c 		    \
	   wiring/pwm.c 		    \
	   wiring/ext_interrupts.c          \
	   wiring/wiring_digital.c

CSRC += $(STM32SRCS)

CPPSRC = lib/util.cpp \
	 wiring/math.cpp \
	 wiring/Print.cpp \
	 wiring/comm/Serial.cpp \
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

# output directories
all: $(BUILD_PATH)/main.bin

$(BUILD_PATH):
	mkdir -p build

_COBJ =  $(moop:.c=.o)
_CPPOBJ =  $(boop:.cpp=.o)
COBJ = $(patsubst %, $(BUILD_PATH)/%,$(_COBJ))
CPPOBJ = $(patsubst %, $(BUILD_PATH)/%,$(_CPPOBJ))


.PHONY: test install run cscope clean

test: $(CSRC_)
	@echo help
	@echo $(moop)
	@echo done

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


install: $(BUILD_PATH)/main.bin
	openocd -f stm32conf/flash.cfg

run: $(BUILD_PATH)/main.bin
	openocd -f stm32conf/run.cfg

cscope:
	rm -rf *.cscope
	find . -iname "*.[hcs]" | grep -v examples | xargs cscope -R -b

clean:
	rm -f *.hex *.o
	rm -rf build/*

