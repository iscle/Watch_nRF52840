#!/usr/bin/env bash
JLinkExe -if swd -device nrf52 -speed 1000 -AutoConnect 1 -CommanderScript /home/hthang/Watch_nRF52840/scripts/nrf52/flash-app.jlink
