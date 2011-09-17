# Board-specific configuration values.  Flash and SRAM sizes in bytes.

ifeq ($(BOARD), maple)
   MCU := STM32F103RB
   PRODUCT_ID := 0003
   ERROR_LED_PORT := GPIOA
   ERROR_LED_PIN  := 5
   DENSITY := STM32_MEDIUM_DENSITY
   FLASH_SIZE := 131072
   SRAM_SIZE := 20480
endif

ifeq ($(BOARD), maple_native)
   MCU := STM32F103ZE
   PRODUCT_ID := 0003
   ERROR_LED_PORT := GPIOC
   ERROR_LED_PIN  := 15
   DENSITY := STM32_HIGH_DENSITY
   FLASH_SIZE := 524288
   SRAM_SIZE := 65536
endif

ifeq ($(BOARD), maple_mini)
   MCU := STM32F103CB
   PRODUCT_ID := 0003
   ERROR_LED_PORT := GPIOB
   ERROR_LED_PIN  := 1
   DENSITY := STM32_MEDIUM_DENSITY
   FLASH_SIZE := 131072
   SRAM_SIZE := 20480
endif

ifeq ($(BOARD), maple_RET6)
   MCU := STM32F103RE
   PRODUCT_ID := 0003
   ERROR_LED_PORT := GPIOA
   ERROR_LED_PIN := 5
   DENSITY := STM32_HIGH_DENSITY
   FLASH_SIZE := 524288
   SRAM_SIZE := 65536
endif

ifeq ($(BOARD), olimex_stm32_h103)
   MCU := STM32F103RB
   PRODUCT_ID := 0003
   ERROR_LED_PORT := GPIOC
   ERROR_LED_PIN := 12
   DENSITY := STM32_MEDIUM_DENSITY
   FLASH_SIZE := 131072
   SRAM_SIZE := 20480
endif

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
