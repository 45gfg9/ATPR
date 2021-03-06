# atmega16 or atmega32
MCU = atmega16
F_CPU = 16000000L

# source dirs
VPATH = src v-usb/usbdrv

# include dirs
LIBPATH = include v-usb/usbdrv

# compilers
CC = avr-gcc
CXX = avr-g++

# preprocess & compile flags
CPPFLAGS = $(addprefix -I, $(LIBPATH)) -DF_CPU=$(F_CPU) -DATPR_DBGEN
CFLAGS = -mmcu=$(MCU) -lm -Os -Wall -Wextra -Werror

# outputs
OUT_DIR = build
ELF_FILE = ATPR.elf
TARGET = $(OUT_DIR)/$(ELF_FILE)

# sources
SRC_EXT = cpp|c|S
OBJECTS = $(shell find $(VPATH) | sed -rn 's/.+\/(.+)\.($(SRC_EXT))$$/$(OUT_DIR)\/\1.o/p')

build: check mkdir $(TARGET)
	avr-size --mcu=$(MCU) -C $(TARGET)

mkdir:
	@mkdir -p $(OUT_DIR)

check:
	@cppcheck -Iinclude --std=c++11 --platform=avr8 src

$(OUT_DIR)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) -std=c++11 -c $< -o $@

$(OUT_DIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -std=c11 -c $< -o $@

$(OUT_DIR)/%.o: %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -x assembler-with-cpp -c $< -o $@
# -x flag for Windows compatibility

$(TARGET): $(OBJECTS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJECTS) -o $@

help:
	@echo "Welcome to ATPR Makefile."
	@echo
	@echo "Available actions:"
	@echo "  make [build]   Build ATPR ELF file"
	@echo "  make help      Show this help"
	@echo "  make install   Upload with avrdude"
	@echo "  make fuse      Set fuse bits"
	@echo "  make clean     Clean build files"
	@echo
	@echo "Configurations:"
	@echo "   Target MCU: $(MCU)"
	@echo "        F_CPU: $(F_CPU)"
	@echo "  Upload Port: $(PORT)"
	@echo "   Programmer: $(PRG)"

# upload settings
# hopefully one day we'll use ATPRsup for this
PORT = usb
PRG = usbasp
HFUSE = 0xD9
LFUSE = 0xEF
AVRDUDE = avrdude -p$(MCU) -c$(PRG) -P$(PORT)

fuse:
	$(AVRDUDE) -Uhfuse:w:$(HFUSE):m -Ulfuse:w:$(LFUSE):m

install: build
	$(AVRDUDE) -Uflash:w:$(TARGET)

.PHONY: clean
clean:
	rm -rf build
