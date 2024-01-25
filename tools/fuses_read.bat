@echo off
avrdude -c usbasp -p atmega328p -P /dev/usb/ttyUSB0 -U hfuse:r:hfuse.txt:h -U lfuse:r:lfuse.txt:h