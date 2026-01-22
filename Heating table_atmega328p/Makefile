 
DEVICE=atmega328p
CLOCK_T=16000000
CLOCK_F=8000000
CLOCK=$(CLOCK_T)
HFUSE=0xD9
LFUSE=0xFC

ISP=usbasp
PORT=/dev/usb/ttyUSB0

TARGET = main

# Add additional .c files here
#OBJS = encoder.o easy_PID.o 
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

COMPILE	=	avr-gcc	-Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

# Set library paths
LIBRARY_PATHS = -I C:\Program Files (x86)\WinAVR\avr\include

all: $(TARGET).hex

main.hex: $(TARGET).o $(OBJS)
	rm -f $(TARGET).hex
	avr-gcc -mmcu=$(DEVICE) -o $(TARGET).elf $(OBJS)
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex
	avr-size --format=avr --mcu=$(DEVICE) $(TARGET).elf

%.o: %.c
	avr-gcc -g -Os -mmcu=$(DEVICE) -DF_CPU=$(CLOCK) -c $< -o $@
.c.o:
	$(COMPILE)	-c $<	-o $@
clean:
	rm -f *.o $(TARGET).elf $(TARGET).hex

flash: $(TARGET).hex
	tools/avrdude -c$(ISP) -p$(DEVICE) -P$(PORT) -U flash:w:$(TARGET).hex

fuses_final:
	tools/avrdude -c$(ISP) -p$(DEVICE) -P$(PORT) -u -U hfuse:w:$(HFUSE):m -U lfuse:w:$(LFUSE):m
	
fuses_read:
	tools/avrdude -c$(ISP) -p$(DEVICE) -P$(PORT) -U hfuse:r:hfuse.txt:h -U lfuse:r:lfuse.txt:h

avrdude:
	tools/avrdude -c$(ISP) -p$(DEVICE) -P$(PORT) -v
	
help:
	@echo "Usage: make                compile all"
	@echo "       make help           help"
	@echo "       make avrdude        testind connect"
	@echo "       make flash          upload in devices"
	@echo "       make fuses_read     upload in devices"
	@echo "       make fuses_final    write FUSES Byte (warning! only final devices)"
