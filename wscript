#!/usr/bin/env python

def options(ctx):
    """Configure command line options."""

    # microcontroller
    ctx.add_option("--mcu", dest="mcu", default="attiny44", help="target microcontroller")
    #ctx.add_option("--mcu-hz", type="int", dest="speed_hz", help="mcu speed (Hz)")
    #ctx.add_option("--mcu-khz", type="int", dest="speed_khz", help="mcu speed (kHz)")
    #ctx.add_option("--mcu-mhz", type="int", dest="speed_mhz", default=8, help="mcu speed (MHz)")

def configure(ctx):
    """Configure the project."""

    # options
    ctx.env.MCU = ctx.options.mcu
    ctx.env.MCU_HZ = 8 * 1000 * 1000 # XXX make this an option

    # programs
    ctx.find_program("avr-gcc", var="CC")
    ctx.find_program("avr-objcopy", var="OBJCOPY")

    # recurse
    ctx.recurse("src")

def build(ctx):
    """Build the project."""

    # recurse
    ctx.recurse("src")
