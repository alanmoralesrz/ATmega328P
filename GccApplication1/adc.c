/*
 * adc.c
 *
 * Created: 14/05/2023 12:07:39 p. m.
 *  Author: Dario 24
 */ 
#include "adc.h"

void ADC_init(void)
{
	// PIN AVCC COMO REFERENCIA:
	ADMUX &= ~_BV(REFS1);
	ADMUX |=  _BV(REFS0);
	
	// AJUSTADO A 8 BITS
	ADMUX |= _BV(ADLAR);
	
	// LEER PIN ADC0
	ADMUX &= ~_BV(MUX3);
	ADMUX &= ~_BV(MUX2);
	ADMUX &= ~_BV(MUX1);
	ADMUX &= ~_BV(MUX0);
	
	// ACTIVAR FREERUNING
	ADCSRA |= _BV(ADATE); // Auto Trigger Enable
	
	// ADC INTERRUPT ENABLE
	ADCSRA |= _BV(ADIE);
	
	// PRESCALER
	//16MHz/128= 125KHz ADC
	ADCSRA |= _BV(ADPS2);
	ADCSRA |= _BV(ADPS1);
	ADCSRA |= _BV(ADPS0);
}

void ADC_on(void)
{
	ADCSRA |= _BV(ADEN); // encender ADC
	ADCSRA |= _BV(ADSC); // iniciar conversion
}
