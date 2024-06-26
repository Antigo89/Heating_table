/*
Author: Antigo
Mail: Antigo1989@gmail.com
Date: 25.09.2023
Version: 0.9 alfa
Timers/Counters for starting functions or periodic measurements.
From 61Hz and above.
Added function auto calibration coefficient divinity (N).
Mode CTC (4)

Call function or measurements place in Interrupt:
ISR(TIMER2_COMPA_vect){...}

NOTE:	Libraries involved: <avr/interrupt>
		sei(); in main.c
*/

#include "timer2CTC.h"

void timer2Init_freq(uint16_t freq){
	uint16_t div;
	TCCR2A = 0x00;
	TCCR2B = 0x00;
	if((F_CPU/(1024*freq))-1 > 1){
		div = 1024;
		TCCR2B = 0x07;
		}else if((F_CPU/(256*freq))-1 > 1){
		div = 256;
		TCCR2B = 0x06;
		}else if((F_CPU/(128*freq))-1 > 1){
		div = 128;
		TCCR2B = 0x06;
		}else if((F_CPU/(64*freq))-1 > 1){
		div = 64;
		TCCR2B = 0x04;
		}else if((F_CPU/(32*freq))-1 > 1){
		div = 32;
		TCCR2B = 0x03;
		}else if((F_CPU/(8*freq))-1 > 1){
		div = 8;
		TCCR2B = 0x02;
		}else{
		div = 1;
		TCCR2B = 0x01;
	}
	uint8_t timediv = (F_CPU/(div*freq))-1;
	OCR2A = timediv&0xFF;
	TCCR2A |= (1<<WGM21);
	TIMSK2 |= (1<<OCIE2A);
}