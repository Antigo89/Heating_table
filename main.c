
#include "main.h"

uint8_t arrayChar[3] = {0,0,0};

volatile uint8_t raz = 0b00100000;
volatile uint8_t seg;

volatile uint8_t flagDisp = 0;

const uint8_t znak[10] = {
	/*Dp,G,F,E,D,C,B,A*/
	0b00111111, //0x3F
	0b00000110, //0x06
	0b01011011, //0x5B
	0b01001111, //0x4F
	0b01100110, //0x66
	0b01101101, //0x6D
	0b01111101, //0x7D
	0b00000111, //0x07
	0b01111111, //0x7F
	0b01101111 //0x6F
};

void portInit(){
	ADCSRA = 0x80;
	//TODO: Encoder, Sensor
	DDRB = 0x06;
	DDRC = 0xFE;
	DDRD = 0xE0;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0xE0;
}

void printDisp(uint16_t dig){
	uint8_t d;
	uint8_t s;
	uint8_t f = 0x00;
	for(s=0;s<3;s++){
		switch (s) {
			case 0:
			d = (dig/100)%10;
			break;
			case 1:
			d = (dig/10)%10;
			break;
			case 2:
			d = dig%10;
			break;
		}
		if(f>0||d>0){
			arrayChar[s] &= 0x80;
			arrayChar[s] |= (znak[d] & 0x7F);
			f = 1;
			}else{
			arrayChar[s] &= 0x80;
		}
	}
}

void outputDisp(){
		uint8_t mask = 0x80;
		uint8_t k = 0;
		PORTC &= ~(1 << PORTC2); //ST 0
		for(k = 0; k < 8; k++){
			if(arrayChar[seg] & mask){
				PORTC |= (1 << PORTC1); // DATA 1
				PORTC |= (1 << PORTC3); // CLK 1
				PORTC &= ~(1 << PORTC3); // CLK 0
			}else{
				PORTC &= ~(1 << PORTC1); // DATA 0
				PORTC |= (1 << PORTC3); // CLK 1
				PORTC &= ~(1 << PORTC3); // CLK 0
			}
			mask = mask >> 1;
		}
		PORTD = ~raz;
		raz = raz == 0b10000000 ? 0b00100000 : raz << 1;
		seg = seg == 2 ? 0 : seg + 1;
		PORTC |= (1 << PORTC2); //ST 1
		flagDisp = 0;
}

int main(void){
	portInit();
	timer2Init_freq(300);
	sei();
	printDisp(280);
	

	while (1){
		
		if(flagDisp = 1){
			outputDisp();
		}
		
    }
}

ISR(TIMER2_COMPA_vect){
	flagDisp = 1;
	/*
	static uint8_t r = 0b00100000;
	static uint8_t s;
	PORTC = arrayChar[s];
	PORTD = ~r;
	r = r == 0b10000000 ? 0b00100000 : r << 1;
	s = s == 2 ? 0 : s + 1;
	*/
}
