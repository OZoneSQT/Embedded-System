#!/bin/sh

cd /sys/class/gpio
echo 23 > export
cd gpio23
echo out > direction

while true
do	
	echo 1 > /sys/class/gpio/gpio23/value
	cat /sys/class/gpio/gpio23/value
	sleep 1
	echo 0 > /sys/class/gpio/gpio23/value
	cat /sys/class/gpio/gpio23/value
	sleep 1
done
