@echo off
avrdude -c usbasp -p atmega328p -P /dev/usb/ttyUSB0 -U hfuse:w:0xD9:m -U lfuse:w:0xFC:m