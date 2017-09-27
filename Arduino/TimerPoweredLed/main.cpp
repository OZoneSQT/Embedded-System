//
//
//

#include "main.h"

int main(void)
{
   // initialize the serial communication:
   Serial.begin(115200);
   int serial_max_write = Serial.availableForWrite();

   /* set pin D5 for output internal LED*/
   DDRB |= (OUTPUT << PB1);

   TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);  //clear on compare match, continue count to OxFF
   TCCR0B |= (1 << CS02) | (1 << CS00);// prescale counter by 1024
   TCNT0 = 0;
   DDRD |= (255);
   OCR0A = 255;  //initial compare match value

   Serial.println("Launching...");
   Serial.flush();

   byte brightness;

   while (1)
   {
      if (Serial.available() > 0)
      {
         Serial.println("now reading next char...");
         Serial.flush();

         // read the most recent byte (which will be from 0 to 255):
         brightness = Serial.read();

         // print the value
         Serial.print("I received: ");
         Serial.println(brightness, DEC);
         Serial.flush();

         OCR0A = brightness;
      }
   }

   return 0;
}
