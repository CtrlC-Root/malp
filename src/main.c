// MALP
#include "config.h"

// AVR
#include <util/delay.h>
#include <avr/interrupt.h>

/**
 * Run the firmware.
 */
int main()
{
    // initialize modules
    //remote_init(5);

    // enable interrupts
    sei();

    // program loop
    while(1)
    {
        // do nothing
        _delay_ms(500);
    }
}
