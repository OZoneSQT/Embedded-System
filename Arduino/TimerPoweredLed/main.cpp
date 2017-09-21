// 
// 
// 

#include "main.h"
#include <util/delay.h>
#include <HardwareSerial.h>

int main(void)
{
	Serial.begin(115200);

	/* set pin D5 for output internal LED*/
	DDRB |= (OUTPUT << PB5);

	while (1)
	{
		_delay_ms(100);
		Serial.println("tick");
	}

	return 0;
}
