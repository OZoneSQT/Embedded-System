# Lab 4 - Midterm

### Table of Contents
1. [Contributors](#Contributors)
2. [Theory Questions](#Theory-Questions)
3. [Compilation and Uploading](#Compilation-and-Uploading)

## Contributors
**Student** | **ID**
:---:| ---
Christopher McArthur | `40004257`

## Theory Questions
1. Which Microcontroller does the Arduino Nano use? **ATmega328**
2. What is the default clock speed for this Microcontroller? **16MHz**
3. How can you change the clock speed? And what can you change it to? **By defining the preprocessor F_CPU; you can set this to any MHz value the chip supports**
4. Some of the libraries that we’ve seen use a constant F_CPU, what does this variable do? **This is not a varaible. It is used to calculate the values needed in function like `_delay_ms()`**
5. Why does the Arduino IDE not complain when you forget to define F_CPU? **The Arduino IDE by default passes the correct command line arguement for your micro-controller**

## Compilation and Uploading
- Compilation
  - Compiler: `avr-gcc -O1 -o blink.o -mmcu=atmega328 blink.cpp`
  - Convert to Hex: `avr-objcopy -O ihex blink.o blink.hex`
- Uploading
  - Flashing MC: `avrdude -c usbtiny -p m328 flash:w:blink.hex`
