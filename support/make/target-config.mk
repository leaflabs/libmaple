# TARGET_FLAGS are to be passed while compiling, assembling, linking.

TARGET_FLAGS :=

# Board-specific configuration values. Punt these to board-specific
# include files.

include $(MAKEDIR)/board-includes/$(BOARD).mk

TARGET_FLAGS += -DBOARD_$(BOARD) -DMCU_$(MCU) \
                -DERROR_LED_PORT=$(ERROR_LED_PORT) \
                -DERROR_LED_PIN=$(ERROR_LED_PIN)

# STM32 series-specific configuration values.

LD_SERIES_PATH := $(LDDIR)/stm32/series/$(MCU_SERIES)
ifeq ($(MCU_SERIES), stm32f1)
   # Hack: force F1 to performance line; this will need to change if
   # you add connectivity etc. line support.
   LD_SERIES_PATH := $(LD_SERIES_PATH)/performance
endif
LIBMAPLE_MODULE_SERIES := $(LIBMAPLE_PATH)/$(MCU_SERIES)

# Memory target-specific configuration values

ifeq ($(MEMORY_TARGET), ram)
   LDSCRIPT := $(BOARD)/ram.ld
   VECT_BASE_ADDR := VECT_TAB_RAM
endif
ifeq ($(MEMORY_TARGET), flash)
   LDSCRIPT := $(BOARD)/flash.ld
   VECT_BASE_ADDR := VECT_TAB_FLASH
endif
ifeq ($(MEMORY_TARGET), jtag)
   LDSCRIPT := $(BOARD)/jtag.ld
   VECT_BASE_ADDR := VECT_TAB_BASE
endif

TARGET_FLAGS += -D$(VECT_BASE_ADDR)
