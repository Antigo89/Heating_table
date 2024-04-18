/*
Author: Antigo
Mail: Antigo1989@gmail.com
Date: 17.04.2024
Version: 0.9 alfa

}
*/

#ifndef EASY_PID_H
#define EASY_PID_H

#include <avr/io.h>

void set_k(float koef_p,float koef_i,float koef_d);
void set_setpoint(uint16_t setp);
void set_limits(int16_t min_limit, int16_t max_limit);
int16_t stepPID(uint16_t sensor_value);

#endif