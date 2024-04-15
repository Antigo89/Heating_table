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
 * Display: 7H x3 BC12-GWA (Katode(GND): PD5-PD7, Anode(VCC): 74H595N Q0-Q7)
 * Register: 74H595N (Q0-Q7: Anode Display, SH_CP/CLK: PC3, ST_CP/SET: PC2, DS/DATA: PC1) 
 */

#ifndef MAIN_H
#define MAIN_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>

#include "encoder.h"
#include "timer2CTC.h"
#include "SPI.h"
#include "easy_PID.h"
//Frequency settings
#define F_CPU 16000000UL
#define F_TIM 300UL //Hz

//PID settings
#define Kp  4.0
#define Ki  0.5
#define Kd  0.05
#define MAX_OUTPUT_PID 1023
#define USER_PID_PERIOD 100 //ms
#define PID_PERIOD USER_PID_PERIOD / 1000 * F_TIM

//Display settings
#define USER_DISPLAY_FREQUENCY 300 //max 300HZ
#define DISPLAY_FREQUENCY F_TIM / USER_DISPLAY_FREQUENCY - 1
#define USER_DELAY_AUTOOUT 3000 //ms
#define DELAY_AUTOOUT USER_DELAY_AUTOOUT / 1000 * F_TIM

//Encoder settings
#define USER_ENCODER_PERIOD 100 //ms
#define ENCODER_PERIOD USER_ENCODER_PERIOD / 1000 * F_TIM

//Measurement settings 
#define START_TEMP 200
#define MAX_TEMP 400
#define USER_TIME_MEASURE 260 //ms
#define TIME_MEASURE USER_TIME_MEASURE / 1000 * F_TIM

//array temperature[]
#define CURRENT 0
#define SET 1

#endif