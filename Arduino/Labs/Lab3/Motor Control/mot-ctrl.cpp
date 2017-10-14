//
//
//

#include "main.h"

ISR(INT0_vect)
{
      cli();                                    // Disable interrupts in case of another interrupt

      Serial.println("Triggered...");
      PORTC |= (HIGH << PC3);                   // activate LED
      _delay_ms(500);

      sei();                                    // Re-enable interrupts
}

int main(void)
{
   EICRA |= (1 << ISC01) | (1 << ISC00);         // trigger on rising edge
   EIMSK |= (1 << INT0);                        // active external pin int0

   DDRC |= (OUTPUT << PC3);                     // listen for signal

   Serial.begin(115200);

   sei();                                       // enable interrupts
   while (1)
   {
      PORTC &= (LOW << PC3);                    // turn off LED
      _delay_ms(50);
   }

   return 0;
}
