# Top level Makefile for libmaple

# The main library
lib_LIBRARIES = \
	libmaple.a \
	libmapleusb.a \
	libwirish.a

noinst_PROGRAMS = \
	main

main_SOURCES = \
	startup2.c \
	main.cpp

X = $(srcdir)/support/ld/maple_native

main_LDFLAGS = \
	--gc-sections \
	-Map=main.map

main_LDADD = libmaple.a

# Main library
libmaple_a_SOURCES = \
	libmaple/adc.c \
	libmaple/dac.c \
	libmaple/exc.c \
	libmaple/exti.c \
	libmaple/flash.c \
	libmaple/fsmc.c \
	libmaple/gpio.c \
	libmaple/nvic.c \
	libmaple/rcc.c \
	libmaple/spi.c \
	libmaple/systick.c \
	libmaple/timers.c \
	libmaple/usart.c \
	libmaple/util.c

nobase_include_HEADERS = \
	libmaple/adc.h \
	libmaple/dac.h \
	libmaple/exti.h \
	libmaple/flash.h \
	libmaple/fsmc.h \
	libmaple/gpio.h \
	libmaple/libmaple.h \
	libmaple/libmaple_types.h \
	libmaple/nvic.h \
	libmaple/rcc.h \
	libmaple/ring_buffer.h \
	libmaple/spi.h \
	libmaple/systick.h \
	libmaple/timers.h \
	libmaple/usart.h \
	libmaple/util.h \
	libmaple/usb/descriptors.h \
	libmaple/usb/usb.h \
	libmaple/usb/usb_callbacks.h \
	libmaple/usb/usb_config.h \
	libmaple/usb/usb_hardware.h \
	libmaple/usb/usb_lib/usb_core.h \
	libmaple/usb/usb_lib/usb_def.h \
	libmaple/usb/usb_lib/usb_init.h \
	libmaple/usb/usb_lib/usb_int.h \
	libmaple/usb/usb_lib/usb_lib.h \
	libmaple/usb/usb_lib/usb_mem.h \
	libmaple/usb/usb_lib/usb_regs.h \
	libmaple/usb/usb_lib/usb_type.h

libmapleusb_a_SOURCES = \
	libmaple/usb/descriptors.c \
	libmaple/usb/usb.c \
	libmaple/usb/usb_callbacks.c \
	libmaple/usb/usb_hardware.c \
	libmaple/usb/usb_lib/usb_core.c \
	libmaple/usb/usb_lib/usb_init.c \
	libmaple/usb/usb_lib/usb_int.c \
	libmaple/usb/usb_lib/usb_mem.c \
	libmaple/usb/usb_lib/usb_regs.c

libwirish_a_SOURCES = \
	wirish/HardwareTimer.cpp \
	wirish/Print.cpp \
	wirish/comm/HardwareSPI.cpp \
	wirish/comm/HardwareSerial.cpp \
	wirish/cxxabi-compat.cpp \
	wirish/ext_interrupts.c \
	wirish/pwm.c \
	wirish/time.c \
	wirish/usb_serial.cpp \
	wirish/wirish.c \
	wirish/wirish_analog.c \
	wirish/wirish_digital.c \
	wirish/wirish_math.cpp \
	wirish/wirish_shift.c

MCU := STM32F103RB
BOARD ?= maple_native

FLAGS = \
	-Os -g -nostdlib -Wall \
	-ffunction-sections -fdata-sections -Wl,--gc-sections \
	-mcpu=cortex-m3 -mthumb -fshort-enums -mfloat-abi=soft \
	-DBOARD_$(BOARD) -DMCU_$(MCU) -DVECT_TAB_BASE \
	-I$(srcdir)/libmaple \
	-I$(srcdir)/libmaple/usb \
	-I$(srcdir)/libmaple/usb/usb_lib

AM_CFLAGS = $(FLAGS) -std=gnu99

AM_CXXFLAGS = $(FLAGS) \
	-I$(srcdir)/wirish -I$(srcdir)/wirish/comm \
	-fno-rtti -fno-exceptions
