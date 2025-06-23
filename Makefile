# === User Configuration ===
MCU = atmega328pb            # Change to match your MCU
F_CPU = 16000000UL           # CPU frequency for compilation
BAUD = 9600                  # Optional: used in your code
PROGRAMMER = xplainedmini          # Programmer type
PORT = COM4          		 # Not used by all programmers

# === Project Files ===
TARGET = build/main                # Output file (no extension)
TARGET_ELF = build/main.elf        # Output file
TARGET_HEX = build/main.hex        # Output file
SRC = main.c keyboard_driver.c     # Add more .c files separated by spaces

# === Toolchain ===
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall
LDFLAGS = -mmcu=$(MCU)

# === Build Targets ===
all: $(TARGET_HEX)

$(TARGET_ELF): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@

$(TARGET_HEX): $(TARGET_ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

flash: $(TARGET_HEX)
	avrdude -c $(PROGRAMMER) -p $(MCU) -U flash:w:$(TARGET_HEX)

clean:
	rm build/*