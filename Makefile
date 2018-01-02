#This is the form of names cross compilers usually have
CXX=avr-g++
CC=avr-gcc
LD=avr-g++
 
#atmega328p is used on the Arduino Uno
#It needs to be specified in several places so it's in the 
#Makefile, not the source code.
MCU=atmega328p
 
#serial port for programmer
#Find this by typing "dmesg" after plugging in the cable
PORT=/dev/ttyACM0
 
#Specify the CPU frequency in Hz
#Required for the delay() function in the C source.
F_CPU=16000000UL
 
#Specify optimizations:t's more common to optimize for size
#not speed (-Os) due to limited flash. We need to tell the compiler
#what the MCU is (of course), and F_CPU needs to be #defined before
#the util header is included.
FLAGS=-Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)
 
#Set these flags so they're picked up by the implicit C and C++ 
#compiler rules.
CXXFLAGS=$(FLAGS)
CFLAGS=$(FLAGS)
 
 
OBJECTS=prog.o
 
#Bog standard linker line
test:$(OBJECTS)
	$(LD) -o $@ $<
 
 
# Programmers expect HEX files not ELF files.
# Copy the text and data sections to make a hex file.
# .text is the machine code. .data is all the static data
# I don't believe we need anything else
%.hex: %
	avr-objcopy -j .text -j .data -O ihex $< $@
 
clean:
	rm -f *.o *.hex test
 
# "make upload" target to program the MCU
# -p specify MCU
# -c progrmmer type.
# -e erase
# -U actions which are flash memory write test.hex
# -P perial port
upload:test.hex
	avrdude -p $(MCU) -c arduino -e -U flash:w:test.hex  -P $(PORT)
