# STM32F072RB Bare Metal LED Blink Makefile

# Toolchain
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# Target name
TARGET = blink

# Source files
SRCS = main.c startup.c

# Object files
OBJS = $(SRCS:.c=.o)

# Linker script
LDSCRIPT = stm32f072rb.ld

# Compiler flags
CFLAGS = -mcpu=cortex-m0 -mthumb
CFLAGS += -Wall -Wextra
CFLAGS += -O2
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -std=c99

# Linker flags
LDFLAGS = -mcpu=cortex-m0 -mthumb
LDFLAGS += -T$(LDSCRIPT)
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -nostdlib

# Default target
all: $(TARGET).bin $(TARGET).hex

# Link
$(TARGET).elf: $(OBJS) $(LDSCRIPT)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)
	$(SIZE) $@

# Create binary file
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Create hex file
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).bin $(TARGET).hex

# Flash using st-flash (from stlink-tools)
flash: $(TARGET).bin
	st-flash write $(TARGET).bin 0x8000000

# Flash using OpenOCD
flash-openocd: $(TARGET).bin
	openocd -f interface/stlink.cfg -f target/stm32f0x.cfg -c "program $(TARGET).bin 0x08000000 verify reset exit"

# Phony targets
.PHONY: all clean flash flash-openocd
