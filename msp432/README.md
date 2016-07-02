# The MSP432 Launchpad

Install GCC cross compiler for ARM Cortex-A/R/M processors. On debian 8.4 this worked.

    $ apt-get remove binutils-arm-none-eabi
    $ apt-get remove gcc-arm-none-eabi
    $ add-apt-repository ppa:terry.guo/gcc-arm-embedded
    $ apt-get update
    $ apt-get install gcc-arm-none-eabi


## Building for MSP432

    $ make CROSS=1

## donwload to target

**under Windows**
Tool: CCS UniFlash
The build process generates a **firmware.axf** file in the /output directory.
This file is used to flash the target with CCS UniFlash.

Open CCS UniFlash. Click on *File-New Configuration*. 
Next window choose as **Connection**: Texas Instruments XDS110 USB Debug Probe
and type in by **Board or Device**: MSP432P401R. At least press OK.

Now click on the left side at **Programs** and right opened window at the bottom at **add**.
Now choose the **firmware.axf** and press OK. 
Last step is to press **program** at the right bottom.

## get REPL

**under Windows**
First look at device manager for COMport number of device *XDS110 Class Apllication/User UART*
Open putty, set a serial connection with the COMport device with baudrate 9600 and press OK.
