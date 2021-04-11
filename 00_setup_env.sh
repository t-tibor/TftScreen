#/bin/bash

echo "Installing AVR toolchain"

sudo apt-get install binutils gcc-avr avr-libc avrdude uisp flex bison byacc

# to check the install location use:
# dpkg -L gcc-avr
# dpkg -L avr-libc
# dpkg -L avrdude

