// MALP
#include "motion.h"
#include "remote.h"

// AVR
#include <util/delay.h>
#include <avr/interrupt.h>

/**
 * Run the firmware.
 */
int main()
{
    // enable modules
    motion_enable();
    remote_enable(5);

    // enable interrupts
    sei();

    // program loop
    while(1)
    {
        // do nothing
        _delay_ms(500);
    }
}
