# AMDX Shaki

![Shaki title picture](https://raw.githubusercontent.com/amdxyz/shaki/master/images/title.png)

Push - Shake - Love: that's as simple as how the "Shaki" works. If you push a button and shake the stick, a message, a name or a symbol appears in the air. But what the Shaki actually demonstrates is a highly complex phenomenon - the Persistence of vision.

## POV

POV stands for Persistence of vision (https://en.wikipedia.org/wiki/Persistence_of_vision)
The image of an object stays on the retina even after stopping looking at it as the eye and brain actually retain a visual impression for about 1/20 th of a second. It is the principle of movies and animations - and of the small exhibit we at Archimedes Exhibitions created to make this scientific phenomenon playfully comprehensive. You can put the Shaki in your trouser pocket and experience and learn about the Persistence of vision wherever you like, alone or in groups.

![POV Sample picture](https://raw.githubusercontent.com/amdxyz/shaki/master/images/proto0_ciao.jpg)

## History

The Shaki was developed as part of an internal competition we regularly launch at Archimedes Exhibitions to cultivate creativity and innovative ideas outside the daily working routine. The goal of the competition was to produce a cheap and insightful giveaway for the upcoming ECSITE annual conference (https://www.ecsite.eu/).

The background idea behind our Shaki was kind of a „Gadgetification": taking one of our original size exhibits and shrinking it until it fits into a trouser pocket.

The Shaki is the gadgetified version of our "Spinning Display", a rotating POV display developed for the Science and Technology Centre Ostrava (CZ), as part of the "World of Nature" exhibition (http://stcostrava.cz/setrvacnost-oka).

Archimedes Exhibitions gave away 200 Shakis units among the participants of the 2018 ECSITE conference and, after its big success, decided to release the Shaki's firmware, tools and PCB as open source.

![Shaki prototypes](https://raw.githubusercontent.com/amdxyz/shaki/master/images/protos.png)

## Components and operation

The Shaki hardware has five main components:

* battery: its power source
* button: connects the battery to the rest of the components
* microcontroller: the brain
* accelerometer: the sensor that detects a shake
* LEDs bar: 8 small light emitting diodes that paint the stored pictures in the air

![Components](https://raw.githubusercontent.com/amdxyz/shaki/master/images/components.png)

### Theory of operation

Once the button is pressed and as long as it's being kept pressed, the microcontroller talks to the accelerometer and attempts to detect the motion of the stick in real time. The accelerometer reports its readouts 1.600 times per second.

The idea is to detect the two extremes of a shake motion (a rapid side to side oscillation) and to paint a frame while moving from left to right.

As soon as the microcontroller decides that the stick is moving from left to right, it starts to stream the current frame to the LEDs bar. The frame is composed of several columns and each column is extracted and "transferred" to the LEDs bar using a timer. This transfer means that some LEDs will be lit, some not, according to the "white" or "black" pixels set in the frame.

Each 2.4ms a new column is moved from the microcontroller's memory to the LEDs bar until all the columns have been transferred. From this point on the LEDs shut down and the microcontroller waits until the rightmost point is reached.

Once the rightmost point is reached, the microcontroller decides whether to advance to the next frame or to paint the last one again (depending on the amount of shakes-per-frame defined). The LEDs are kept off until the cycle repeats.

![Steps](https://raw.githubusercontent.com/amdxyz/shaki/master/images/steps.png)

### More details on the components

* Microcontroller: ATMEL ATTiny88 (8kB FLASH, 512B SRAM) clocked at 8Mhz via its internal RC oscillator
* Accelerometer: ST LIS3DH MEMS accelerometer (16bit, I2C/SPI, 5300Hz max update rate)

The accelerometer is connected to the microcontroller via its I2C interface.

## What to find in the repository

This repository is composed of the following:

* eagle: EagleCAD schematics, PCB layout and BOM
* firmware: the software that runs inside the Shakis
* tools: converter and authoring tools to customise the displayed frames

Each folder contains a detailed readme file.

## FAQ

AKA frequently asked questions:

### Can I get an assembled, ready-to-use Shaki?

Yes, write to us: shaki {a} amdx.de

### Can I produce, customise, sell the Shaki?

As long as it fits the terms of the [LICENSE](https://github.com/amdxyz/shaki/blob/master/LICENSE.md), you're more than welcome.

### How can I customise my Shaki?

This repository provides everything you need to do any customisation you may have in mind, but the process requires some technical skills and tools.

In short:

* Produce the frames using a graphic authoring tool or the included of_bitpuncher tool
* Convert the authored graphic (not required when using of_bitpuncher)
* Compile the firmware
* Upload the firmware to the Shaki using a programmer and a programming jig

### Why no USB?

One of the Shaki's primary requirements was to minimize its production costs. It wasn't initially supposed to be released to the public, so we didn't consider a consumer-grade programming interface.

### How can I contribute?

Feel free to file an issue or post a push request!

### Any media?

You can watch a short presentation here: https://www.youtube.com/watch?v=L5a6pu70XJo

And a brief introduction here: http://www.amdx.de/shaki
