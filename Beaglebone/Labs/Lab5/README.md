# Lab 5 Report
The purpose of this lab is to explore the basic GPIO functionality of the beaglebone black. This is done natively from linux with shell scripts and from a compiled language (C or Python).

> To best view this [document](https://github.com/prince-chrismc/Embedded-System/blob/master/Beaglebon/Labs/Lab5/README.md), use the link provided.

### Table of Contents
1. [Contributors](#Contributors)
2. [Introduction](#Introduction)
3. [Resources](#Resources)
    * [Software Resources](#Software-Resources)
    * [Hardware Setup](#Hardware-Setup)
4. [Discussion/Conclusion](#Discussion/Conclusion)
5. [Program Snipets](#Snippets)

## Contributors
**Student** | **ID**
:---:| ---
Christopher McArthur | `40004257`

## Introduction
#### Problem Statement:
> How do we control the GPIO headers and pin on the beaglebone black?

#### Abbreviations and Acronyms
- LED == Light Emiting Diode
- GPIO == General-purpose input/output
- LAN == Local Area Network
- SSH == Secure Shell
- CLI == Command Line Interface

## Resources
### Software Resources
- Putty for SSH from workstation to beaglebone
- Visual Studio 2017 with Linux development package from remote compilation and debug
  - GDB Server on the beaglebone was used for remote debugging

### Hardware Setup
![image](https://user-images.githubusercontent.com/16867443/33232803-6f7dbbd0-d1da-11e7-9c22-cdb7eff0613b.png)

## Discussion/Conclusion
#### Bash Exploration
Starting off with the bash section I knew I was going to follow my normal cross-platform development. I plugged the beaglebone into my switch and checked my DHCP server to find its IP address (I later reserved an IP for its MAC and mapped the IP with my DNS server). From my workstation I opened Putty and connected simply with SSH. With access to bash I made myself a user with root priviledges and made a executable file `gpio-test.sh`. I had tried to use echo at first to the built in LED to turn it off then back to heartbeat mode straight form the CLI but I had permission denied issues. The onboard filesystem access is owned by root and even running my commands with `sudo` still gave the same error. Turns out you cant access system resources (like items in the device tree) from user space at all. Solution is halarious to me, I had to run a my shell command as a shell command running from root. See [bash snippets](#Snippets) for the details. Thankfully when I ran my shell script I didnt have this rediculous problem which thanks to good planning worked on the first try.

#### CPP Exploration
After quickly setting up my enviroment, I set off emulating my shell script. I choose `ofstream` because it works exactly like echo. The code was nothing fancy, activate pin, set direction, toggle in a loop the value and that's it. See [bash snippets](#Snippets) for the details. I eneded up running it locally frrom the beaglebone as root since it was easiest.

## Snippets
#### Bash - Internal ON/OFF
```shell
cmcarthur@beaglebone:~$ sudo sh -c "echo none > /sys/class/leds/beaglebone\:green\:usr0/trigger"
cmcarthur@beaglebone:~$ sudo sh -c "echo heartbeat > /sys/class/leds/beaglebone\:green\:usr0/trigger"
```
#### Bash - Interal Timer Controlled
```shell
cmcarthur@beaglebone:~$ sudo sh -c "echo timer > /sys/class/leds/beaglebone\:green\:usr0/trigger"
cmcarthur@beaglebone:~$ sudo sh -c "echo 100 > /sys/class/leds/beaglebone\:green\:usr0/delay_off"
cmcarthur@beaglebone:~$ sudo sh -c "echo 100 > /sys/class/leds/beaglebone\:green\:usr0/delay_off"
```
#### Bash - GPIO Blink
```shell
cmcarthur@beaglebone:~$ sudo ./gpio-blink.sh
Blinking LED connected to Pin 48 ...
```
#### CPP - GPIO Blink
Code:
```cpp
// Activate the GPIO pin controlling the LED
std::ofstream gpio_setup("/sys/class/gpio/export");
gpio_setup << "48";
gpio_setup.close();
```
Output:
```shell
cmcarthur@beaglebone:~$ sudo projects/Blink/bin/ARM/Debug/Blink.out
Hello World from Blink!

Setting up gpio P9_15!
Now blinking LED...
```

## Useful links
#### Setup from remote
- How to [setup](https://blogs.msdn.microsoft.com/vcblog/2016/03/30/visual-c-for-linux-development/)  beaglebone for remote compilation and debug
#### C/CPP
- [blink gpio](http://eionix.blogspot.ca/2015/02/gpio-blink-led-using-c-beagleboneblack.html)
#### Bash
- [blink internal](https://elinux.org/EBC_Exercise_10_Flashing_an_LED)
