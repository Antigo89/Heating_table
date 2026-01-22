/*
Author: Antigo
Mail: Antigo1989@gmail.com
Date: 18.04.2024
Version: 1.0
Compile library SPI interface for ATMega328p. Master device. Speed 1MHz.
*/
	
#include "SPI.h"
	
//Initialization SPI Master
void SPIMasterInit(){
	//MOSI SCK SS - outport
	DDRB |=((1<<3)|(1<<5)|(1<<2));
	//SS - '1'
	PORTB |=(1<<2);
	//Enable SPI, Master, sck = f/16 (1MHz)
	SPCR|=(1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<CPHA);

}
//Initialization SPI Slave
void SPISlaveInit(){
	//MISO - outport
	DDRB |=(1<<4);
	//Enable SPI
	SPCR|=(1<<SPE);
}
//End connected SPI
void SPIClose(){
	SPCR &= ~(1<<SPE);
	DDRB &= (~((1<<3)|(1<<5)));
}
//Send 8bit to standart SS
uint8_t SPIWrite(uint8_t data){
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	return (SPDR);
}
//Selected SS(CS) to '0' when reading
/*
uint8_t SPIReadSlave(){
	while(!(SPSR & (1 << SPIF)));
	return SPDR;
}
*/