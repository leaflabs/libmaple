# Standard things
sp              := $(sp).x
dirstack_$(sp)  := $(d)
d               := $(dir)
BUILDDIRS       += $(BUILD_PATH)/$(d)

# Add board directory and MCU-specific directory to BUILDDIRS. These
# are in subdirectories, but they're logically part of the Wirish
# submodule.
WIRISH_BOARD_PATH := boards/$(BOARD)
BUILDDIRS += $(BUILD_PATH)/$(d)/$(WIRISH_BOARD_PATH)
BUILDDIRS += $(BUILD_PATH)/$(d)/$(MCU_SERIES)

# Safe includes for Wirish.
WIRISH_INCLUDES := -I$(d)/include -I$(d)/$(WIRISH_BOARD_PATH)/include

# Local flags. Add -I$(d) to allow for private includes.
CFLAGS_$(d) := $(LIBMAPLE_INCLUDES) $(WIRISH_INCLUDES) -I$(d)

# Local rules and targets
sSRCS_$(d) := start.S
cSRCS_$(d) := start_c.c
cppSRCS_$(d) := boards.cpp
# TODO: test these on F2 and put them back in:
# cppSRCS_$(d) := wirish_math.cpp		 \
#                 Print.cpp		 \
#                 HardwareSerial.cpp	 \
#                 HardwareSPI.cpp		 \
# 		HardwareTimer.cpp	 \
#                 usb_serial.cpp		 \
#                 cxxabi-compat.cpp	 \
# 		wirish_shift.cpp	 \
# 		wirish_analog.cpp	 \
# 		wirish_time.cpp		 \
# 		pwm.cpp 		 \
# 		ext_interrupts.cpp	 \
# 		wirish_digital.cpp
# TODO: Put this back in once we've got the necessary libmaple support back.
# cppSRCS_$(d) += $(WIRISH_BOARD_PATH)/board.cpp
cppSRCS_$(d) += $(MCU_SERIES)/boards_setup.cpp

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
