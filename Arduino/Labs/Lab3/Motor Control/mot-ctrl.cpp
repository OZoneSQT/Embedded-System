//
//
//

#include "main.h"

ISR(INT0_vect)
{
      // Disable interrupts in case of another interrupt
      cli();
      // My code goes here

      // Re-enable interrupts
      sei();
}


int main(void)
{
   EICRA |= (1 << ISC01) | (1 << ISC00);
   EIMSK |= (1 << INT0);

   sei();
   while (1)
   {

   }

   return 0;
}
