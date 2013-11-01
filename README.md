malp
====

A simple AVR based robot. 

Build
-----

Install required RPMs.

* avr-gcc
* avr-libc
* avr-binutils

Configure the project and locate dependencies.

    $ ./waf configure

Build the project and create HEX and EEP files for programming.

    $ ./waf build

Program
-------

Install required RPMs.

* avrdude

Assuming you are using the AVR ISP mkII and an ATTINY44 MCU.

    cd build/src
    avrdude -p attiny44 -c avrispmkii -P usb -U flash:w:malp.hex -U eeprom:w:malp.eep 
