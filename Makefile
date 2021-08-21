# atmega16 or atmega32
MCU = atmega16
F_CPU = 12000000L

# source dirs
VPATH = src v-usb/usbdrv

# include dirs
LIBPATH = include v-usb/usbdrv

# compilers
CC = avr-gcc
CXX = avr-g++

# preprocess & compile flags
CPPFLAGS = $(addprefix -I, $(LIBPATH)) -DF_CPU=$(F_CPU)
CFLAGS = -mmcu=$(MCU) -Wall -Os

# outputs
OUT_DIR = build
TARGET = ATPR.elf

# sources
SRC_EXT = cpp|c|S
OBJECTS = $(shell find $(VPATH) | sed -rn 's/.+\/(.+)\.($(SRC_EXT))$$/$(OUT_DIR)\/\1.o/p')

build: mkdir $(OUT_DIR)/$(TARGET)
	avr-size --mcu=$(MCU) -C $(OUT_DIR)/$(TARGET)

mkdir:
	@mkdir -p $(OUT_DIR)

$(OUT_DIR)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.o: %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -x assembler-with-cpp -c $< -o $@
# -x flag for Windows compatibility

$(OUT_DIR)/$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

help:
	@echo "Welcome to ATPR Makefile."
	@echo
	@echo "Available actions:"
	@echo "  make           Build ATPR ELF file"
	@echo "  make build       and check size"
	@echo "  make help      Show this help"
	@echo "  make install   Upload with avrdude"
	@echo "  make clean     Clean build files"
	@echo
	@echo "Configurations:"
	@echo "   Target MCU: $(MCU)"
	@echo "        F_CPU: $(F_CPU)"
	@echo "  Upload Port: $(PORT)"
	@echo "   Programmer: $(PRG)"

PORT = usb
PRG = usbasp

install: build
	avrdude -c $(PRG) -P $(PORT) -p $(MCU)

.PHONY: clean
clean:
	rm -rf build
