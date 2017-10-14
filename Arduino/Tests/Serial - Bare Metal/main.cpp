//
//
//

#include "main.h"

int main(void)
{
   sei();
   Serial.begin(115200);

   while (1)
   {
      Serial.println("\nenter an input");
      while(!Serial.available()) {}
      Serial.write(Serial.read());
   }

   return 0;
}
