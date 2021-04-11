# Makefile for the avg-gcc toolchain


# Program settings
CC = avr-gcc
CXX = avr-g++
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
NM = avr-nm
AVRDUDE = avrdude
REMOVE = rm -f
MV = mv -f
# HW parameters
MCU = atmega328p
F_CPU = 16000000
FORMAT = ihex



# Name of this Makefile (used for "make depend").
MAKEFILE = Makefile
# source settings
TARGET = Tft
SOURCE_FOLDER 	= ./
OBJECT_FOLDER	= ./obj


# Define all source files
SRC 	:= $(wildcard $(SOURCE_FOLDER)/*.c) 
CXXSRC	:= $(wildcard $(SOURCE_FOLDER)/*.cpp)
ASRC 	:= $(wildcard $(SOURCE_FOLDER)/*.S)
# Define all object files.
OBJ = $(patsubst $(SOURCE_FOLDER)/%.c, $(OBJECT_FOLDER)/%.o, $(SRC))
# Define all listing files.
LST = $(patsubst $(SOURCE_FOLDER)/%.c, $(OBJECT_FOLDER)/%.lst, $(SRC))


# Build & compile parameters
# Place -D or -U options here
CDEFS = -DF_CPU=$(F_CPU)
CXXDEFS = -DF_CPU=$(F_CPU)
# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
DEBUG = stabs
OPT = s
CSTANDARD = -std=gnu99
CDEBUG = -g$(DEBUG)
CWARN = -Wall
CTUNING =  -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects
CFLAGS = $(CDEBUG) $(CDEFS) $(CINCS) -O$(OPT) $(CWARN) $(CSTANDARD) $(CEXTRA)
CXXFLAGS =  -g -O$(OPT) -Wall $(CXXDEFS) -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto
ELF_FLAGS = $(CWARN) -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections
ASFLAGS = -c -g -x assembler-with-cpp -flto -MMD $(CDEFS)
LDFLAGS = 
# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = $(CFLAGS) -mmcu=$(MCU) $(CINCS)
ALL_CXXFLAGS = $(CXXFLAGS) -mmcu=$(MCU) $(CINCS)
ALL_ASFLAGS = -mmcu=$(MCU) -x assembler-with-cpp $(ASFLAGS) $(CINCS) 


# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
# General rules

# Compile: create object files from C source files.
$(OBJECT_FOLDER)/%.o: $(SOURCE_FOLDER)/%.c
	$(CC) -c $(ALL_CFLAGS) $< -o $@ 

# Link: create ELF output file from object files.
$(TARGET).elf: $(OBJ)
	$(CC) $(ALL_CFLAGS) $(OBJ) --output $@ $(LDFLAGS)

# Convert ELF to COFF for use in debugging / simulating in AVR Studio or VMLAB.
COFFCONVERT=$(OBJCOPY) --debugging \
--change-section-address .data-0x800000 \
--change-section-address .bss-0x800000 \
--change-section-address .noinit-0x800000 \
--change-section-address .eeprom-0x810000 


coff: $(TARGET).elf
	$(COFFCONVERT) -O coff-avr $(TARGET).elf $(TARGET).cof

extcoff: $(TARGET).elf
	$(COFFCONVERT) -O coff-ext-avr $(TARGET).elf $(TARGET).cof

%.hex : %.elf
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

%.eep : %.elf
	$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings  --change-section-lma .eeprom=0 -O $(FORMAT) $< $@

# Create extended listing file from ELF output file.
%lss : %.elf
	$(OBJDUMP) -h -S $< > $@

# Create a symbol table from ELF output file.
%.sym: %.elf
	$(NM) -n $< > $@



# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
# Make targets

all: build

build: elf hex eep

elf: $(TARGET).elf
hex: $(TARGET).hex
eep: $(TARGET).eep
lss: $(TARGET).lss 
sym: $(TARGET).sym


# Target: clean project.
clean:
	$(REMOVE) $(TARGET).hex $(TARGET).eep $(TARGET).cof $(TARGET).elf \
	$(TARGET).map $(TARGET).sym $(TARGET).lss \
	$(OBJ) $(LST) $(SRC:.c=.s) $(SRC:.c=.c.d) $(CXXSRC:.cpp=.s) $(CXXSRC:.cpp=.cpp.d) $(ASRC:.S=.S.d)

depend:
	if grep '^# DO NOT DELETE' $(MAKEFILE) >/dev/null; \
	then \
		sed -e '/^# DO NOT DELETE/,$$d' $(MAKEFILE) > \
			$(MAKEFILE).$$$$ && \
		$(MV) $(MAKEFILE).$$$$ $(MAKEFILE); \
	fi
	echo '# DO NOT DELETE THIS LINE -- make depend depends on it.' \
		>> $(MAKEFILE); \
	$(CC) -M -mmcu=$(MCU) $(CDEFS) $(CINCS) $(SRC) $(ASRC) >> $(MAKEFILE)

	
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
# Uploading

# Programming support using avrdude. Settings and variables.
UPLOAD_RATE = 115200
AVRDUDE_PROGRAMMER = arduino
AVRDUDE_PART = atmega328p
AVRDUDE_PORT = /dev/ttyACM0
AVRDUDE_WRITE_FLASH = -Uflash:w:$(TARGET).hex:i
AVRDUDE_FLAGS = -v  -p $(AVRDUDE_PART) -c $(AVRDUDE_PROGRAMMER) -P $(AVRDUDE_PORT) -b $(UPLOAD_RATE) -D
	
# Program the device.  
upload: $(TARGET).hex $(TARGET).eep
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)






.PHONY:	all build elf hex eep lss sym program coff extcoff clean depend