#!/bin/sh

# https://groups.google.com/d/msg/beagleboard/RQ_FTbP7rHM/PtjW1popct0J
# attempt to control from cli -- default is heartbeat
sudo sh -c "echo none > /sys/class/leds/beaglebone\:green\:usr0/trigger" # attempt 1 (following tutorial)

# trying user specified timer values
sudo sh -c "echo timer > /sys/class/leds/beaglebone\:green\:usr0/trigger"
sudo sh -c "echo 100 > /sys/class/leds/beaglebone\:green\:usr0/delay_on"
sudo sh -c "echo 100 > /sys/class/leds/beaglebone\:green\:usr0/delay_off"
