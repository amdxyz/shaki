# of_bitpuncher

This application helps to create patterns and sequences through a graphical interface. It allows you to upload new patterns to your Shaki by using platformIO or to export them to a C-header file suitable for the Shaki firmware.

**Note: Tested on OSX with openframeworks 0.10.0**

## Requirements

### openframeworks

The of_bitpuncher app is based on openframeworks, an open source C++ toolkit. Download it from https://openframeworks.cc/.

The app uses the addon ofxGuiExtended by frauzufall. Clone it to the openframeworks addons directory.

    $ cd ../of_vX.XX.X_osx_release/addons
    $ git clone https://github.com/frauzufall/ofxGuiExtended.git

Create a new openframeworks project on top of the of_bitpuncher source files. Navigate to the project generator app coming along with openframeworks.

    $ open ../of_vX.XX.X_osx_release/projectGenerator/projectGenerator.app

Under the tab 'create/update' fill in the following:

    Project name: 'of_bitpuncher'
    Project path: '../tools/'
    Addons: 'ofxGuiExtended'

Click on 'Generate'. This will automatically create the make file needed to compile the software on your computer.

To compile:

    $ cd ../tools/of_bitpuncher
    $ make

To run the app:

    $ make run
Alternatively execute ../tools/of_bitpuncher/bin/of_bitpuncher.app

### platformIO

PlatformIO is required to compile and upload the produced patterns / sequences to the Shaki with a one-button operation. Alternatively, the patterns / sequences can be exported to a C-header frame data file suitable for the current firmware.

## Usage

### Edit a frame

Create a pattern by clicking / dragging the mouse over the 8x8 matrix on the top. It is also possible to use the key input to have a quick access to predefined letters and numbers. Only letters from 'a' to 'z' and numbers from '0' to '9' are implemented.

### Create a sequence

In order to create words, animation or multiple icons create a sequence by adding more frames. Click on '+' to add one frame or click on the trash can icon to delete the currently selected frame.

### Shakes per frame

'Shakes per frame' defines the number of shakes before the Shaki advances to the next frame.

### Templates

Pick one of the templates on the right-hand side for quick and easy start. There is also the option to add the current sequence to the template list by clicking on 'Add template' at the bottom right.

### Reset / Upload / Export

Click on 'Reset' to start from scratch. 'Upload' will flash the firmware on the Shaki (platformIO required). 'Export' allows you to save the frame_data.h file on you computer.
