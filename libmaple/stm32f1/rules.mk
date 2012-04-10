# Standard things
sp              := $(sp).x
dirstack_$(sp)  := $(d)
d               := $(dir)
BUILDDIRS       += $(BUILD_PATH)/$(d)

# Local flags
CFLAGS_$(d) = -I$(d) $(LIBMAPLE_PRIVATE_INCLUDES) $(LIBMAPLE_INCLUDES) -Wall -Werror

# Local rules and targets
sSRCS_$(d) := isrs_performance.S
sSRCS_$(d) += vector_table_performance.S

cSRCS_$(d) := adc.c
cSRCS_$(d) += bkp.c
cSRCS_$(d) += fsmc.c
cSRCS_$(d) += gpio.c
cSRCS_$(d) += rcc.c
cSRCS_$(d) += spi.c
cSRCS_$(d) += timer.c
cSRCS_$(d) += usart.c

sFILES_$(d) := $(sSRCS_$(d):%=$(d)/%)
cFILES_$(d) := $(cSRCS_$(d):%=$(d)/%)

OBJS_$(d) := $(sFILES_$(d):%.S=$(BUILD_PATH)/%.o) \
             $(cFILES_$(d):%.c=$(BUILD_PATH)/%.o)
DEPS_$(d) := $(OBJS_$(d):%.o=%.d)

$(OBJS_$(d)): TGT_ASFLAGS :=
$(OBJS_$(d)): TGT_CFLAGS := $(CFLAGS_$(d))

TGT_BIN += $(OBJS_$(d))

# Standard things
-include        $(DEPS_$(d))
d               := $(dirstack_$(sp))
sp              := $(basename $(sp))
