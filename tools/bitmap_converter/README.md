# Bitmap to Shaki frame data header converter

This tool converts a set of bitmap files to the C-header format required by the firmware to store the frames data.

## Requirements

### Converter

The converter requires python 2.7 or python 3 and uses PIL/Pillow for image operations. This requirement can be fulfilled in different ways depending on the working platform.

A typical workflow using virtualenv:

	$ virtualenv _venv
	$ source _venv/bin/activate
	$ pip install -Ur requirements.txt

Remember to activate the virtualenv before using the converter.

### Input files

The converter expects the input files to meet the following requirements:

* Color mode: bitmap (1 bit per pixel)
* White pixels turn the LEDs on
* The height must be exactly 8 pixels
* The width is arbitrary, but widths below 12 work best
* Any common image compression is supported, PNG is suggested
* The number of frames is arbitrary (see below for the memory limits)

Check the files provided in the samples folder.

## Usage

The simplest usage example:

	$ ./convert.py samples/amdx/*

The invocation above uses two sample bitmaps provided in the amdx samples folder and converts them into a file "frame_data.h" in the current working directory.

A more complete example:

	$ ./convert.py --spf 2 --output ../../firmware/src/frame_data.h samples/helloworld/*

* --spf 2: indicates that each frame should be painted for two shakes
* --output ../../firmware/src/frame_data.h: overwrite the current frame_data.h file
* Files list: this is the ordered list of bitmap frames to convert. Globbing is supported.

### Note about spf

The "spf" parameter (standing for shakes-per-frame) defines how the frames are coupled to the POV scan (or shake).

A value greater than zero (the default of the tool is 5) will repeat the paint of a single frame for more than once.

Repeating helps the user to properly understand the painted frame.

An SPF of 1 may be used with frames sequences that are supposed to show a fluid animation and where the sequence in its whole is more representative than each single frame.

## Memory limits

Each row requires one byte of flash memory. The memory available for the frame buffer is around 7200 bytes, which means 7200 columns maximum in total.

When using 8x8 frames, for example, the maximum number of frames that can be stored is roughly 112.
