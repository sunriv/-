CROSS = aarch64-none-elf-
CC = $(CROSS)gcc
AS = $(CROSS)as
LD = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy

CFLAGS = -Wall -nostdlib -nostartfiles -ffreestanding -I./core -I./hal
# Add -g for debugging symbols
CFLAGS += -g

# Source files
CORE_SRCS = $(wildcard core/*.c)
HAL_SRCS_C = $(wildcard hal/*.c)
# Explicitly list assembly files to ensure they are included.
HAL_SRCS_S = hal/start.S hal/context.S 
# Select only one user file to build to avoid multiple definitions.
USER_SRCS = user/work.c

# Object files
OBJS = $(CORE_SRCS:.c=.o)
OBJS += $(HAL_SRCS_C:.c=.o)
OBJS += $(HAL_SRCS_S:.S=.o)
OBJS += $(USER_SRCS:.c=.o)

# Output binary name
TARGET = kernel8.img
ELF_TARGET = eos.elf

.PHONY: all clean

all: $(TARGET)

$(ELF_TARGET): $(OBJS)
	$(LD) -T hal/linker.ld -o $(ELF_TARGET) $(OBJS)

$(TARGET): $(ELF_TARGET)
	$(OBJCOPY) -O binary $(ELF_TARGET) $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(AS) -g -o $@ $<

clean:
	rm -f $(TARGET) $(ELF_TARGET) core/*.o hal/*.o user/*.o
