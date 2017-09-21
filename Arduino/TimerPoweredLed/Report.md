# Lab1 Report

## Introduction
- Problem Statement: Using arduino and coding in 'bare metal' (c programming) create a 4-bt counter that displays the binary value of the counter on a set of LEDs. the solution should take in a count debouncing effect.
- Abbreviations and Acronyms
 - LED == Light Emiting Diode
 
## Resources 
- Hardware Resources
 - Arduino Nano
 - LEDs
 - Push Button
 - Resistors
 - Jumper Wires
- Hardware Setup
 - Nano has its 5V and GRN pin connected to the power lines of the bread board
 - it has four pins wired to the LEDs, one to one
 - the LEDs are connected to a bar resistor which is connected to the GRN power line
 - A push button recives power from the power line
 - when pressed the push button signals an LED and the Nano its been pressed

## Software Resources
- Software setup
 - IDE is Visual Studio 2017 Enterprise
 - Compilers are the avr-gcc for windows
 - loader is the default Arduino IDE one
 - Visual studio has an extension called 'Visual Micro' which handles everything from compiling to upload (it just needs to be configured like the Arduino IDE)
 
## Program Snipets
- main loop
```
while (1)
{
  if (isButtonPressed())
  {
    displayCounter(++iCounter);
	_delay_ms(100);
  }
}
```
- button detection
```
if (PINB&(HIGH << PB4) && !g_bPressed)
{
  g_bPressed = 1;
  return 1;
}
g_bPressed = 0;
return 0;
```

## Reference Code Common
- the basic Arduino bare metal IO.h
- the utility delay.h as well

## Discussion/Conclusion
- Thankfully I had already done bare metal before on an arduino so I had everything already configured but a week to figure that out certainly is not enough time
- Having both a Lab and pre-lab to do every week seems a bit intensive though I do love the work and challenge
- I waste a lot of time because i wrote +counter and not ++counter but once i fixed that everything worked