# The MSP432 Launchpad

Install GCC cross compiler for ARM Cortex-A/R/M processors. On debian 8.4 this worked.

    $ apt-get remove binutils-arm-none-eabi
    $ apt-get remove gcc-arm-none-eabi
    $ add-apt-repository ppa:terry.guo/gcc-arm-embedded
    $ apt-get update
    $ apt-get install gcc-arm-none-eabi


## Building for MSP432

    $ make CROSS=1


