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

TODO
----

Add support to the motor module for acceleration curves. The current approach
of specifying a speed doesn't take into account the natural acceleration of the
motor. In other words, the speed parameter currently controls how fast the
motors reach their cruising speed, not the cruising speed. This could be fixed
by adjusting the speed (in the timer overflow stub that's currently commented
out) continuously.
