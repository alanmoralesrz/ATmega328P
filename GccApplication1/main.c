/*
 * 
 * Alan Dario Morales Rodriguez
 * 20-11-2024
 * 
 */ 

//***************************LIBRERÍAS******************************//
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "display7seg.h"
#include "timers.h"
#include "ext_ISR.h"

//**************************MACROS ENTRADAS*************************//

// BOTONES INC/DECR POR INTERRUPCIONES
#define BUTTONS_INCDEC_DDRX DDRD
#define BUTTONS_INCDEC_PORTX PORTD
#define BUTTONS_INCDEC_PINX PIND
#define BUTTON_INC PIND2
#define BUTTON_DEC PIND3
#define BUTTON_INC_PRESS BUTTONS_INCDEC_PINX & _BV(BUTTON_INC)
#define BUTTON_DEC_PRESS BUTTONS_INCDEC_PINX & _BV(BUTTON_DEC)

// BOTONES CAMBIO DE ESTADO (HARDWARE DEBOUNCE)
#define BUTTONS_DDRX DDRB
#define BUTTONS_PORTX PORTB
#define BUTTONS_PINX PINB
#define BUTTON_ON_OFF PINB1
#define BUTTON_RESET PINB2
#define BUTTON_ON_OFF_PRESS BUTTONS_PINX & _BV(BUTTON_ON_OFF)
#define BUTTON_RESET_PRESS BUTTONS_PINX & _BV(BUTTON_RESET)

//************************MACROS SALIDAS****************************//
#define ACTUATOR  PORTB3   // Pin D11 conectado al relevador
#define ACTUATOR_ON PORTB |=_BV(ACTUATOR)
#define ACTUATOR_OFF PORTB &= ~_BV(ACTUATOR);

//*************************VARIABLES********************************//
//VARIABLES DE TIMERS
volatile uint8_t timer0_count_display = 0; 
volatile uint16_t timer1_count = 0;

//VARIABLE DEL ADC
volatile int16_t ADC_analog_value = 0;

//VARIABLE DE LA TEMPERATURA
int32_t temperature_value = 0;
int16_t temperature_value_incr = 0;
int16_t temperature_value_decr = 0;
int16_t set_temperature = 0;

//VARIABLE DEL DIGITO
uint8_t new_number;

//VARIABLES CAMBIO DE ESTADO
uint8_t button_on_off_state_flag=0;
uint8_t button_reset_state_flag = 0;

//*****************FUNCIONES DE ESTE CODIGO*************************//
void ports_init(void);
void display_show_parameter(int32_t temperature_value);
void display_show_word(char letter1, char letter2, char letter3, char letter4);
int32_t get_temperature(void);
long int get_resistance(double voltage);
double steinhart_hart(uint32_t resistance);


//********************FUNCIONES DE LAS LIBRERIAS********************//
// INT EXTERNAS
void INT_init(void);

// FUNCIONES DISPLAY
void display_show_number(uint8_t number);
void display_show_letter(char letter);
void display_7_seg_ports_init(void);

// FUNCIONES ADC
void ADC_init(void);
void ADC_on(void);

//******************************STATES******************************//
enum states
{
	state_idle,
	state_set,
	state_start,
	state_stop
} state;


//_____________________________MAIN__________________________________//

int main(void)
{
	cli();
  	ports_init(); 
	display_7_seg_ports_init ();
	commons_init();
	timer0_init();
	timer1_init();
	ADC_init();
	INT_init();
	sei();
	timer0_on();
	timer1_on();
	ADC_on();

    while (1)
    {
		switch(state)
		{
//*****************************STATE IDLE****************************//
			case state_idle:
			
			ACTUATOR_OFF;
			
			display_show_word('H','O','L','A');
			
			if (timer1_count > 3) {  //Esperar 3 seg
				timer1_count = 0;
				state = state_set;
			}
			else{
				state = state_idle;
			}
			break;
//****************************STATE SET******************************//
			case state_set:
			
			ACTUATOR_OFF;
			
			if(!(BUTTON_ON_OFF_PRESS)){button_on_off_state_flag=0;} //Evita cambio estado
			
			if(BUTTON_ON_OFF_PRESS && button_on_off_state_flag == 0) //Cambiar estado
			{
				button_on_off_state_flag = 1;
				set_temperature = temperature_value;
				state = state_start;
			}
			
			else if(BUTTON_RESET_PRESS){
				state = state_idle;
			}
			
			else{
				temperature_value = get_temperature(); //Obtener temperatura
				display_show_parameter(temperature_value);
				state = state_set;
			}
			break;
//***************************STATE START*****************************//
			case state_start:
			
			if(!(BUTTON_ON_OFF_PRESS)){button_on_off_state_flag=0;}
			if(!(BUTTON_RESET_PRESS)){button_reset_state_flag=0;}
			
			temperature_value = get_temperature();
			
			if(temperature_value >=(set_temperature-10) &&
			temperature_value<=(set_temperature+10)){
				display_show_word('S','E','T','-');
				ACTUATOR_OFF;
			}
			if(temperature_value>(set_temperature+10)){
				
				display_show_word('H','O','T','-');
				
				ACTUATOR_ON;
				
				if (timer1_count > 1) {  //Esperar 1 seg
					timer1_count = 0;
					ACTUATOR_OFF;
				}
			}
			if(temperature_value<(set_temperature-10)){
				display_show_word('C','O','L','D');
				ACTUATOR_OFF;
			}
			if(BUTTON_RESET_PRESS && button_reset_state_flag == 0){
				button_reset_state_flag=1;
				state = state_idle;
			}
			else if(BUTTON_ON_OFF_PRESS && button_on_off_state_flag == 0){
				button_on_off_state_flag = 1;
				state = state_stop;
			}
			else {
				state = state_start;
			}
			break;
//******************************STATE STOP***************************//
			case state_stop:
			
			if(!(BUTTON_ON_OFF_PRESS)){button_on_off_state_flag=0;}
			if(!(BUTTON_RESET_PRESS)){button_reset_state_flag=0;}
			
			//motor_stop();
			display_show_word('S','T','O','P');

			if(BUTTON_RESET_PRESS && button_reset_state_flag == 0)
			{
				button_reset_state_flag = 1;
				state = state_idle;
			}
			else if(BUTTON_ON_OFF_PRESS && button_on_off_state_flag == 0)
			{
				button_on_off_state_flag = 1;
				state = state_start;
			}
			else
			{
				state = state_stop;
			}
			break;
		} // Fin switch

    }// Fin while
}// Fin main

//*****************************FUNCIONES****************************//
// INICIALIZACION
void ports_init (void)
{
	//BOTONES
	BUTTONS_DDRX  &= ~(_BV(BUTTON_ON_OFF)|_BV(BUTTON_RESET)); //input
	BUTTONS_PORTX &= ~(_BV(BUTTON_ON_OFF)|_BV(BUTTON_RESET)); //pull down
	
	//BOTONES INCR Y DECR
	BUTTONS_INCDEC_DDRX &=~(_BV(BUTTON_INC)|_BV(BUTTON_DEC)); //input
	BUTTONS_INCDEC_PORTX |=(_BV(BUTTON_INC)|_BV(BUTTON_DEC)); //pull down
	
	//MOTOR
	DDRB |=  _BV(ACTUATOR);
	PORTB &= ~_BV(ACTUATOR);
}

// OBTENER RESISTENCIA

long int get_resistance(double voltage) {
	double VCC = 5.0; // Voltaje de referencia
	double R1 = 10000.0; // Resistencia (10k)
	return ((R1 * (VCC - voltage)) / voltage);
}

// ECUACION STEINHART
double steinhart_hart(uint32_t resistance)
{
	double temperature;
	/*
	Temperature (K) = 1 / (a + (b*ln(Rntc) + c.ln(Rntc)*ln(Rntc)*ln(Rntc)))

	a = 0.0011303
	b = 0.0002339
	c = 0.00000008863
	*/
	temperature = log(resistance);
	temperature = 1 / (0.0011303 + (0.0002339 * temperature) + (0.00000008863 * temperature * temperature * temperature));
	//Convert in Celsius
	temperature = temperature - 273;
	return temperature;
}

// OTBENER TEMPERATURA
int32_t get_temperature(void)
{
	double voltage = ADC_analog_value * 0.019607843; //R = 5 / (2^8 - 1) = 0.019607843
	long resistance = get_resistance(voltage);
	temperature_value = steinhart_hart(resistance);
	temperature_value += temperature_value_incr - temperature_value_decr;
	return temperature_value;
}



// MOSTRAR PALABRAS
void display_show_word(char letter1, char letter2, char letter3, char letter4)
{
	switch (timer0_count_display)
	{
		case 0:
		COMMONS_PORTX = 0b00011100; // millares
		display_show_letter(letter1);
		break;
		case 1:
		COMMONS_PORTX = 0b00101100; // centenas
		display_show_letter(letter2);
		break;
		case 2:
		COMMONS_PORTX = 0b00110100; // decenas
		display_show_letter(letter3);
		break;
		case 3:
		COMMONS_PORTX = 0b00111000; // unidades
		display_show_letter(letter4);
		break;
	}
}
/**
void display_show_word(char letter1, char letter2, char letter3, char letter4)
{
	switch (timer0_count_display)
	{
		case 0:
		COMMON_THOUSANDS_ON;
		COMMON_HUNDREDS_OFF;
		COMMON_TENS_OFF;
		COMMON_UNITS_OFF;
		//COMMONS_PORTX = 0b00011100; // millares
		display_show_letter(letter1);
		break;
		case 1:
		COMMON_THOUSANDS_OFF;
		COMMON_HUNDREDS_ON;
		COMMON_TENS_OFF;
		COMMON_UNITS_OFF;
		//COMMONS_PORTX = 0b00101100; // centenas
		display_show_letter(letter2);
		break;
		case 2:
		COMMON_THOUSANDS_OFF;
		COMMON_HUNDREDS_OFF;
		COMMON_TENS_ON;
		COMMON_UNITS_OFF;
		//COMMONS_PORTX = 0b00110100; // decenas
		display_show_letter(letter3);
		break;
		case 3:
		COMMON_THOUSANDS_OFF;
		COMMON_HUNDREDS_OFF;
		COMMON_TENS_OFF;
		COMMON_UNITS_ON;
		//COMMONS_PORTX = 0b00111000; // unidades
		display_show_letter(letter4);
		break;
	}
}
**/

// MOSTRAR GRADOS
void display_show_parameter(int32_t parameter_number)
{
	switch (timer0_count_display)
	{
		case 0:
		new_number = parameter_number/1000;
		COMMONS_PORTX = 0b00011100;
		display_show_number(new_number);  // millares
		break;
		case 1:
		new_number = (parameter_number%1000)/100;
		COMMONS_PORTX = 0b00101100;
		display_show_number(new_number); // centenas
		break;
		case 2:
		new_number = (parameter_number%100)/10;
		COMMONS_PORTX = 0b00110100;
		display_show_number(new_number); // decenas
		break;
		case 3:
		new_number = parameter_number%10;
		COMMONS_PORTX = 0b00111000;
		display_show_number(new_number);  // unidades
		break;
	}
}
/**
void display_show_parameter(int32_t parameter_number)
{
	switch (timer0_count_display)
	{		
		case 0:
		new_number = parameter_number/1000;
		COMMON_THOUSANDS_ON;
		COMMON_HUNDREDS_OFF;
		COMMON_TENS_OFF;
		COMMON_UNITS_OFF;
		//COMMONS_PORTX = 0b00011100;
		display_show_number(new_number);  // millares
		break;
		case 1:
		new_number = (parameter_number%1000)/100;
		COMMON_THOUSANDS_OFF;
		COMMON_HUNDREDS_ON;
		COMMON_TENS_OFF;
		COMMON_UNITS_OFF;
		//COMMONS_PORTX = 0b00101100; 
		display_show_number(new_number); // centenas
		break;
		case 2:
		new_number = (parameter_number%100)/10;
		COMMON_THOUSANDS_OFF;
		COMMON_HUNDREDS_OFF;
		COMMON_TENS_ON;
		COMMON_UNITS_OFF;
		//COMMONS_PORTX = 0b00110100; 
		display_show_number(new_number); // decenas
		break;
		case 3:
		new_number = parameter_number%10;
		COMMON_THOUSANDS_OFF;
		COMMON_HUNDREDS_OFF;
		COMMON_TENS_OFF;
		COMMON_UNITS_ON;
		//COMMONS_PORTX = 0b00111000;
		display_show_number(new_number);  // unidades
		break;
	}
}
**/


/**
void display_show_parameter(int32_t parameter_number) 
{
	uint8_t digit_value = (parameter_number / (int32_t)pow(10, 3 - timer0_count_display)) % 10;
	switch (timer0_count_display) {
		case 0:
		COMMON_THOUSANDS_ON;
		COMMON_HUNDREDS_OFF;
		COMMON_TENS_OFF;
		COMMON_UNITS_OFF;
		break;
		case 1: 
		COMMON_THOUSANDS_OFF;
		COMMON_HUNDREDS_ON;
		COMMON_TENS_OFF;
		COMMON_UNITS_OFF;
		break;
		case 2: 
		COMMON_THOUSANDS_OFF;
		COMMON_HUNDREDS_OFF;
		COMMON_TENS_ON;
		COMMON_UNITS_OFF;
		break;
		case 3:
		COMMON_THOUSANDS_OFF;
		COMMON_HUNDREDS_OFF;
		COMMON_TENS_OFF;
		COMMON_UNITS_ON;
		break;
	}
	display_show_number(digit_value);
}
**/




//*****************VECTORES DE INTERRUPCION**************************//

//TIMER0
ISR (TIMER0_COMPA_vect)
{
	timer0_count_display++;
	if (timer0_count_display > 4)
	{
		timer0_count_display = 0;
	}
}


//TIMER1
ISR (TIMER1_COMPA_vect)
{
	timer1_count++;
}


//VALOR ADC
ISR (ADC_vect)
{
	ADC_analog_value = ADCH;
}

// INTERRUPCION INT0
ISR (INT0_vect)
{
	temperature_value_incr++;
}
// INTERRUPCION INT1
ISR (INT1_vect)
{
	temperature_value_decr++;
}