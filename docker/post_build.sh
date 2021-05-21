#!/bin/sh
export LC_ALL=C.UTF-8
export LANG=C.UTF-8
set -x

mkdir -p /sources/build/output
/opt/mcuboot/scripts/imgtool.py create --align 4 --version 1.0.0 --header-size 32 --slot-size 475136 --pad-header /sources/build/src/Watch-mcuboot-app-0.9.0.bin /sources/build/output/image-0.9.0.bin
adafruit-nrfutil dfu genpkg --dev-type 0x0052 --application /sources/build/output/image-0.9.0.bin /sources/build/output/dfu-0.9.0.zip

cp /sources/build/src/*.bin /sources/build/output/
cp /sources/build/src/*.hex /sources/build/output/
cp /sources/build/src/*.out /sources/build/output/
cp /sources/build/src/*.map /sources/build/output/
cp /sources/bootloader/bootloader-5.0.4.bin /sources/build/output/bootloader.bin


