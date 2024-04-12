/*
Author: Antigo
Mail: Antigo1989@gmail.com
Date: 12.04.2024
Version: 0.9

}
*/

#ifndef EASY_PID_H
#define EASY_PID_H

volatile float kp = 1.0;
volatile float ki = 0.1;
volatile float kd = 0.01;

volatile uint16_t setpoint = 0;
volatile int16_t max_output = 255;
volatile int16_t min_output = 0;

void set_k(float koef_p,float koef_i,float koef_d){
	kp = koef_p;
	ki = koef_i;
	kd = koef_d;
}

void set_setpoint(uint16_t setp){
	setpoint = setp;
}

void set_limits(int16_t min_limit, int16_t max_limit){
	min_output = min_limit;
	max_output = max_limit;
}

int16_t stepPID(uint16_t sensor_value) {
	int16_t output = 0;
	volatile int16_t error = 0;
	volatile int16_t integral = 0;
	volatile int16_t derivative = 0;
	volatile int16_t last_error = 0;
	
	error = setpoint - sensor_value;
	integral += error;
	derivative = error - last_error;
	
	//TODO: Приведение типов дописать
	output = kp * error + ki * integral + kd * derivative;
	
	output = (output > max_output) ? max_output : output;
	output = (output < min_output) ? min_output : output;

	last_error = error;
	return output;
}

#endif