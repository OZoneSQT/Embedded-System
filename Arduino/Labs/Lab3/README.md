# Lab3 Report
The purpose of this lab was to develop basic skills related to interruprt handling, hbridge, arduino communication, and motor control.

> To best view this [document](https://github.com/prince-chrismc/Embedded-System/blob/master/Arduino/Labs/Lab3/README.md), use the link provided.

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
- Problem Statement: Build a simulated car which reverses on detection of any object infront of it. One Arduino is responsible for the object detection and the second is responsible for motor control. This setup requires for communication between the two. Motors (LEDs in practice) are wired to an HBridge amplifying the Arduino's 5Vs.
- Abbreviations and Acronyms
  - LED == Light Emiting Diode
  - DDRx, PBn, etc... Registers names
  - OCR == output compare register
  - IR == infra red
  - ADC == analog to digital conversion
  - PWM == pulse with modulation
  - DC == direct current
  - UART == Universal asynchronous receiver-transmitter+
 
## Resources 
- Hardware Resources
  - Two Arduino Nano
  - LEDs
  - Jumper Wires
  - IR Sensor
  - Capacitor
  - HBridge
  - Mini Car (if aplicable)
- Hardware Setup
  - Part 3: ![image](https://user-images.githubusercontent.com/16867443/31867354-fa3f5df8-b75b-11e7-9aff-d27addf83a9b.png)
  - Part 4: I was unable to find the Hbridge in fritzing.

## Software Resources
- Software setup
  - IDE is Visual Studio 2017 Enterprise
  - Compilers are the avr-gcc/avr-g++ for windows
  - Visual studio has an extension called [Visual Micro](http://www.visualmicro.com/) which handles everything from compiling to upload (it just needs to be configured similar to the Arduino IDE)
  - Fritzing for diagrams
 
## Program Snipets

## Reference Code Common
- the basic Arduino bare metal IO.h for access to pins and registers and basic definitions
- the AVR libraries interrupts.h was a key component
- HardwareSerial.h for serial communitcation for debug prints
- The supplied ADC code was extremely useful, I just specialized it to my particular case. (recouperated from lab2)
- The UART example on moodle (I cleaned and refacted it)

## Discussion/Conclusion
In the early stages of the Lab (Part 2) the difficulty was figure how best to trigger the interrupts. I had an initial 5v output during the interrupt and tried the various modes but in the end I selected `trigger on rising edge` and fine tuned my signal to 5v out for 150ms and then 0v out; however intermidiately I still had an issue with only 1 interrupt being detected. Getting the UART communication to work took me several hours, namely because i had put my `serial_read()` within interrupts being disabled. There was no major challenge or unexpected behavoir getting UART to work thats to the code provided. The final section for adding the Hbridge and the 'motor' (really just two LEDs) was surprising easy once I figured out which side was which. I did not need to use PWM I just used serial `HIGH` and `LOW` as my signal to the Hbridge. Toggling the outputs changed the direction of the 'motor' (ie. changed which LED was lite).
