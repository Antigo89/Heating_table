/*
Author: Antigo
Mail: Antigo1989@gmail.com
Date: 18.04.2024
Version: 1.0
Compile library SPI interface for ATMega328p. Master device. Speed 1MHz.
*/
#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

#define SPI_PORT 	PORTB
#define SCK_POS 	5
#define MISO_POS 	4
#define MOSI_POS	3
#define SS_POS		2
#define SPI_DDR 	DDRB

//Initialization SPI Master
void SPIMasterInit();
//Initialization SPI Slave
void SPISlaveInit();
//End connected SPI
void SPIClose();
//Send 8bit to standart SS
uint8_t SPIWrite(uint8_t data);
//Selected SS(CS) to '0' when reading
//uint8_t SPIReadSlave();
#endif
