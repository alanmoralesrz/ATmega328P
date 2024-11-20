/*
 * timers.c
 *
 * Created: 07/05/2023 04:35:11 p. m.
 *  Author: Dario 24
 */ 

#include "timers.h"

//------------------TIMER 0 -------------------------------//

void timer0_init(void)
{
	// MODO CTC
	TCCR0A &= ~_BV(WGM00); 
	TCCR0A |=  _BV(WGM01);
	TCCR0B &= ~_BV(WGM02);

	// TOP 
	OCR0A = 20; 

	// ACTIVAR TIMSK
	TIMSK0 |= _BV(OCIE0A); 
}

void timer0_on() 
{
	TCNT0 = 0; // reiniciar registro que lleva el conteo 

	//PRESCALER 1024
	TCCR0B |=  _BV(CS00); 
	TCCR0B &= ~_BV(CS01); 
	TCCR0B |=  _BV(CS02); 
}

void timer0_off()
{
	TCCR0B &= ~_BV(CS00);
	TCCR0B &= ~_BV(CS01); 
	TCCR0B &= ~_BV(CS02); 
}


//------------------TIMER 1 -------------------------------//


void timer1_init(void)
{
	// MODO CTC
	TCCR1A &= ~_BV(WGM10);
	TCCR1A &= ~_BV(WGM11);
	TCCR1B |=  _BV(WGM12);
	TCCR1B &= ~_BV(WGM13);
	
	// Para 1024: 15623:1SEG, 1562:0.1 SEG=100ms, 156:0.01SEG= 10ms, 15:0.001s=1ms, 1: 0.1ms
	// Prescaler64 125 = 500us
	OCR1A = 15623;

	// ACTIVAR TIMSK
	TIMSK1 |= _BV(OCIE1A);
}

void timer1_on()
{
	TCNT1 = 0; // reiniciar registro que lleva el conteo

	//PRESCALER 1024
	TCCR1B |= _BV(CS10);
	TCCR1B &=~_BV(CS11);
	TCCR1B|=  _BV(CS12);
}

void timer1_off()
{
	TCCR1B &= ~_BV(CS10);
	TCCR1B &= ~_BV(CS11);
	TCCR1B &= ~_BV(CS12);
}


/*
//------------------TIMER 2 -------------------------------//

void timer2_init(void)
{
	// MODO CTC
	TCCR2A |= _BV(WGM21);
	TCCR2A &= ~_BV(WGM20);
	TCCR2B &= ~_BV(WGM22);

	// TOP
	OCR2A = 15623;

	// ACTIVAR TIMSK
	TIMSK2 |= _BV(OCIE2A);
}

void timer2_on()
{
	TCNT2 = 0; // reiniciar registro que lleva el conteo

	// PRESCALER 1024
	TCCR2B |= _BV(CS20);
	TCCR2B &= ~_BV(CS21);
	TCCR2B |= _BV(CS22);
}

void timer2_off()
{
	TCCR2B &= ~_BV(CS20);
	TCCR2B &= ~_BV(CS21);
	TCCR2B &= ~_BV(CS22);
}

*/