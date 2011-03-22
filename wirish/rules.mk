# Standard things
sp              := $(sp).x
dirstack_$(sp)  := $(d)
d               := $(dir)
BUILDDIRS       += $(BUILD_PATH)/$(d)
BUILDDIRS       += $(BUILD_PATH)/$(d)/comm

WIRISH_INCLUDES := -I$(d) -I$(d)/comm

# Local flags
CFLAGS_$(d) := $(WIRISH_INCLUDES) $(LIBMAPLE_INCLUDES)

# Local rules and targets
cSRCS_$(d) :=  

cppSRCS_$(d) := wirish_math.cpp		 \
                Print.cpp		 \
                comm/HardwareSerial.cpp	 \
                comm/HardwareSPI.cpp	 \
                usb_serial.cpp		 \
                cxxabi-compat.cpp	 \
		wirish.cpp		 \
		wirish_shift.cpp	 \
		wirish_analog.cpp	 \
		time.cpp		 \
		pwm.cpp 		 \
		ext_interrupts.cpp	 \
		wirish_digital.cpp	 \
		native_sram.cpp		 \
		boards.cpp

cFILES_$(d) := $(cSRCS_$(d):%=$(d)/%)
cppFILES_$(d) := $(cppSRCS_$(d):%=$(d)/%)

OBJS_$(d)     := $(cFILES_$(d):%.c=$(BUILD_PATH)/%.o) \
                 $(cppFILES_$(d):%.cpp=$(BUILD_PATH)/%.o)
DEPS_$(d)     := $(OBJS_$(d):%.o=%.d)

$(OBJS_$(d)): TGT_CFLAGS := $(CFLAGS_$(d))

TGT_BIN += $(OBJS_$(d))

# Standard things
-include        $(DEPS_$(d))
d               := $(dirstack_$(sp))
sp              := $(basename $(sp))
