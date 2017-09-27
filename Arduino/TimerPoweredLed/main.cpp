//
//
//

#include "main.h"

int main(void)
{
   /* set pin D5 for output internal LED*/
   DDRB |= (OUTPUT << PB1);

   TCCR1A |= (1 << COM1A0); //toggle on compare match
   TCCR1B |= (1 << CS12) | (1 << CS10); // prescale by 1024
   TCNT1 = 0;

   while (1)
   {

   }

   return 0;
}
