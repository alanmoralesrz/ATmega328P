/*
 * display.h
 *
 * Created: 07/05/2023 04:17:49 p. m.
 *  Author: Dario 24
 */ 


#ifndef DISPLAY7SEG_H_
#define DISPLAY7SEG_H_
#include <avr/io.h>

// DISPLAY 7 SEG MACROS
#define SEG1 PORTD
#define SEG2 PORTB
#define A PORTB5
#define B PORTB4
#define C PORTB0
#define D PORTD7
#define E PORTD6
#define F PORTD5
#define G PORTD4
#define A_On SEG2 |= _BV(A) // encender segmento
#define B_On SEG2 |= _BV(B)
#define C_On SEG2 |= _BV(C)
#define D_On SEG1 |= _BV(D)
#define E_On SEG1 |= _BV(E)
#define F_On SEG1 |= _BV(F)
#define G_On SEG1 |= _BV(G)
#define A_Off SEG2 &= ~_BV(A) // apagar segmento
#define B_Off SEG2 &= ~_BV(B)
#define C_Off SEG2 &= ~_BV(C)
#define D_Off SEG1 &= ~_BV(D)
#define E_Off SEG1 &= ~_BV(E)
#define F_Off SEG1 &= ~_BV(F)
#define G_Off SEG1 &= ~_BV(G)

//COMUNES OUTPUTS
#define COMMONS_DDRX     DDRC
#define COMMONS_PORTX    PORTC
#define COMMON_UNITS     PORTC2
#define COMMON_TENS      PORTC3
#define COMMON_HUNDREDS  PORTC4
#define COMMON_THOUSANDS PORTC5
#define COMMON_UNITS_OFF	 COMMONS_PORTX |= _BV(COMMON_UNITS) //si mandas 1, se apagan los comunes
#define COMMON_TENS_OFF		 COMMONS_PORTX |= _BV(COMMON_TENS)
#define COMMON_HUNDREDS_OFF  COMMONS_PORTX |= _BV(COMMON_HUNDREDS)
#define COMMON_THOUSANDS_OFF COMMONS_PORTX |= _BV(COMMON_THOUSANDS)
#define COMMON_UNITS_ON		 COMMONS_PORTX &= ~_BV(COMMON_UNITS) //encender comunes
#define COMMON_TENS_ON		 COMMONS_PORTX &= ~_BV(COMMON_TENS)
#define COMMON_HUNDREDS_ON   COMMONS_PORTX &= ~_BV(COMMON_HUNDREDS)
#define COMMON_THOUSANDS_ON  COMMONS_PORTX &= ~_BV(COMMON_THOUSANDS) 

// DISPLAY 7 SEG FUNCTIONS
void display_show_letter(char letter);
void display_show_number(uint8_t number);
void display_7_seg_ports_init (void);
void commons_init(void);

#endif /* DISPLAY7SEG_H_ */