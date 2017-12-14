# Lab 6 - Final

### Table of Contents
1. [Contributors](#Contributors)
2. [Device tree](#Device-tree)
3. [Real Time](#Real-time)
4. [Attributions](#Attributions)

## Contributors
**Student** | **ID**
:---:|---
Christopher McArthur | `40004257`

## Device Tree
Initial in the linux kernel, the information/configuration regarding all support platforms was hard coded into the kernel. At boot time the kernel would be given the platform ID and behave accordingly. The issue of this hardcoded aproach rose when microcontrollers began exploding, each containing thier own set of hardware. This eventually lead to the developers of the linux kernel being unable to keep up and as a result they released the _device tree_ such that not every new device would be supported natively in the kernel.

In breif, a device tree is the descriptor of the hardware configuration of a device. This descriptor is loaded to memory by the bootloader and the adress is given to the kernel such that it is able to behave correctly. The file processed by the kernal is byte code, a `.dtb`, which means it is compiled implying theres some source code to it. The device tree source, a `.dts`, can be viewed and edited as a textformat similar to XML/JSON.

In the case of the BeagleBone Black where there are 92 pins which are multiplexed upwards of a factor of 8, the device tree allows for the pins to be reconfigured based on the requirements of the system. It is possible to change the configuration without altering the device tree but the changes made would be lost on reboot. A prime example of this is the onboard LEDs, by default `LED` is set to the `heartbeat` mode (meaning it blinks twice in rapid succession then takes a short pause before repeating). If you were to change this using the systems file directory and change the mode to `none` or `timer`, you would see the effect live on the device. How every, upon reboot, the changes you made would be lost and it would return to the default state of `heartbeat`. In comparision to changing the mode through the device tree, the changes would be kept regardless of being rebooted.

Due to the vast number of pins and the degree to which they are multiplexed, there is around 400 possible configurations which can be set on the BeagleBone Black. Despite the possiblity to change the mode of every single pin live with the file system, this does not garauntee the pin is availiable to you for use. The default settings have HDMI caoabilites enabled, this means the linux OS will be trying to output the display on these pins so you may not get the results you are hoping for.

Since most functionality does not require just one pin, for example many communication methods, there is a need to easily configure multiple pins to multiple modes. This is the role of the BeagleBone's cape manager, or `bone_capemgr` for short, to allow for preset functionalities to be enabled or disabled and configured correctly through the device tree. The cape manage loads or works with overlays which are easiest to describe as a fragment of a device tree which specifies a certain functionality. The overlay will contain all the information need for the kernel to operate correctly such as which pins, what mux to set for these pins, which driver is being utilised, and any other necessary information.

```c++
/*
 * Copyright (C) 2013 CircuitCo
 *
 * Virtual cape for UART1 on connector pins P9.24 P9.26
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
/dts-v1/;
/plugin/;
 
/ {
   	compatible = "ti,beaglebone", "ti,beaglebone-black";
 
    /* identification */
    part-number = "BB-UART1";
    version = "00A0";
 
    /* state the resources this cape uses */
    exclusive-use =
        /* the pin header uses */
        "P9.24",        /* uart1_txd */
        "P9.26",        /* uart1_rxd */
        /* the hardware ip uses */
        "uart1";
 
    fragment@0 {
        target = <&am33xx_pinmux>;
        __overlay__ {
            bb_uart1_pins: pinmux_bb_uart1_pins {
                pinctrl-single,pins = <
                    0x184 0x20 /* P9.24 uart1_txd.uart1_txd MODE0 OUTPUT (TX) */
                    0x180 0x20 /* P9.26 uart1_rxd.uart1_rxd MODE0 INPUT (RX) */
                >;
            };
        };
    };
 
     fragment@1 {
         target = <&uart2>;	/* really uart1 */
         __overlay__ {
             status = "okay";
             pinctrl-names = "default";
             pinctrl-0 = <&bb_uart1_pins>;
         };
     };
};
```

The example above is taken from [adafruit's explination](https://learn.adafruit.com/introduction-to-the-beaglebone-black-device-tree/device-tree-overlays) of overlays. In this example the node will be attached to the root `/` of the device tree and is compatible with the beaglebone and beaglebone black variants. The name of the overlay and its version are also specified. The usuage section specifies `"P9.24", "P9.26", "uart1";` as the pins to use for the UART1 functionality. Fragement 0 defines the pin muxing settings and fragment 1 enables the device for use.

## Real Time
The linux OS does not meet the requirements for real hard time because it is a _non-preemptive_ operating system. What this means is that while an execution is underway in kernel space there is no way to interrrupt that processes. Making a square wave using a application running on a linux OS can run into problems as the quote below explains...
>  For example, it could be time for a GPIO to be toggled in a time‐critical manner, but the Linux process scheduler may already have determined that the Apache web server should execute. Because Linux is a nonpreemptive OS, Apache cannot be interrupted until it fi nishes its kernel service time. Therefore, the toggling of the GPIO will be delayed and signal jitter arises

Hard time is messured in the nanosecond range, because the linux OS has to interrupt a process, call the schedular, context switch to the correct application which can only then execute the time sensitive code. This makes the latency of the OS very unresponsive and unable to meet the needs of real hard time.

In order to meet the real hard time require usually expected from embedded micro controllers the BeagleBone Black comes equiped with two PRUs or real time processing units. Each PRU has its own memory and independant CPU and is not included in the kernel. This makes the PRU's pure bare metal meaning there is only your program running and each instruction runs in constant time. Having an entire processor to your program means there is no time slicing with an OS distributing resources; every PRU operation takes a known time making it able to meet the requirements of a hard time system. Since the pins are multiplexe some can be configured to have direct access to the PRU meaning you can closely get a square wave.

When working in C with the PRU's there are some important function calls:
- `prussdrv_init();` - Initializes and allocates memory for the PRU Subsystem driver
- `prussdrv_open(PRU_EVTOUT_0);` - Opens an event out and initializes memory mapping.
- `prussdrv_pruintc_init(&pruss_intc_initdata);` - Initializes and enables the PRU interrupt controller

- `prussdrv_load_datafile(PRU_NUM, "./data.bin");` - Loads binary to PRU
- `prussdrv_exec_program_at(PRU_NUM, "./text.bin", START_ADDR);` - Begins execution
- `prussdrv_pru_disable(PRU_NUM);` - Releases PRUSS clocks and disables prussdrv module
- `prussdrv_exit ();` - 

### Attributions
* [Introduction to device trees](http://ofitselfso.com/BeagleNotes/AboutTheDeviceTree.pdf)
* [Introduction to cape manager and slots](http://www.raspberry-pi-geek.com/index.php/Archive/2014/03/Capemgr-keeps-track-of-theBeagleBone-Black-s-expansion-boards-known-as-capes/(offset)/2)
* [Introduction to device tree overlays](https://learn.adafruit.com/introduction-to-the-beaglebone-black-device-tree/device-tree-overlays)
* [Exploring The BeagleBone Black](http://fccr.ucsd.edu/refs/ExploringBeagleBone.pdf)
* [BeagleBone Black PRU](http://mythopoeic.org/bbb-pru-minimal/)
* [PRU Function Definitions](http://processors.wiki.ti.com/index.php/PRU_Linux_Application_Loader_API_Guide)
* [PRU Function Implementation](https://github.com/beagleboard/am335x_pru_package/blob/master/pru_sw/app_loader/interface/prussdrv.c)
