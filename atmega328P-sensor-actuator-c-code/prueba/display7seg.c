/*
 * display.c
 *
 * Created: 07/05/2023 04:18:24 p. m.
 *  Author: Dario 24
 */ 

//LIBRERIA DISPLAY7SEG.H
#include "display7seg.h"

//**********************DEFINICION DE FUNCIONES***************************//

// INICIALIZAR DISPLAY 7 SEG 
void display_7_seg_ports_init (void)
{
	DDRD |=   (_BV(D) | _BV(E) | _BV(F) | _BV(G)); // Outputs 7SEG
	DDRB |=   (_BV(A) | _BV(B) | _BV(C)); 
	PORTD &= ~(_BV(D) | _BV(E) | _BV(F) |_BV(G)); // 7SEG apagado
	PORTB &= ~(_BV(A) | _BV(B) | _BV(C)); 
}

// INICIALIZAR COMUNES
void commons_init(void)
{
	COMMONS_DDRX |= (_BV(COMMON_UNITS) | _BV(COMMON_TENS));
	COMMONS_DDRX |= (_BV(COMMON_HUNDREDS) | _BV(COMMON_THOUSANDS));
	
	COMMONS_PORTX |= (_BV(COMMON_UNITS) | _BV(COMMON_TENS));
	COMMONS_PORTX |= (_BV(COMMON_HUNDREDS) | _BV(COMMON_THOUSANDS));
	
}

// MOSTRAR LETRAS
void display_show_letter(char letter)
{
	switch(letter)
	{
		break;
		case 'A':
		A_On;
		B_On;
		C_On;
		D_Off;
		E_On;
		F_On;
		G_On;
		break;
		case 'B':
		A_Off;
		B_Off;
		C_On;
		D_On;
		E_On;
		F_On;
		G_On;
		break;
		case 'C':
		A_On;
		B_Off;
		C_Off;
		D_Off;
		E_On;
		F_On;
		G_Off;
		break;
		case 'D':
		A_Off;
		B_On;
		C_On;
		D_On;
		E_On;
		F_Off;
		G_On;
		break;
		case 'E':
		A_On;
		B_Off;
		C_Off;
		D_On;
		E_On;
		F_On;
		G_On;
		break;
		case 'G':
		A_On;
		B_On;
		C_On;
		D_On;
		E_Off;
		F_On;
		G_On;
		break;
		case 'H':
		A_Off;
		B_On;
		C_On;
		D_Off;
		E_On;
		F_On;
		G_On;
		break;
		case 'J':
		A_Off;
		B_On;
		C_On;
		D_On;
		E_On;
		F_Off;
		G_Off;
		break;
		case 'L':
		A_Off;
		B_Off;
		C_Off;
		D_On;
		E_On;
		F_On;
		G_Off;
		break;
		case 'O':
		A_On;
		B_On;
		C_On;
		D_On;
		E_On;
		F_On;
		G_Off;
		break;
		case 'P':
		A_On;
		B_On;
		C_Off;
		D_Off;
		E_On;
		F_On;
		G_On;
		break;
		case 'S':
		A_On;
		B_Off;
		C_On;
		D_On;
		E_Off;
		F_On;
		G_On;
		break;
		case 'T':
		A_Off;
		B_Off;
		C_Off;
		D_On;
		E_On;
		F_On;
		G_On;
		break;
		case '-':
		A_Off;
		B_Off;
		C_Off;
		D_Off;
		E_Off;
		F_Off;
		G_Off;
		break;
	}
}

// MOSTRAR NUMEROS
void display_show_number(uint8_t number)
{
	switch (number)
	{
		case 0:
		A_On;
		B_On;
		C_On;
		D_On;
		E_On;
		F_On;
		G_Off;
		break;
		case 1:
		A_Off;
		B_On;
		C_On;
		D_Off;
		E_Off;
		F_Off;
		G_Off;
		break;
		case 2:
		A_On;
		B_On;
		C_Off;
		D_On;
		E_On;
		F_Off;
		G_On;
		break;
		case 3:
		A_On;
		B_On;
		C_On;
		D_On;
		E_Off;
		F_Off;
		G_On;
		break;
		case 4:
		A_Off;
		B_On;
		C_On;
		D_Off;
		E_Off;
		F_On;
		G_On;
		break;
		case 5:
		A_On;
		B_Off;
		C_On;
		D_On;
		E_Off;
		F_On;
		G_On;
		break;
		case 6:
		A_On;
		B_Off;
		C_On;
		D_On;
		E_On;
		F_On;
		G_On;
		break;
		case 7:
		A_On;
		B_On;
		C_On;
		D_Off;
		E_Off;
		F_Off;
		G_Off;
		break;
		case 8:
		A_On;
		B_On;
		C_On;
		D_On;
		E_On;
		F_On;
		G_On;
		break;
		case 9:
		A_On;
		B_On;
		C_On;
		D_On;
		E_Off;
		F_On;
		G_On;
		break;
	}
}
