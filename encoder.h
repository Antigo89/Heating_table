/*
Author: Antigo
Mail: Antigo1989@gmail.com
Date: 17.04.2024
Version: 1.1
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

#include <avr/io.h>
#include <avr/interrupt.h>

#define STEP	1
//Connected encoder
#define PORTN	PORTD
#define PINN	PIND
#define DDRN	DDRD
#define DW_PIN	4
#define CLK_PIN	3

void encInit(uint16_t max_temp);
uint8_t encClick(uint16_t *count);

#endif