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

#ifndef TIMER2CTC_H
#define TIMER2CTC_H

#include <avr/io.h>

void timer2Init_freq(uint16_t freq);

#endif
