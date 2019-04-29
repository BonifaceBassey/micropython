#!/bin/bash

TOP=`pwd`
TOOLCHAIN=${TOP}/toolchain

if [ ! -d "$TOOLCHAIN" ]; then
    read -p "Toolchain directory not found. Download? (y/n)? " choice
    case "$choice" in 
        y|Y ) 
            wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/7-2018q2/gcc-arm-none-eabi-7-2018-q2-update-linux.tar.bz2    
            tar -xjvf gcc-arm-none-eabi-7-2018-q2-update-linux.tar.bz2
            mv gcc-arm-none-eabi-7-2018-q2-update toolchain
	    rm gcc-arm-none-eabi-7-2018-q2-update-linux.tar.bz2
            ;;
        n|N )
            echo -e "\x1B[01;93m$(date +%s) Goodbye! \x1B[0m" && exit 1 
            ;;
        * ) echo -e "\x1B[01;93m$(date +%s) Invalid choice \x1B[0m" && exit 1;;
    esac
else
	echo "Toolchain directory already found. Run make CROSS=1"
fi

#wget http://software-dl.ti.com/ccs/esd/uniflash/uniflash_sl.4.5.0.2056.run
