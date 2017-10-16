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
- Problem Statement: Build a simulated car which reverses on detection of any object infront of it. One Arduino is responsible for the object detection and the second is responsible for motor control. This setup requires for communication between the two.
- Abbreviations and Acronyms
  - LED == Light Emiting Diode
  - DDRx, PBn, etc... Registers names
  - OCR == output compare register
  - IR == infra red
  - ADC == analog to digital conversion
  - PWM == pulse with modulation
  - DC == direct current
 
## Resources 
- Hardware Resources
  - Two Arduino Nano
  - LEDs
  - Jumper Wires
  - IR Sensor
  - HBridge
  - Mini Car (if aplicable)
- Hardware Setup
  - fritzing for each part.

## Software Resources
- Software setup
  - IDE is Visual Studio 2017 Enterprise
  - Compilers are the avr-gcc/avr-g++ for windows
  - Visual studio has an extension called [Visual Micro](http://www.visualmicro.com/) which handles everything from compiling to upload (it just needs to be configured similar to the Arduino IDE)
 
## Program Snipets

## Reference Code Common
- the basic Arduino bare metal IO.h for access to pins and registers and basic definitions
- the AVR libraries interrupts.h was a key component
- HardwareSerial.h for serial communitcation for debug prints
- The supplied ADC code was extremely useful, I just specialized it to my particular case. (recouperated from lab2)

## Discussion/Conclusion
- In the early stages of the Lab (Part 2) the difficulty was figure how best to trigger the interrupts. I had an initial 5v output during the interrupt and tried the various modes but in the end I selected `trigger on rising edge` and fine tuned my signal to 5v out for 500ms and then 0v out.
