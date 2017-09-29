//
//
//

#include "main.h"

void ADC_setup()
{
   // data sheed 24.9.1-2
   ADMUX |= ADC4D | (1 << REFS0); // Vcc ( 5v) conversion scale
   ADCSRA |= (1 << ADEN) | (1 << ADPS2); // enable with prescalar  at 16 (65kHz conversion clock speed)
}

int main(void)
{
   ADC_setup();
   Serial.begin(115200);

   while (1)
   {
      ADCSRA |= (1 << ADSC); // Start Conversion
      while (!(ADCSRA & (1 << ADIF))) {} // wait for ADIF to go to 0, indicating conversion complete.
      ADCSRA |= (1 << ADIF); // Reset ADIF to 1 for the next conversion
      Serial.println(ADC); // Print ADC conversion value
      _delay_ms(50);
   }
}
