#!/usr/bin/env bash
#  Package the repo for release

set -e  #  Exit when any command fails.
set -x  #  Echo all commands.

cd ..
set +e
rm Watch-rust-mynewt.7z
set -e
7z a Watch-rust-mynewt.7z Watch-rust-mynewt

set +x  #  Stop echoing all commands.
echo ✅ ◾ ️Done!
