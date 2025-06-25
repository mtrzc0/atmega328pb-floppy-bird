# === User Configuration ===
MCU           = atmega328p
F_CPU         = 16000000UL
BAUD          = 9600
PROGRAMMER    = arduino
PORT          = COM5
AVRDUDE_BAUD  = 115200

# === Project Files ===
BUILD_DIR     = build
TARGET        = $(BUILD_DIR)/main
TARGET_ELF    = $(TARGET).elf
TARGET_HEX    = $(TARGET).hex
SRC           = main.c keyboard_driver.c matrix.c

# === Toolchain ===
CC            = avr-gcc
OBJCOPY       = avr-objcopy
CFLAGS        = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall
LDFLAGS       = -mmcu=$(MCU)

# === Build Targets ===
all: $(TARGET_HEX)

# utworzenie katalogu build, jeśli nie istnieje
$(BUILD_DIR):
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

# linkowanie do .elf (upewnia się, że build/ istnieje)
$(TARGET_ELF): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $@

# generowanie .hex
$(TARGET_HEX): $(TARGET_ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# wgrywanie przez bootloader Arduino UNO
flash: $(TARGET_HEX)
	avrdude -c $(PROGRAMMER) \
	        -p $(MCU) \
	        -P $(PORT) \
	        -b $(AVRDUDE_BAUD) \
	        -D \
	        -U flash:w:$(TARGET_HEX):i

# czyszczenie
clean:
	if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)
