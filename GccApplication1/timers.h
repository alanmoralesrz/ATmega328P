/*
 * timers.h
 *
 * Created: 07/05/2023 04:35:20 p. m.
 *  Author: Dario 24
 */ 

#ifndef TIMERS_H_
#define TIMERS_H_
#include <avr/io.h>

void timer0_init(void); //inicializar timers
void timer1_init(void);
void timer0_on();   //encender timers
void timer1_on();
void timer0_off();  //apagar timers
void timer1_off();
void timer2_init();
void timer2_on();
void timer2_off();

#endif /* TIMERS_H_ */