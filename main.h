/*
 * @Author: Antigo
 * Mail: Antigo1989@gmail.com
 * Date: 03.12.2023
 * Version: 0.1
 * Controller for Heating Table.
 * Sensor: DS18B20 (PB3, PB4)
 * Display: 7H x3 BC12-GWA (Anode: PC0-PC6, Katode: PB0-PB2)
 * TIARC: BCA16-600 ()
 * Control: Encoder (DW: PD2, CLK: PD3)
 */

#ifndef MAIN_H
#define MAIN_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "ds18.h"
#include "encoderInterrupt.h"
#include "timer2CTC.h"

#define F_CPU 16000000UL

// ms
#define t_bounce 100

// 1/300 sec
#define delay_autoout 1500 //5sec


#endif