# Fuses provisioning

Shaki boards produced by AMDX come always provisioned and require no additional setup.

Self-produced boards require one-time setup for the fuses settings.

## Under windows (Atmel Studio 7)

Make sure the programmer is connected via USB to your PC

* Open the solution file (optional)
* Open the device programming tool (Tools -> Device Programming)
* Select the programmer from the Tool dropdown
* If not selected, choose "ATTiny88" as device
* Press "Apply"
* Make sure that the pogo-pins jig is attached to the board
* Press "Read" to check connection and device signature
* Select "Fuses" on the left navigation column
* Uncheck "LOW.CKDIV8"
* Press "Program"

Ensure that the summary of the action reports all entries with a trailing "OK"

## Under windows (avrdude)

**Note: the drivers installed by Atmel Studio are incompatible with avrdude**

Prerequisite: avrdude must be in the path or the exe and the config file must be moved to this directory

* Make sure that the pogo-pins jig is attached to the board
* Execute the bat file

## Under OSX or Linux

Prerequisite: avrdude must be installed (via homebrew for OSX or any packaging system under linux)

* Make sure that the pogo-pins jig is attached to the board
* Execute the shell script
