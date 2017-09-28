//
//
//

#include "main.h"

int main(void)
{
   // initialize the serial communication:
   Serial.begin(115200);
   int serial_max_write = Serial.availableForWrite();

   TCCR2A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);  //clear on compare match, continue count to OxFF
   TCCR2B |= (1 << CS02) | (1 << CS00); // prescale counter by 1024
   DDRB |= (255); // turn all of PB's to output
   OCR2A = 255;  //initial compare match value - max brightness

#if defined(USBCON)
   USBDevice.attach();
#endif

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

         OCR2A = brightness;
         if (serialEventRun) serialEventRun();
      }
   }

   return 0;
}
