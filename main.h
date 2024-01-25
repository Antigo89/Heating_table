/*
 * @Author: Antigo
 * Mail: Antigo1989@gmail.com
 * Date: 03.12.2023
 * Version: 0.1
 * Controller for Heating Table.
 * Control: Key (PB0)
 * TIARC: MOC3021 -> BCA16-600 (OC1A: PB1)
 * Sensor: max6675 (MOSI: PB3, MISO: PB4, SCK: PB5, SS: PB2)
 * UART: not use (Rx: PD0, Tx: PD1)
 * Zero crossing: PC814 <- 2W10 (INT0: PD2)
 * Control: Encoder (DW: PD3, CLK: PD4)
 * Display: 7H x3 BC12-GWA (Katode: PD5-PD7, Anode: PC0-PC6)
 */

#ifndef MAIN_H
#define MAIN_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
/*
#include "ds18.h"
#include "encoderInterrupt.h"
*/
#include "timer2CTC.h"

#define F_CPU 16000000UL

// ms
#define t_bounce 100

// 1/300 sec
#define delay_autoout 1500 //5sec


#endif