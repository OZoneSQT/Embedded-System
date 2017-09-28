# Lab2 Report
This lab consisted of three parts, LED brightness controlled by User (throught PWM), Oout putting the values from an IR sensor, and lastly controlling the brightness of the LED using the IR sensor.

> To best view this [document](https://github.com/prince-chrismc/Embedded-System/blob/master/Arduino/Labs/Lab2/README.md), use the link provided

As of 27/09/2017 at 5:07pm only part 1 is code complete, see [discussion](#Issues-with-Serial) for details.

### Table of Contents
1. [Contributors](#Contributors)
2. [Introduction](#Introduction)
3. [Resources](#Resources)
4. [Software Resources](#Software-Resources)
5. [Program Snipets](#Program-Snipets)
6. [Reference Code Common](#Reference-Code-Common)
7. [Discussion/Conclusion](#Discussion/Conclusion)

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
  - Compilers are the avr-gcc/avr-g++ for windows
  - Visual studio has an extension called [Visual Micro](http://www.visualmicro.com/) which handles everything from compiling to upload (it just needs to be configured similar to the Arduino IDE)
 
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
- To be completed

### Issues with Serial
Having first proto-typed the Lab in arduino the transition to bare metal was not clean cut. Previously all my work for bare metal was in in C-code which is how I started this lab. The issue is that the arduino library is *C++* and the `Serial` object produced compilation errors; this actually took an hour of research because the the errors from the avr-gcc compiler are under equiped. The fix was to rename my file from .c to .cpp such that my visual studio extension would use the correct compiler.

With everything now compiling, running the code didnt even successfully output anything. It would hang after two bytes and never complete printing. Turns out after investigating there's a `Serial.flush()`, [code here](https://github.com/arduino/Arduino/blob/0c325b4ff6118be331dfb27db06a6596bb6ebde8/hardware/arduino/avr/cores/arduino/HardwareSerial.cpp#L193), whichs waits till the buffer is emptied but maybe helps in sending too. Either way adding this to each of my prints helped.

Now with lovely debug prints fully functional (code no longer hanging), I tried to pass information from the Serial dialogue to the Nano. This doesnt work, my... 
```c 
if(Serial.available() > 0) { /* ... blah blah ... */} 
```
...was never true. Going back and for from arduino to bare metal, I tried testing `Serial.read()` without having printed anything, did have an effect, and a slue of other tweaks and modifications to never obtain a result. I was so faustered at why the arduino was not Rx anything I found this [tutorial](https://blog.manash.me/serial-communication-with-an-arduino-using-c-on-windows-d08710186498) for doing Serial communication from C++ windows to arduino, and use it to manual check what was written. Guess what? It was written successfully. 

 Doing a `git reset --hard` to have both the arduino and bare metal the extact same and compiled both. The arduino was 1818 bytes and the bare metal was 1437; clearly the bare metal compilation is missing a key detail. Since all C/C++ programs have a `main()` function I set out to find it, took a while but again it was on [github](https://github.com/arduino/Arduino/blob/0c325b4ff6118be331dfb27db06a6596bb6ebde8/hardware/arduino/avr/cores/arduino/main.cpp#L33). There was a few snippets which stood out imediately which I did not know or expect...
 ```c
 #if defined(USBCON)
	USBDevice.attach();
#endif
```
...and within the loop...
```c
if (serialEventRun) serialEventRun();
```
Sadly opening the arduino IDE itself and trying to use `USBDevice` did not work nor was `USBCON` defined. Now what does `serialEventRun()` do? [This](https://github.com/arduino/Arduino/blob/0c325b4ff6118be331dfb27db06a6596bb6ebde8/hardware/arduino/avr/cores/arduino/HardwareSerial.cpp#L66). and calling `serialEvent()` does what? according to [this](https://www.arduino.cc/en/Reference/SerialEvent) is is called when data is available. I have honestly no clue why but clearly this is where my issue was. This maps to the [input function](https://github.com/arduino/Arduino/blob/0c325b4ff6118be331dfb27db06a6596bb6ebde8/hardware/arduino/avr/cores/arduino/HardwareSerial_private.h#L101) of the serial communication... I cut out the parirty check since it was the only possible fail case, recompiled the library and rebuilt my program and voila! Everything worked, minus the fact that my read was occasionally outputting garbage (one in every 10 inputs was wrong) it worked. okay so why was the parity/checksum wrong? I don't care that was the problem and its not my bug to fix so I submited the issue.
