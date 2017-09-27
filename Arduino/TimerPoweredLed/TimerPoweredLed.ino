/*
Dimmer

Demonstrates sending data from the computer to the Arduino board, in this case
to control the brightness of an LED. The data is sent in individual bytes,
each of which ranges from 0 to 255. Arduino reads these bytes and uses them to
set the brightness of the LED.

The circuit:
- LED attached from digital pin 9 to ground.
- Serial connection to Processing, Max/MSP, or another serial application

created 2006
by David A. Mellis
modified 30 Aug 2011
by Tom Igoe and Scott Fitzgerald

This example code is in the public domain.

http://www.arduino.cc/en/Tutorial/Dimmer
*/

/*
THIS CODE HAS BEEN MODIFIED TO BETTER SUIT MY TEST CASE
Chris Mc 27/09/17
*/

const int ledPinA = 6;      // the pin that the LED is attached to
const int ledPinB = 7;      // max brightness

void setup() {
   // initialize the serial communication:
   Serial.begin(115200);
   // initialize the ledPin as an output:
   pinMode(ledPinA, OUTPUT);
   pinMode(ledPinB, OUTPUT);
   analogWrite(ledPinB, 255);
}

void loop() {
   byte brightness;

   // check if data has been sent from the computer:
   if (Serial.available()) {
      // read the most recent byte (which will be from 0 to 255):
      brightness = Serial.read();

      // print the value
      Serial.print("I received: ");
      Serial.println(brightness, DEC);

      // set the brightness of the LED:
      analogWrite(ledPinA, brightness);
   }
}