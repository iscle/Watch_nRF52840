#!/bin/bash

adafruit-nrfutil dfu genpkg --dev-type 0x0052 --application image.bin dfu.zip
#adafruit-nrfutil dfu genpkg --dev-type 0x0052 --application Aimage.bin dfu-imgA.zip