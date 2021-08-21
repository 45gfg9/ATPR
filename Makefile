MCU = atmega16 # or atmega32
F_CPU = 12000000L

VPATH = src v-usb/usbdrv

LIBPATH = include v-usb/usbdrv

CC = avr-gcc
CXX = avr-g++

CPPFLAGS = $(addprefix -I, $(LIBPATH)) -DF_CPU=$(F_CPU)
CFLAGS = -mmcu=$(MCU) -Wall -Os

OUT_DIR = build

SRC_EXT = cpp|c|S
OBJECTS = $(shell find $(VPATH) | sed -rn 's/.+\/(.+)\.($(SRC_EXT))$$/$(OUT_DIR)\/\1.o/p')

build: mkdir $(OUT_DIR)/main.elf

mkdir:
	@mkdir -p $(OUT_DIR)

$(OUT_DIR)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.o: %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -x assembler-with-cpp -c $< -o $@
# -x flag for Windows compatibility

$(OUT_DIR)/main.elf: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

help:
	@echo "Welcome to ATPR Makefile."
	@echo
	@echo "Available actions:"
	@echo "  make           Build ATPR ELF file"
	@echo "  make build     ^"
	@echo "  make help      Show this help"
	@echo "  make install   Upload with avrdude"
	@echo "  make clean     Clean build files"
	@echo
	@echo "Configurations:"
	@echo "  Target MCU: $(MCU)"
	@echo "  F_CPU: $(F_CPU)"

PORT = usb
PRG = usbasp

install: build
	avrdude -c $(PRG) -P $(PORT) -p $(MCU)

.PHONY: clean
clean:
	rm -rf build
