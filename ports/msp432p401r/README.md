# The MSP432P401R port
This project ports MicroPython to the MSP432P401R MCU

## Setup arm gcc toolchain
Run the setup script:

    $ ./setup.sh

## Building for an MSP432P401R MCU
The Makefile includes start-up code for an MSP432P401R MCU and also enables a UART
for communication.  To build:

    $ make CROSS=1

## Clean up the build system
To clean up the build system run:

    $ make CROSS=1 clean

## Deployment
Building will produce the build/firmware.axf file which can be programmed
to an MSP432P401R MCU flash using the integrated XDS110 emulator and Ti's DSLite. 

    $ make CROSS=1 deploy
    
This buld will give you a MicroPython REPL on the backport UART at 9600 baud.
Your udev rules will need to be configured to allow you to access the LaunchPad. The rule you need is:
`SUBSYSTEM=="usb",ENV{DEVTYPE}=="usb_device",ATTRS{idVendor}=="0451",ATTRS{idProduct}=="bef3",MODE:="0666"`

## Usage
Any terminal program will do, for example:

    $ sudo screen /dev/ttyACM0

