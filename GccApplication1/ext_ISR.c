/*
 * ext_ISR.c
 *
 * Created: 26/05/2023 03:55:21 p. m.
 *  Author: Dario 24
 */

#include "ext_ISR.h"
/*
void INT_init(void)
{
	EICRA &= ~(_BV(ISC00) | _BV(ISC01)); // INT0 = LOW LEVEL
	EIMSK |= _BV(INT0); // INT0 activado

	EICRA |= _BV(ISC10); // INT1 = FALLING EDGE
	EICRA &= ~_BV(ISC11); // INT1 = FALLING EDGE
	EIMSK |= _BV(INT1); // INT1 activado
}
*/

void INT_init(void)
{
	EICRA |= (_BV(ISC00) | _BV(ISC01)); // INT0 = HIGH LEVEL
	EIMSK |= _BV(INT0); // INT0 activado

	EICRA |= _BV(ISC10); // INT1 = 
	EICRA |= _BV(ISC11); // INT1 = 
	EIMSK |= _BV(INT1); // INT1 activado
}
