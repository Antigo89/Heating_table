@echo off
avrdude -c usbasp -p atmega328p -P /dev/usb/ttyUSB0 -U flash:w:main.hex