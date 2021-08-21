MCU = atmega16
F_CPU = 12000000L

VPATH = src:v-usb/usbdrv

LIBPATH = include v-usb/usbdrv

CC = avr-gcc
CXX = avr-g++

FLAGS = $(addprefix -I, $(LIBPATH)) -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)

OUT_DIR = build

# Must we specify all .o here?
OBJECTS = $(addprefix $(OUT_DIR)/, usbdrv.o usbdrvasm.o oddebug.o ATPR.o)

build: mkdir $(OUT_DIR)/main.elf

$(OUT_DIR)/%.o: %.cpp
	$(CXX) $(FLAGS) -c $< -o $@

$(OUT_DIR)/%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(OUT_DIR)/%.o: %.S
	$(CC) $(FLAGS) -x assembler-with-cpp -c $< -o $@
# -x flag for Windows compatibility

$(OUT_DIR)/main.elf: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

mkdir:
	@mkdir -p $(OUT_DIR)

help:
	@echo "ATPR Makefile"

PORT = usb
PRG = usbasp

install: build
	avrdude -c $(PRG) -P $(PORT) -p $(MCU)

.PHONY: clean
clean:
	rm -r build
