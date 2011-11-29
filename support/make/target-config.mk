# TARGET_FLAGS are to be passed while compiling, assembling, linking.

TARGET_FLAGS :=

# Board-specific configuration values.  Flash and SRAM sizes in bytes.

ifeq ($(BOARD), maple)
   MCU := STM32F103RB
   PRODUCT_ID := 0003
   ERROR_LED_PORT := GPIOA
   ERROR_LED_PIN  := 5
   DENSITY := STM32_MEDIUM_DENSITY
   TARGET_FLAGS += -D$(DENSITY)
endif

ifeq ($(BOARD), maple_native)
   MCU := STM32F103ZE
   PRODUCT_ID := 0003
   ERROR_LED_PORT := GPIOC
   ERROR_LED_PIN  := 15
   DENSITY := STM32_HIGH_DENSITY
   TARGET_FLAGS += -D$(DENSITY)
endif

ifeq ($(BOARD), maple_mini)
   MCU := STM32F103CB
   PRODUCT_ID := 0003
   ERROR_LED_PORT := GPIOB
   ERROR_LED_PIN  := 1
   DENSITY := STM32_MEDIUM_DENSITY
   TARGET_FLAGS += -D$(DENSITY)
endif

ifeq ($(BOARD), maple_RET6)
   MCU := STM32F103RE
   PRODUCT_ID := 0003
   ERROR_LED_PORT := GPIOA
   ERROR_LED_PIN := 5
   DENSITY := STM32_HIGH_DENSITY
   TARGET_FLAGS += -D$(DENSITY)
endif

ifeq ($(BOARD), olimex_stm32_h103)
   MCU := STM32F103RB
   PRODUCT_ID := 0003
   ERROR_LED_PORT := GPIOC
   ERROR_LED_PIN := 12
   DENSITY := STM32_MEDIUM_DENSITY
   TARGET_FLAGS += -D$(DENSITY)
endif

TARGET_FLAGS += -DBOARD_$(BOARD) -DMCU_$(MCU) \
                -DERROR_LED_PORT=$(ERROR_LED_PORT) \
                -DERROR_LED_PIN=$(ERROR_LED_PIN)

# STM32 series-specific configuration values.

# NB: these only work for STM32F1 performance line chips, but those
# are the only ones we support at this time.  If you add support for
# STM32F1 connectivity line MCUs or other STM32 families, this section
# will need to change.
LD_SERIES_PATH := $(LDDIR)/stm32/series/f1/performance
LIBMAPLE_MODULE_SERIES := $(LIBMAPLE_PATH)/stm32f1

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
