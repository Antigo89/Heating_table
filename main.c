#include "main.h"

#define TEST

uint8_t arrayChar[3] = {0,0,0};

volatile uint8_t raz = 0b00100000;
volatile uint8_t seg;

uint8_t temp_set_l EEMEM;
uint8_t temp_set_h EEMEM;

volatile uint8_t flagDisp = 0;
volatile uint8_t flag_enc = 0;
volatile uint8_t flag_measure = 0;
volatile uint16_t flag_pid = 0;

uint16_t time_delay = 0;

const uint8_t znak[10] = {
	/*Dp,G,F,E,D,C,B,A*/
	0b00111111, //0x3F
	0b00000110, //0x06
	0b01011011, //0x5B
	0b01001111, //0x4F
	0b01100110, //0x66
	0b01101101, //0x6D
	0b01111101, //0x7D
	0b00000111, //0x07
	0b01111111, //0x7F
	0b01101111 //0x6F
};

void portInit(){
	ADCSRA = 0x80;
	//TODO: Sensor
	DDRB = 0x06;
	DDRC = 0xFE;
	DDRD = 0xE0;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0xE0;	
}

void pwmInit(){
	DDRB |= (1<<DDB1);
	TCCR1A |= (1<<WGM11)|(1<<WGM10)|(1<<COM1A1);
	TCCR1B |= (1<<WGM12)|(1<<CS10)|(1<<CS11);
	OCR1A = 0;
}

void printDisp(uint16_t dig){
	uint8_t d = 0;
	uint8_t s = 0;
	uint8_t f = 0x00;
	for(s=0;s<3;s++){
		switch (s) {
			case 0:
			d = (dig/100)%10;
			break;
			case 1:
			d = (dig/10)%10;
			break;
			case 2:
			d = dig%10;
			break;
		}
		if(f>0||d>0){
			arrayChar[s] &= 0x80;
			arrayChar[s] |= (znak[d] & 0x7F);
			f = 1;
			}else{
			arrayChar[s] &= 0x80;
		}
	}
}

void outputDisp(){
		uint8_t mask = 0x80;
		uint8_t k = 0;
		PORTC &= ~(1<<PORTC2); //ST 0
		for(k = 0; k<8; k++){
			if(arrayChar[seg] & mask){
				PORTC |= (1<<PORTC1); // DATA 1
				PORTC |= (1<<PORTC3); // CLK 1
				PORTC &= ~(1<<PORTC3); // CLK 0
			}else{
				PORTC &= ~(1<<PORTC1); // DATA 0
				PORTC |= (1<<PORTC3); // CLK 1
				PORTC &= ~(1<<PORTC3); // CLK 0
			}
			mask = mask >> 1;
		}
		PORTD = ~raz;
		raz = raz == 0b10000000 ? 0b00100000 : raz << 1;
		seg = seg == 2 ? 0 : seg + 1;
		PORTC |= (1 << PORTC2); //ST 1
		flagDisp = 0;
}

void write_temp(uint16_t temperature){
	uint8_t two = (temperature&0xFF);
	uint8_t one = ((temperature >> 8) & 0xFF);
	eeprom_write_byte(&temp_set_l, two);
	eeprom_write_byte(&temp_set_h, one);
}

uint16_t measure_temperature(){
	PORTB &= ~(1<<PORTB2);
	_delay_ms(1);
	uint16_t tmp_16 = SPIWrite(0x00);
	tmp_16 <<= 8;
	tmp_16 |= SPIWrite(0x00);
	
		if(!(tmp_16&0x04)){
			tmp_16 >>= 3;
			tmp_16 /= 4;			
		}else{
			tmp_16 = 1;
		}
	
	PORTB |= (1<<PORTB2);
	//_delay_ms(10);
	return tmp_16;
}

int main(void){

	uint16_t temperatures[2] = {100, 100};
	
	portInit();
	pwmInit();
	SPIMasterInit();
	encInit(MAX_TEMP);
	timer2Init_freq(F_TIM);
	sei();
	//write_temp(300); 
	uint8_t cursor = 1;
	uint16_t temp_eeprom;
	uint16_t temp_eeprom_16;
	temp_eeprom = eeprom_read_byte(&temp_set_h);
	temp_eeprom_16 = eeprom_read_byte(&temp_set_l);
	temp_eeprom_16 = temp_eeprom_16 + ((temp_eeprom << 8) & 0xFFFF);
	if(temp_eeprom_16 > MAX_TEMP) temp_eeprom_16 = START_TEMP;
	temperatures[SET] = temp_eeprom_16;
	//settings PID
	set_k(Kp, Ki, Kd);
	set_limits(0, MAX_OUTPUT_PID);
	
	while (1){
		if(flag_enc > ENCODER_PERIOD){
			if(encClick(&temperatures[SET])){
				cursor = SET;
				time_delay = 0;
			}
			flag_enc = 0;
		}
		
		if(flagDisp > DISPLAY_FREQUENCY){
			printDisp(temperatures[cursor]);
			outputDisp();
		}
		
		if(flag_measure > TIME_MEASURE){
			temperatures[CURRENT] = measure_temperature();
			flag_measure = 0;
		}
				
		if(flag_pid > PID_PERIOD){
			OCR1A = 1023 - (uint16_t)stepPID(temperatures[CURRENT]);
			flag_pid = 0;
		}

		if(time_delay>DELAY_AUTOOUT){
			if(cursor>CURRENT){
				#ifndef TEST
				write_temp(temperatures[SET]);
				#endif
				set_setpoint(temperatures[SET]);
				cursor = CURRENT;
				//printDisp(temperatures[cursor]);
			}
			time_delay = 0;
		}

		if(!(PINB&(1<<PINB0))){
			//test function
			temperatures[SET] = 300;
			cursor = SET;
			time_delay = 0;
		}
		
    }
}

ISR(TIMER2_COMPA_vect){
	flagDisp++;
	flag_enc++;
	time_delay++;
	flag_measure++;
	flag_pid++;
}