// 
// 
// 

#include "main.h"
#include <util/delay.h>

int main()
{
	DDRC |= (1 << PC0); // output
	DDRB &= (0 << PB5); // LED to input

	while (1)
	{
		// turn on LED
		PORTC |= (1 << PC0);
		_delay_ms(100);

		//turn off LED
		PORTC &= (0 << PC0);
		_delay_ms(100);
	}
}
