# BSP for MSP432
This is a basic board support package to permit bare-metal use of the TI MSP432
line of microcontrollers. It is ready to use with the MSP432 P401R LaunchPad
kit out of the box. This BSP is meant for use with the GCC compiler.
The recommended compiler is [GCC ARM Embedded](https://launchpad.net/gcc-arm-embedded).
You will need to add the compiler to your PATH environment variable, or
specify it explicitly by providing the CROSS\_COMPILE variable.

Use the (proprietary and hard to find) DSLite utility to flash your code onto
the LaunchPad using the integrated XDS110 emulator. The utility is bundled
inside the CCS web support package, and is also bundled with Energia.
For convenience, I have uploaded the Linux version of the standalone utility
to [Mediafire](https://www.mediafire.com/?d84ku2n9x321x2p). You can also
find DSLite with the TI packages available
[here](http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP-EXP432P401R/latest/index_FDS.html).

Your udev rules will need to be configured to allow you to access the
LaunchPad. The rule you need is:
```
SUBSYSTEM=="usb",ENV{DEVTYPE}=="usb_device",ATTRS{idVendor}=="0451",ATTRS{idProduct}=="bef3",MODE:="0666"
```
