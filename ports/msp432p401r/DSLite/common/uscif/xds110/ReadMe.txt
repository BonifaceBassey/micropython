xdsdfu Update Utility for the XDS110

How to update the firmware and change the serial number.

*** Updating the Firmware Using xdsdfu. ***

You can update the XDS110 firmware using the xdsdfu program included 
in this directory over the USB connection. 

To program the firmware, follow these steps:

1) Plug the XDS110 debug probe into your computer. Make sure that you 
only have one XDS110 class debug probe plugged in. The xdsdfu program  
will attempt to flash the first XDS110 debug probe it finds.

2) Run the following two commands from this directory:

xdsdfu -m
xdsdfu -f firmware.bin -r

You may need to pause after the first command to give the OS time to 
recognize that the XDS110 has reconfigured as a different USB device.

Once the second command completes, the firmware is updated, and the 
debug probe should be ready to use.

NOTE: Check with your vendor for the correct firmware .bin file to use.
      Your vendor may have made changes or added features that require
      the use of a custom firmware supplied by them.

*** Changing the Serial Number Using xdsdfu. ***

You can change the XDS110 serial number using the xdsdfu program. This 
will allow you to have more than one XDS110 connected to your system
and let the host locate a specific one to connect to.

To change the serial number, follow these steps:

1) Plug the XDS110 debug probe into your computer. Make sure that you 
only have one XDS110 class debug probe plugged in. The xdsdfu program  
will attempt to flash the first XDS110 debug probe it finds.

2) Run the following two commands from this directory:

xdsdfu -m
xdsdfu -s xxxxxxxx -r

where xxxxxxxx is a serial number, any combination of letters and 
numbers, from 1 to 8 characters in length.

You may need to pause after the first command to give the OS time to 
recognize that the XDS110 has reconfigured as a different USB device.

Once the second command completes, the serial number is updated, and the 
debug probe should be ready to use.

*** Updating Firmware Using a JTAG Connection. ***

You can update the XDS110 firmware using a JTAG connection.  Contact 
your vendor for details on how to attache a JTAG cable and for what 
programmer tool you should use.

To use the LM Flash Utility from Stellaris:

Make sure to use the option to erase only the required pages of memory.

Flash the boot_loader.bin file to address 0x0000.
Flash the firmware.bin file to address 0x4000.

Power cycle the debug probe (unplug and replug it into the USB port).

The firmware is now updated, and the debug probe should be ready to use.

To use the flash tools from inside CCS:

Create a target configuration for your debug probe and select the
TM4C1294NCPDT device as the target.  Connect to the target and erase
the flash then load the appropriate boot_loader.afx file.

Power cycle the debug probe and then use xdsdfu to flash the firmware
as detailed above.

NOTE: Check with your vendor for the correct boot loader file to use.
      The included files may only work for the standard TI XDS110
      debug probes.  Your vendor may have made changes or added features
      that require the use of a custom boot loader.

*** Recovering a Bricked XDS110 Without JTAG ***

In the case that your XDS110 fails to enumerate as a USB device, or it
fails to enter DFU programming mode, you can attempt the following steps
to force it into DFU mode to recover:

1) Ground the TCK pin (sometimes labeled as TCLK or SWCLK, check with your
vendor for how to identify which pin to ground).

2) Unplug and re-plug the XDS110 into the host PC while the pin is grounded.

3) The XDS110 should now be in DFU programming mode and you can flash it 
using the xdsdfu utility as detailed above.

Note that this feature is currently only implemented in the XDS110 boot 
loader that was first available in emupack 5.1.537.0. If your XDS110's
boot loader is an earlier version, this procedure won't work, and you'll 
need to use JTAG to recover.
