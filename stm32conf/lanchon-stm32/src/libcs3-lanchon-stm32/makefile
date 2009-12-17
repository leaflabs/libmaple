# setup environment

TARGET_ARCH = -mcpu=cortex-m3 -mthumb

CC = arm-none-eabi-gcc
CFLAGS =

AS = $(CC) -x assembler-with-cpp -c $(TARGET_ARCH)
ASFLAGS =

AR = arm-none-eabi-ar
ARFLAGS = cr


LIB_OUT = libcs3-lanchon-stm32.a

LIB_OBJS = lanchon-stm32-vector.o lanchon_stm32_isr_interrupt.o


# all

.PHONY: all
all: $(LIB_OUT)


# lib

$(LIB_OUT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $(LIB_OBJS)


# clean

.PHONY: clean
clean:
	-rm -f $(LIB_OBJS) $(LIB_OUT)
