# Standard things
sp              := $(sp).x
dirstack_$(sp)  := $(d)
d               := $(dir)
BUILDDIRS       += $(BUILD_PATH)/$(d)
BUILDDIRS       += $(BUILD_PATH)/$(d)/usb_lib

# Local flags
CFLAGS_$(d) = -I$(d) -I$(d)/usb_lib $(LIBMAPLE_INCLUDES) -Wall

# Local rules and targets
sSRCS_$(d) :=
cSRCS_$(d) := usb.c                \
              usb_reg_map.c        \
              usb_cdcacm.c         \
              usb_lib/usb_core.c   \
              usb_lib/usb_init.c   \
              usb_lib/usb_mem.c    \
              usb_lib/usb_regs.c

sFILES_$(d) := $(sSRCS_$(d):%=$(d)/%)
cFILES_$(d) := $(cSRCS_$(d):%=$(d)/%)

OBJS_$(d) := $(sFILES_$(d):%.S=$(BUILD_PATH)/%.o) \
             $(cFILES_$(d):%.c=$(BUILD_PATH)/%.o)
DEPS_$(d) := $(OBJS_$(d):%.o=%.d)

$(OBJS_$(d)): TGT_CFLAGS := $(CFLAGS_$(d))
$(OBJS_$(d)): TGT_ASFLAGS :=

TGT_BIN += $(OBJS_$(d))

# Standard things
-include        $(DEPS_$(d))
d               := $(dirstack_$(sp))
sp              := $(basename $(sp))
