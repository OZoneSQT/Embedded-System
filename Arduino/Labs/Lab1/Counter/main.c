//
//
//

#include "main.h"
#include <util/delay.h>

int g_bPressed = 0;

int main(void)
{
   /* set pin D2-5 for output*/
   DDRD |= (OUTPUT << PD2);
   DDRD |= (OUTPUT << PD3);
   DDRD |= (OUTPUT << PD4);
   DDRD |= (OUTPUT << PD5);

   /* set B4 for inout with pullup */
   DDRB &= (INPUT << PB4);
   PORTB &= (LOW << PB4);

   byte iCounter = 0;

   while (1)
   {
      if (isButtonPressed())
      {
         displayCounter(++iCounter);
         _delay_ms(100);
      }
   }

   return 0;
}


int isButtonPressed()
{
   if (PINB&(HIGH << PB4) && !g_bPressed)
   {
      g_bPressed = 1;
      return 1;
   }
   g_bPressed = 0;
   return 0;
}


void displayCounter(int n)
{
   if (bitRead(n, 0) == 1)
      PORTD |= (HIGH << PD2);
   else
      PORTD &= (LOW << PD2);

   if (bitRead(n, 1) == 1)
      PORTD |= (HIGH << PD3);
   else
      PORTD &= (LOW << PD3);

   if (bitRead(n, 2) == 1)
      PORTD |= (HIGH << PD4);
   else
      PORTD &= (LOW << PD4);

   if (bitRead(n, 3) == 1)
      PORTD |= (HIGH << PD5);
   else
      PORTD &= (LOW << PD5);
}
