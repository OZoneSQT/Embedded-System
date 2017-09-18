#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
 
//bool g_bPressed = false;
 
int main (void)
{
 /* set pin C2-5 of PORTB for output*/
 DDRD |= (1<<PD2);
 DDRD |= (1<<PD3);
 DDRD |= (1<<PD4);
 DDRD |= (1<<PD5);

 int iCounter = 0;
 
 while(1) 
 {
   _delay_ms(50);
  if(isButtonPressed())
    displayCounter(++iCounter);
 }

 return 0;
}


bool isButtonPressed()
{
  if(PINB&(1<<PB4) /*&& !g_bPressed*/ )
  {
    //g_bPressed = true;
    return true;
  }
  //g_bPressed = false;
  return false;
}


void displayCounter(int n)
{
  (n&0b0001) ? PORTD |= (1<<PD2) : PORTD &= (0<<PD2);
  (n&0b0010) ? PORTD |= (1<<PD3) : PORTD &= (0<<PD3);
  (n&0b0100) ? PORTD |= (1<<PD4) : PORTD &= (0<<PD4);
  (n&0b1000) ? PORTD |= (1<<PD5) : PORTD &= (0<<PD5);
}
