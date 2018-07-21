# Shaki firmware

This directory contains the firmware for the Shaki board.

Building the firmware is a required step for customizing the stored frames, since they're backed into the firmware itself (and residing in flash).

The firmware can be built using two IDEs:

* Platformio (http://www.platformio.org)
* Atmel Studio 7 (https://www.microchip.com/mplab/avr-support/atmel-studio-7)

## Frame data

The simplest way to hack the Shaki is to alter the content of its frame buffer.

All the frames shown during a shake, are stored into the header frame_data.h in the variable named "frames".

The file can be generated using one of the two tools provided:

* bitmap_converter
* of_bitpuncher

More information is provided inside the tools folder.


## Modifying the source and/or building it

There are three methods that can be followed to build the firmware:

### Using platformio command line tools

Build the firmware by issuing:

	$ pio run

The firmware can be then uploaded using the target "upload":

	$ pio run -t upload

Check below for notes about uploading.

### Using platformio IDE

Open the project in the IDE and press either build or upload.

### Using Atmel Studio 7

Navigate into atmelstudio and double-click the solution file "atmelstudio.atsln".

The solution can be built pressing F7 (or choosing "Build solution" from the build menu).

In order to upload the firmware or run a debug session, a programming tool must be defined.

## Uploading the firmware

In order to upload the firmware, you need the following tools:

* AVRISP-MKII or compatible
* ISP pogo-pins jig (eg: Sparkfun KIT-11591 https://www.sparkfun.com/products/11591)

The jig should be applied over the exposed programming pads as shown in the following picture:

![Pogo-pins ISP](https://raw.githubusercontent.com/amdxyz/shaki/master/images/pogo_isp.jpg)

Once the pogo pins are properly in contact with the pads, the programming can be carried on.

### Using Atmel-ICE

As the AVRISP is no longer in production, it can be replaced with the newer atmel-ICE.

In order to use it with platformio, edit the file boards/shaki.json and modify the key "protocol" under "upload":

	"protocol": "avrispmkii",

to

	"protocol": "atmelice_isp",

Make sure the programmer pigtail is connected to the "AVR" port.

## Fuses

The AMDX Shaki board comes provisioned and pre-programmed with a default pattern. In case you produced the board by yourself, the microcontroller must be provisioned with fuses setting.

The fuses hexes are:

* High: 0xd7
* Low: 0xee

The directory "provisioning" contains two scripts that can be used to set the fuses using avrdude and an AVRISP-MKII programmer. They can be used under windows (.bat) and linux, OSX (.sh), provided that avrdude is available in the PATH.

## Debugging

### Test pattern

A test pattern can be activated by adding a define TEST_PATTERN (see firmware/platfomio.ini).

Once flashed, the firmware will provide two brief blinks to signal the detection of the two motion extremes (left and right).

### Timing test point TP1

TP1 is a timing pin that can be connected to an oscilloscope in order to perform motion analysis.

It offers two debugging modes:

* DEBUG_ON_COLUMN : every time a new column from a frame is transferred to the LED bar, this line asserts shortly
* DEBUG_ON_SHAKE : the line asserts during a left-to-right motion and deasserted otherwise

The two modes can be activated by defining the respective identifiers. Check firmware/platformio.ini file for more information.
