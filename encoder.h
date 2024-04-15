/*
Author: Antigo
Mail: Antigo1989@gmail.com
Date: 23.07.2021
Version: 1.0
Compile library for processing encoder. Connect to any PIN. 
Polling occurs by timer or in a custom cycle.
Example:
Optimal Timer 100Hz;
ISR(TIMER1_COMPA_vect){
	encClick(&count)
}
*/
#ifndef ENCODERT_H
#define ENCODERT_H
#define STEP	1
//Connected encoder
#define PORTN	PORTD
#define PINN	PIND
#define DDRN	DDRD
#define DW_PIN	4
#define CLK_PIN	3

uint8_t curStat = 0x00;
uint8_t prevStat = 0x00;
volatile uint8_t  mask = 0x00;
volatile uint16_t max_count = 255;

void encInit(uint16_t max_temp){
	DDRN &= ~((1<<CLK_PIN)|(1<<DW_PIN));
	PORTN |= (1<<CLK_PIN)|(1<<DW_PIN);
	mask |= (1<<DW_PIN)|(1<<CLK_PIN);
	max_count = max_temp;
}

uint8_t encClick(uint16_t *count){
	uint8_t flag = 0;
	curStat = PINN & mask;
	
	if(curStat != prevStat){
		cli();
		if((prevStat == mask) && (curStat&(1<<DW_PIN)) && !(curStat&(1<<CLK_PIN))){
			if(*count < max_count) *count = *count + 1;
			flag = 1;
		}
		if((prevStat == mask) && (curStat&(1<<CLK_PIN)) && !(curStat&(1<<DW_PIN))){
			if(*count > 0) *count = *count - 1;
			flag = 1;
		}
		sei();
		prevStat = curStat;
	}
	return flag;
}


#endif