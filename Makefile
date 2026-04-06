OBJS = build/main.o build/ringbuffer.o build/serial.o
MMCU = atmega328p
CFLAGS = -Wall -Werror -g
BIN = build/echo.elf
HEX = build/echo.hex

all: $(HEX)

$(HEX): $(BIN)
	avr-objcopy -O ihex -j .text -j .data -R .eeprom $^ $@

$(BIN): $(OBJS) | build
	avr-gcc -Os -mmcu=$(MMCU) $(CFLAGS) -o $@ $^

build/%.o: src/%.c
	avr-gcc -Os -mmcu=$(MMCU) $(CFLAGS) -c -o $@ $^

build:
	mkdir -p build

.PHONY: clean
clean:
	@rm -rf build/*
