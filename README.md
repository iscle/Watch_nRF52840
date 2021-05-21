Watch_nRF52840
add compiler : gcc

https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm

add SDK Nordic :

https://www.nordicsemi.com/Software-and-tools/Software/nRF5-SDK/Download

add openocd :

http://openocd.org/

*BUILD App :

mkdir build


cmake ../

make all

*Just Flash Bootloader :

./scripts/nrf52/flash-boot.sh

Jush Flash Firmware :

./scripts/nrf52/flash-app.sh

*Flash  Bootloader and Firmware :

./scripts/nrf52/flash-app-full.sh

*DFU OTA :

use nordic App : NRFConnect (runs on Android and iOS).

file DFU: /build/src/watch-app-dfu-x.xx.x.zip

https://devzone.nordicsemi.com/nordic/nordic-blog/b/blog/posts/common-faqs-on-dfu

