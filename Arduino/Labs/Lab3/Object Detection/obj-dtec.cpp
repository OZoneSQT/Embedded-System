//
//
//

#include "main.h"

void ADC_setup()
{
   // data sheed 24.9.1-2
   ADMUX |= ADC4D | (1 << REFS0);               // Vcc ( 5v) conversion scale
   ADCSRA |= (1 << ADEN) | (1 << ADPS2);        // enable with prescalar  at 16 (65kHz conversion clock speed)
}

void PWM_setup()
{
   // Setting PWM output pin
   TCCR2A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);  //clear on compare match, continue count to OxFF
   TCCR2B |= (1 << CS02) | (1 << CS00);         // prescale counter by 1024
   OCR2A = 0;                                   // initial compare match value - LED off
}

int main(void)
{
   sei();

   PWM_setup();
   ADC_setup();
   Serial.begin(115200);

   while (true)
   {
      ADCSRA |= (1 << ADSC);                    // Start Conversion
      while (!(ADCSRA & (1 << ADIF))) {}        // wait for ADIF to go to 0, indicating conversion complete.
      ADCSRA |= (1 << ADIF);                    // Reset ADIF to 1 for the next conversion
      Serial.println(ADC);                      // Print ADC conversion value

      if (ADC >= 400)                           // above 400
      {
         DDRB |= (OUTPUT << PB3);               // turn on LED
         OCR2A = 128;                           // set brightness value

         DDRB |= (OUTPUT << PB2);               // activate sender
         PORTB |= (HIGH << PB2);                // send signal to rcvr
      }
      else
      {
         DDRB &= (INPUT << PB3);                // turn off LED
         DDRB &= (INPUT << PB2);                // turn off signal
      }

      _delay_ms(50);
   }
}
