# Standard things
sp              := $(sp).x
dirstack_$(sp)  := $(d)
d               := $(dir)
BUILDDIRS       += $(BUILD_PATH)/$(d)
BUILDDIRS       += $(BUILD_PATH)/$(d)/comm
BUILDDIRS       += $(BUILD_PATH)/$(d)/boards

WIRISH_INCLUDES := -I$(d) -I$(d)/comm -I$(d)/boards

# Local flags
CFLAGS_$(d) := $(WIRISH_INCLUDES) $(LIBMAPLE_INCLUDES)

# Local rules and targets

sSRCS_$(d) := start.S
cSRCS_$(d) := start_c.c
cppSRCS_$(d) := wirish_math.cpp		 \
                Print.cpp		 \
		boards.cpp               \
                boards/maple.cpp	 \
                boards/maple_mini.cpp	 \
                boards/maple_native.cpp	 \
                boards/maple_RET6.cpp	 \
                boards/olimex_stm32_h103.cpp \
                comm/HardwareSerial.cpp	 \
                comm/HardwareSPI.cpp	 \
		HardwareTimer.cpp	 \
                usb_serial.cpp		 \
                cxxabi-compat.cpp	 \
		wirish_shift.cpp	 \
		wirish_analog.cpp	 \
		wirish_time.cpp		 \
		pwm.cpp 		 \
		ext_interrupts.cpp	 \
		wirish_digital.cpp

sFILES_$(d)   := $(sSRCS_$(d):%=$(d)/%)
cFILES_$(d)   := $(cSRCS_$(d):%=$(d)/%)
cppFILES_$(d) := $(cppSRCS_$(d):%=$(d)/%)

OBJS_$(d)     := $(sFILES_$(d):%.S=$(BUILD_PATH)/%.o) \
                 $(cFILES_$(d):%.c=$(BUILD_PATH)/%.o) \
                 $(cppFILES_$(d):%.cpp=$(BUILD_PATH)/%.o)
DEPS_$(d)     := $(OBJS_$(d):%.o=%.d)

$(OBJS_$(d)): TGT_CFLAGS := $(CFLAGS_$(d))

TGT_BIN += $(OBJS_$(d))

# Standard things
-include        $(DEPS_$(d))
d               := $(dirstack_$(sp))
sp              := $(basename $(sp))
