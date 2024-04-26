#include "main.h"

#define TEST

uint8_t arrayChar[3] = {0,0,0};

volatile uint8_t raz = 0b00100000;
volatile uint8_t seg;

uint8_t temp_set_l EEMEM;
uint8_t temp_set_h EEMEM;

volatile uint8_t flagDisp = 0;
volatile uint8_t flag_enc = 0;
volatile uint16_t flag_measure = 0;
volatile uint16_t flag_pid = 0;

uint16_t time_delay = 0;

volatile int16_t ocr_set = 0;

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
	PORTB = 0x04;
	PORTC = 0x00;
	PORTD = 0xE0;	
	EICRA |= (1<<ISC01);
	EIMSK |= (1<<INT0);
}

void Tim1Init(){
	DDRB |= (1<<DDB1);
	TCCR1A = 0;
	TCCR1B = 0;
	OCR1A = MAX_TIM1;
	OCR1B = MAX_TIM1 - 1;
	TIMSK1 |= (1<<OCIE1A)|(1<<OCIE1B);
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
	_delay_us(1500);
	uint16_t tmp_16 = SPIWrite(0x00);
	tmp_16 <<= 8;
	tmp_16 |= SPIWrite(0x00);
	
		if(!(tmp_16&0x04)){
			tmp_16 >>= 3;
			tmp_16 /= 4;			
		}else{
			tmp_16 = 1;
		}
	//_delay_ms(1);
	PORTB |= (1<<PORTB2);
	//_delay_ms(10);
	return tmp_16;
}

int main(void){
	uint8_t display_frequency = F_TIM / USER_DISPLAY_FREQUENCY - 1; 
	uint8_t encoder_period = USER_ENCODER_PERIOD / 1000 * F_TIM; 
	uint16_t time_measure = 80;
	uint16_t pid_period = USER_PID_PERIOD / 1000 * F_TIM;
	uint16_t delay_autoout = USER_DELAY_AUTOOUT / 1000 * F_TIM;
	
	uint16_t temperatures[2] = {100, 100};
	
	portInit();
	Tim1Init();
	SPIMasterInit();
	encInit(MAX_TEMP);
	timer2Init_freq(F_TIM);
	sei();
	//write_temp(300); 
	uint8_t cursor = SET;
	uint16_t temp_eeprom;
	uint16_t temp_eeprom_16;
	temp_eeprom = eeprom_read_byte(&temp_set_h);
	temp_eeprom_16 = eeprom_read_byte(&temp_set_l);
	temp_eeprom_16 = temp_eeprom_16 + ((temp_eeprom << 8) & 0xFFFF);
	if(temp_eeprom_16 > MAX_TEMP) temp_eeprom_16 = START_TEMP;
	temperatures[SET] = temp_eeprom_16;
	printDisp(temperatures[SET]);
	//settings PID
	set_k(Kp);
	
	while (1){
		if(flag_enc > encoder_period){
			if(encClick(&temperatures[SET])){
				cursor = SET;
				printDisp(temperatures[SET]);
				time_delay = 0;
			}
			flag_enc = 0;
		}
		
		if(flagDisp > display_frequency){
			//printDisp(temperatures[cursor]);
			outputDisp();
		}
		
		if(flag_measure > time_measure){
			temperatures[CURRENT] = measure_temperature();
			if(cursor == CURRENT){
				printDisp(temperatures[CURRENT]);
			}
			flag_measure = 0;
		}
				
		if(flag_pid > pid_period){
			ocr_set += stepPI(temperatures[CURRENT]);
			ocr_set = (ocr_set > MAX_OUTPUT_PID) ? MAX_OUTPUT_PID : ocr_set;
			ocr_set = (ocr_set < 0) ? 0 : ocr_set;
			OCR1B = 540 - (uint16_t)ocr_set;
			flag_pid = 0;
		}

		if(time_delay>delay_autoout){
			if(cursor>CURRENT){
				#ifndef TEST
				write_temp(temperatures[SET]);
				#endif
				set_setpoint(temperatures[SET]);
				cursor = CURRENT;
				printDisp(temperatures[CURRENT]);
			}
			time_delay = 0;
		}

		if(!(PINB&(1<<PINB0))){
			//test function
			temperatures[SET] = 300;
			cursor = SET;
			printDisp(temperatures[SET]);
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

ISR(INT0_vect){
	TCCR1B |= (1<<WGM12)|(1<<CS12);
}

ISR(TIMER1_COMPB_vect){
	PORTB |= (1<<PORTB1);
}

ISR(TIMER1_COMPA_vect){
	PORTB &= ~(1<<PORTB1);
	TCCR1B = 0;
}



