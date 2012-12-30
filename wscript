#!/usr/bin/env python

def options(ctx):
    """Configure command line options."""

    ctx.add_option("--mcu", dest="mcu", default="attiny44", help="target microcontroller")

def configure(ctx):
    """Configure the project."""

    ctx.env.MCU = ctx.options.mcu

    ctx.find_program("avr-gcc", var="CC")
    ctx.find_program("avr-objcopy", var="OBJCOPY")

    ctx.recurse("src")

def build(ctx):
    """Build the project."""

    ctx.recurse("src")
