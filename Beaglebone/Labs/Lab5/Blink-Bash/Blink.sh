#!/bin/sh

# https://groups.google.com/d/msg/beagleboard/RQ_FTbP7rHM/PtjW1popct0J
# attempt to control from cli
sudo sh -c "echo none > /sys/class/leds/beaglebone\:green\:usr0/trigger"
