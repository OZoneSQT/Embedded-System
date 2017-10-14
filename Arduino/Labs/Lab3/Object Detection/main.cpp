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
   sei();

   // Setting PWM output pin
   TCCR2A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);  //clear on compare match, continue count to OxFF
   TCCR2B |= (1 << CS02) | (1 << CS00); // prescale counter by 1024
   OCR2A = 0;  // initial compare match value - LED off

   ADC_setup();
   Serial.begin(115200);

   while (true)
   {
      ADCSRA |= (1 << ADSC); // Start Conversion
      while (!(ADCSRA & (1 << ADIF))) {} // wait for ADIF to go to 0, indicating conversion complete.
      ADCSRA |= (1 << ADIF); // Reset ADIF to 1 for the next conversion
      Serial.println(ADC); // Print ADC conversion value

      if (ADC <= 350)
      {
         DDRB &= (INPUT << PB3);
         OCR2A = 0;                       // less than 350
      }
      else if (ADC <= 500)
      {
         DDRB |= (OUTPUT << PB3);
         OCR2A = 26;                      // 351 to 500
      }
      else if (ADC <= 650)
      {
         DDRB |= (OUTPUT << PB3);
         OCR2A = 128;                     // 501 to 650
      }
      else
      {
         DDRB |= (OUTPUT << PB3);
         OCR2A = 255;
      }

      _delay_ms(50);
   }
}
