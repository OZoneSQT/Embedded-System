//
//
//

#define BAUD 115200
#include <util/setbaud.h>
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

/// Configuring UART Communication in order to send data to the serial monitor
void Serial_setup(void)
{
   UBRR0H = UBRRH_VALUE;
   UBRR0L = UBRRL_VALUE;

#if USE_2X
   UCSR0A |= _BV(U2X0);
#else
   UCSR0A &= ~(_BV(U2X0));
#endif

   UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);          // 8-bit data
   UCSR0B = _BV(RXEN0) | _BV(TXEN0);            // Enable RX and TX
}

/// Sends 1 byte of data to the serial Monitor
/// Waits for USART Data Register to be empty by checking if the UDRE flag is set
void Serial_write(char c)
{
   loop_until_bit_is_set(UCSR0A, UDRE0);        // Wait until data register empty
   UDR0 = c;
}

/// Recieves  1 byte of data from the serial Monitor
/// Waits for UDR0 Data Register to have data that can be read by checking the RXC0 flag
char Serial_read(void)
{
   loop_until_bit_is_set(UCSR0A, RXC0);         // Wait until data exists.
   return UDR0;
}

/// Prints string
void Serial_print(const char *s)
{
   while (*s)                                   // loop through entire string
   {
      Serial_write(*s);
      s++;
   }
}

/// Prints string with new line
void Serial_println(const char *s)
{
   Serial_print(s);
   Serial_write('\n');
}

ISR(INT0_vect)
{
      cli();                                    // Disable interrupts in case of another interrupt

      PORTC ^= (HIGH << PC3);                   // toggle LED (drive)
      PORTC ^= (HIGH << PC4);                   // toggle LED (reverse)
      _delay_ms(150);

      sei();                                    // Re-enable interrupts

      char rcv = Serial_read();                 // read instruction
      Serial_write(rcv);                        // echo confirmation
}

int main(void)
{
   Serial_setup();

   sei();                                       // enable interrupts

   EICRA |= (1 << ISC01) | (1 << ISC00);        // trigger on rising edge
   EIMSK |= (1 << INT0);                        // active external pin int0

   DDRC |= (OUTPUT << PC3);                     // channel for LED (drive)
   DDRC |= (OUTPUT << PC4);                     // channel for LED (reverse)

   PORTC |= (HIGH << PC3);                      // activate LED (drive)
   PORTC &= (LOW << PC4);                       // turn off LED (reverse)

   while (1)
   {
      _delay_ms(50);
   }

   return 0;
}
