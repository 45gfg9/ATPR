MCU = atmega16
F_CPU = 12000000L

VPATH = src:v-usb/usbdrv

LIBPATH = include v-usb/usbdrv

CC = avr-gcc
CPPC = avr-g++

CARGS = $(addprefix -I, $(LIBPATH)) -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)

OUT_DIR = build

# Must we specify all .o here?
OBJECTS = usbdrv.o usbdrvasm.o oddebug.o ATPR.o

.cpp.o:
	$(CPPC) $(CARGS) -c $< -o $(OUT_DIR)/$@

.c.o:
	$(CC) $(CARGS) -c $< -o $(OUT_DIR)/$@

.S.o:
	$(CC) $(CARGS) -x assembler-with-cpp -c $< -o $(OUT_DIR)/$@
# -x flag for Windows compatibility

build: mkdir $(OBJECTS)
	$(CC) $(addprefix $(OUT_DIR)/, $(OBJECTS)) -o $(OUT_DIR)/main.elf

mkdir:
	mkdir $(OUT_DIR) 2>/dev/null || true

help:
	@echo "ATPR Makefile"

PORT = usb
PRG = usbasp

upload: build
	avrdude -c $(PRG) -P $(PORT) -p $(MCU)

.PHONY: clean
clean:
	rm -r build
