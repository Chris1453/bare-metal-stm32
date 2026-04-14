TARGET   = firmware
MCU      = cortex-m4
FPU      = -mfpu=fpv4-sp-d16 -mfloat-abi=hard
DEFS     = -DSTM32F411xE

TOOLCHAIN = arm-none-eabi
CC       = $(TOOLCHAIN)-gcc
AS       = $(TOOLCHAIN)-gcc -x assembler-with-cpp
OBJCOPY  = $(TOOLCHAIN)-objcopy
SIZE     = $(TOOLCHAIN)-size

OPENOCD  = openocd
OCD_CFG  = -f interface/stlink.cfg -f target/stm32f4x.cfg

SRC_DIR     = src
STARTUP_DIR = startup
LINKER_DIR  = linker
BUILD_DIR   = build
CMSIS_DIR   = ../cmsis

SRCS = $(wildcard $(SRC_DIR)/*.c)
ASMS = $(wildcard $(STARTUP_DIR)/*.s)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o) \
       $(ASMS:$(STARTUP_DIR)/%.s=$(BUILD_DIR)/%.o)

CFLAGS  = -mcpu=$(MCU) -mthumb $(FPU) $(DEFS) \
          -I$(CMSIS_DIR) \
          -O0 -g -Wall -fdata-sections -ffunction-sections
ASFLAGS = -mcpu=$(MCU) -mthumb $(FPU) $(DEFS) \
          -g -Wall
LDFLAGS = -mcpu=$(MCU) -mthumb $(FPU) \
          -T$(LINKER_DIR)/stm32f411re.ld \
          -Wl,--gc-sections \
          -Wl,-Map=$(BUILD_DIR)/$(TARGET).map \
          --specs=nosys.specs

.PHONY: all flash clean

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
	$(SIZE) $(BUILD_DIR)/$(TARGET).elf

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(STARTUP_DIR)/%.s | $(BUILD_DIR)
	$(AS) $(ASFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

flash: $(BUILD_DIR)/$(TARGET).elf
	$(OPENOCD) $(OCD_CFG) \
	  -c "program $(BUILD_DIR)/$(TARGET).elf verify reset exit"

clean:
	rm -rf $(BUILD_DIR)
