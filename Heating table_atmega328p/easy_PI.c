/*
Author: Antigo
Mail: Antigo1989@gmail.com
Date: 26.04.2024
Version: 0.9 alfa

}
*/

#include "easy_PI.h"

//coefficients
volatile uint8_t kp = 1;

//sets
volatile uint16_t setpoint = 0;
volatile int16_t integral_limit = 27000;
//values
volatile int16_t integral = 0;
volatile int16_t last_error = 0;


void set_k(uint8_t koef_p){
	kp = koef_p;
}

void set_setpoint(uint16_t setp){
	setpoint = setp;
}

int16_t stepPI(uint16_t sensor_value) {
	int16_t output = 0;
	volatile int16_t error = 0;
	volatile int16_t derivative = 0;
	
	error = setpoint - sensor_value;
	integral += error;
	integral = (integral > integral_limit) ? integral_limit : integral;
	integral = (integral < -integral_limit) ? -integral_limit : integral;
	
	derivative = error - last_error;
	
	int16_t kp_out = (int16_t)(kp * error);
	int16_t ki_out = (int16_t)(integral/10);
	int16_t kd_out = (int16_t)(derivative/10);
	output = kp_out + ki_out + kd_out;

	last_error = error;
	return output;
}