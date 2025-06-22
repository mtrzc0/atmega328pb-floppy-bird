# === User Configuration ===
MCU = atmega328pb            # Change to match your MCU
F_CPU = 16000000UL           # CPU frequency for compilation
BAUD = 9600                  # Optional: used in your code
PROGRAMMER = usbasp          # Programmer type
PORT = /dev/ttyUSB0          # Not used by all programmers

# === Project Files ===
TARGET = main                # Output file (no extension)
SRC = main.c                 # Add more .c files separated by spaces

# === Toolchain ===
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall
LDFLAGS = -mmcu=$(MCU)

# === Build Targets ===
all: $(TARGET).hex

$(TARGET).elf: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

flash: $(TARGET).hex
	avrdude -c $(PROGRAMMER) -p $(MCU) -U flash:w:$(TARGET).hex

clean:
	rm -f *.o *.elf *.hex