# The MSP432 Launchpad

Install GCC cross compiler for ARM Cortex-A/R/M processors. On debian 8.4 this worked.

    $ apt-get remove binutils-arm-none-eabi
    $ apt-get remove gcc-arm-none-eabi
    $ add-apt-repository ppa:terry.guo/gcc-arm-embedded
    $ apt-get update
    $ apt-get install gcc-arm-none-eabi


## Building for MSP432

    $ make CROSS=1

To remove the built object files

    $ make CROSS=1 clean


## Donwload to Target

See using Command Line: before executing this command
    
    $ make CROSS=1 deploy


**under Windows**
* Tool: CCS UniFlash
* The build process generates a **firmware.axf** file in the /build output directory.
  This file is used to flash the target with CCS UniFlash.

* Open CCS UniFlash. Click on *File-New Configuration*. 
  Next window choose as **Connection**: Texas Instruments XDS110 USB Debug Probe
  and type in by **Board or Device**: MSP432P401R. At least press OK.

* Now click on the left side at **Programs** and right opened window at the bottom at **add**.
  Now choose the **firmware.axf** and press OK. 
  Last step is to press **program** at the right bottom.


**Under Linux**

  Download UniFlash for linux and follow the installation instructions from [TI's wiki page](http://processors.wiki.ti.com/index.php/Linux_Host_Support_CCSv6#Installation_Instructions.) for your linux machine
  

**using GUI:**

  Download to target is similar to the Windows description above.

**using Command Line:**

* Install uniflash_3.4 into the msp432 directory (/msp432/uniflash_3.4)
  
* Setup new configuration (see "under Windows" above) and save it to the /uniflash_3.4 directory 
  File -> Save Configuration As -> /uniflash_3.4/msp432_config.ccxml

*  Download to target from command line, `make CROSS=1 deploy`

## get REPL

**under your Windows**

First look at device manager for COMport number of device *XDS110 Class Apllication/User UART*
Open putty, set a serial connection with the COMport device with baudrate 9600 and press OK.


**under Linux**

use any of your favourite serial communication programs like **minicom**, **screen** or **picocom**.
Locate and connect to your board as Root: for example,
	
	$ (root) screen /dev/ttyACM0


