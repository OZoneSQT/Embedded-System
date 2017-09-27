# Lab2 Report
This lab consisted of three parts, LED brightness controlled by User (throught PWM), Oout putting the values from an IR sensor, and lastly controlling the brightness of the LED using the IR sensor.

> To best view this [document](https://github.com/prince-chrismc/Embedded-System/blob/master/Arduino/TimerPoweredLed/Report.md), use the link provided

As of 27/09/2017 at 5:07pm only part 1 is code complete, see [Discussion/Conclusion](#Discussion/Conclusion) for details.

### Table of Contents
0. [Contributors](#Contributors)
1. [Introduction](#Introduction)
2. [Resources](#Resources)
3. [Software Resources](#Software-Resources)
4. [Program Snipets](#Program-Snipets)
5. [Reference Code Common](#Reference-Code-Common)
6. [Discussion/Conclusion](#Discussion/Conclusion)

## Contributors
**Student** | **ID**
:---:| ---
Christopher McArthur | `40004257`

## Introduction
- Problem Statement: Using arduino and coding in 'bare metal' (c programming) create a 4-bt counter that displays the binary value of the counter on a set of LEDs. the solution should take in a count debouncing effect.
- Abbreviations and Acronyms
 - LED == Light Emiting Diode
 - DDRx, PBn, etc... Registers names
 - OCR == output compare register
 - IR == infra red
 - ADC == analog to digital conversion
 - PWM == pulse with modulation
 
## Resources 
- Hardware Resources
 - Arduino Nano
 - LEDs
 - Push Button
 - Resistors
 - Jumper Wires
 - IR Sensor
- Hardware Setup
 - I have not installed Fritzing

## Software Resources
- Software setup
 - IDE is Visual Studio 2017 Enterprise
 - Compilers are the avr-gcc for windows
 - Visual studio has an extension called 'Visual Micro' which handles everything from compiling to upload (it just needs to be configured like the Arduino IDE)
 
## Program Snipets
- timer 2 setup code
```c
TCCR2A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);  //clear on compare match, continue count to OxFF
TCCR2B |= (1 << CS02) | (1 << CS00); // prescale counter by 1024
DDRB |= (255); // turn all of PB's to output
OCR2A = 255;  //initial compare match value - max brightness
```
- loop
```c
if (Serial.available() > 0)
{
   // read the most recent byte (which will be from 0 to 255):
   brightness = Serial.read();

   // print the value
   Serial.print("I received: ");
   Serial.println(brightness, DEC);
   Serial.flush(); // hangs otherwise

   OCR2A = brightness; // set to user input
}
```

## Reference Code Common
- the basic Arduino bare metal IO.h for access to pins and registers and basic definitions
- HardwareSerial.h for serial communitcation

## Discussion/Conclusion
- Sadly I wasted too much time on trying to get the `Serial.read()` to work; which never succeed so I did not hav time to complete them before the lab was due. I will submit the complete version tomorrow 28/09/17 most likely