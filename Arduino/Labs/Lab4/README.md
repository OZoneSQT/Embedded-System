# Lab 4 - Midterm

### Table of Contents
1. [Contributors](#Contributors)
2. [Theory Questions](#Theory-Questions)
3. [Compilation and Uploading](#Compilation-and-Uploading)
4. [Attributions](#Attributions)

## Contributors
**Student** | **ID**
:---:| ---
Christopher McArthur | `40004257`

## Theory Questions
1. Which Microcontroller does the Arduino Nano use? **ATmega328**
2. What is the default clock speed for this Microcontroller? **1 or 8MHz depending on configuration**
3. How can you change the clock speed? And what can you change it to? **By changing the clock prescalar registars; By using external clock**
4. Some of the libraries that we’ve seen use a constant F_CPU, what does this variable do? **This is not a varaible. It is used to calculate the values needed in function like `_delay_ms()`**
5. Why does the Arduino IDE not complain when you forget to define F_CPU? **The Arduino IDE by default passes the correct command line arguement for your micro-controller**

## Compilation and Uploading
- Compilation
  - Compiler: `avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -w -x c++ -E -CC -mmcu=atmega328p   -DF_CPU=16000000L -DARDUINO=10804 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR -I"C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\eightanaloginputs" "C:\Users\cmcarthur\AppData\Local\Temp\VMBuilds\Motor Control\nano_atmega328\Release\Motor Control.cpp" -o "nul"`
  - Convert to Hex: `avr-objcopy" -O ihex -R .eeprom "C:\Users\cmcarthur\AppData\Local\Temp\VMBuilds\Motor Control\nano_atmega328\Release/Motor Control.ino.elf" "C:\Users\cmcarthur\AppData\Local\Temp\VMBuilds\Motor Control\nano_atmega328\Release/Motor Control.ino.hex"`
- Uploading
  - Flashing MC: `avrdude "-CE:\Program Files (x86)\Arduino\hardware\tools\avr/etc/avrdude.conf" -v -patmega328p -carduino "-PCOM4" -b57600 -D "-Uflash:w:C:\Users\CMCART~1\AppData\Local\Temp\VMBuilds\PHASEC~1\NANO_A~1\Release/Phase Correct PWM.ino.hex:i"`

## Attributions
Over hearing other students discuss thier answers because I didnt have time to even start this. Though I'm pretty sure I gave away more answers... I though this was common knowledge stuff.
