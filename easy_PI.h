/*
Author: Antigo
Mail: Antigo1989@gmail.com
Date: 26.04.2024
Version: 0.9 alfa

}
*/

#ifndef EASY_PI_H
#define EASY_PI_H

#include <avr/io.h>

void set_k(uint8_t koef_p);
void set_setpoint(uint16_t setp);
int16_t stepPI(uint16_t sensor_value);

#endif