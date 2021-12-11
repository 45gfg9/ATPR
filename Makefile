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
CPPFLAGS = $(addprefix -I, $(LIBPATH)) -DF_CPU=$(F_CPU) -DDEBUG_LEVEL=3
CFLAGS = -mmcu=$(MCU) -Wall -Wextra -Werror -Wno-error=cpp -Os

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
	@cppcheck src

$(OUT_DIR)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

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
# hopefully one day we'll use ATPR for this
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
