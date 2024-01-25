
#include "main.h"

uint8_t arrayChar[3] = {0,0,0};

const uint8_t znak[10] = {
	/*Dp,G,F,E,D,C,B,A*/
	0b00111111,
	0b00000110,
	0b01011011,
	0b01001111,
	0b01100110,
	0b01101101,
	0b01111101,
	0b00000111,
	0b01111111,
	0b01101111
};

void portInit(){
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

int main(void){
	portInit();
	timer2Init_freq(300);
	sei();
	
    while (1){
    }
}

ISR(TIMER2_COMPA_vect){
	static uint8_t r = 0b00100000;
	static uint8_t s;
	PORTC = arrayChar[s];
	PORTD = ~r;
	r = r == 0b10000000 ? 0b00100000 : r << 1;
	s = s == 2 ? 0 : s + 1;
}
