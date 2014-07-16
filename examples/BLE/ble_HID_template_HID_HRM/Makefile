### Get the current directory
CURRENT_DIR       = $(shell basename $(CURDIR))

### PROJECT_DIR
PROJECT_DIR       = $(CURRENT_DIR)

### ARDMK_DIR
### Path to the Arduino-Makefile directory. 
### Change this depending on where you have saved the main makefile
ARDMK_DIR     =/cygdrive/c/Users/emga/Arduino-Makefile

### ARDUINO_DIR
### Path to the Arduino application and resources directory.
### Change this variable as it depends where the make file is located
ARDUINO_DIR   =../../../../../Arduino

### USER_LIB_PATH
### Path to where the your project's libraries are stored.
#USER_LIB_PATH     :=  $(PROJECT_DIR)/lib

### BOARD_TAG
### It must be set to the board you are currently using. (i.e uno, mega2560, etc.)
BOARD_TAG         = uno

### MONITOR_BAUDRATE
### It must be set to Serial baudrate value you are using.
MONITOR_BAUDRATE  = 115200

### ARDUINO_LIBS
### Libraries used on the BLE project
ARDUINO_LIBS = SPI BLE EEPROM

### MONITOR_PORT
### The port to which the Arduino is connected
MONITOR_PORT = com7

### CPPFLAGS
### Flags you might want to set for debugging purpose. Comment to stop.
#CPPFLAGS         = -pedantic -Wall -Wextra   DEFINED ON THE MAKE FILE

### OBJDIR
### This is were you put the binaries you just compile using 'make'
#OBJDIR            = $(PROJECT_DIR)/bin/$(BOARD_TAG)/$(CURRENT_DIR) DEFINED ON THE MAKEFILE

### path to Arduino.mk, inside the ARDMK_DIR
include $(ARDMK_DIR)/Arduino.mk


