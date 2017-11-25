# Lab 5

## Useful links
### C/CPP
- http://derekmolloy.ie/beaglebone-controlling-the-on-board-leds-using-c/
- http://eionix.blogspot.ca/2015/02/gpio-blink-led-using-c-beagleboneblack.html
### Bash
- http://eionix.blogspot.ca/2015/02/gpio-blinking-led-using-bash-script.html
- https://elinux.org/EBC_Exercise_10_Flashing_an_LED

## Snippet
```shell
cmcarthur@beaglebone:~$ sudo sh -c "echo none > /sys/class/leds/beaglebone\:green\:usr0/trigger"
cmcarthur@beaglebone:~$ sudo sh -c "echo heartbeat > /sys/class/leds/beaglebone\:green\:usr0/trigger"
```
```shell
cmcarthur@beaglebone:~$ sudo sh -c "echo timer > /sys/class/leds/beaglebone\:green\:usr0/trigger"
cmcarthur@beaglebone:~$ sudo sh -c "echo 100 > /sys/class/leds/beaglebone\:green\:usr0/delay_off"
cmcarthur@beaglebone:~$ sudo sh -c "echo 100 > /sys/class/leds/beaglebone\:green\:usr0/delay_off"
```
