// 
// 
// 

#include "main.h"
#include <util/delay.h>

int main()
{
	DDRB |= (1 << PB5);
	while (1)
	{
		// turn on LED
		PORTB |= (1 << PB5);
		_delay_ms(100);

		//turn off LED
		PORTB &= (0 << PB5);
		_delay_ms(100);
	}
}
