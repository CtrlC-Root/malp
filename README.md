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

```
$ ./waf configure
```

Build the project and create HEX and EEP files for programming.

```
$ ./waf build
```

Program
-------

Install required RPMs.

* avrdude

Assuming you are using the AVR ISP mkII and an ATTINY44 MCU.

```
$ cd build/src
$ avrdude -p attiny44 -c avrispmkii -P usb -U flash:w:malp.hex -U eeprom:w:malp.eep
```

Schematic
---------

Install Eagle schematic editor and required part libraries.

* Eagle (http://www.cadsoftusa.com)
* SparkFun Part Library (https://github.com/sparkfun/SparkFun-Eagle-Libraries)
* CtrlC Part Library (https://github.com/CtrlC-Root/eagle-libs)

The Eagle project is in the ```doc/eagle``` directory.

Reference
---------

* https://learn.sparkfun.com/tutorials/how-to-install-and-setup-eagle
* https://learn.sparkfun.com/tutorials/using-eagle-schematic
