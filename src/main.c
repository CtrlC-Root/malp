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
        // wait for a command
		if(remote_codes->count == 0)
		{
			_delay_ms(100);
			continue;
		}

		// execute the next command
		uint8_t code;
		queue_pop(remote_codes, &code);

		switch(code)
		{
		case REMOTE_PLAY:
			motion_config(STOP, 0);
			break;

		case REMOTE_VDEC:
			motion_config(BACKWARD, 128);
			break;

		case REMOTE_VINC:
			motion_config(FORWARD, 128);
			break;

		case REMOTE_PREV:
			motion_config(LEFT, 128);
			break;

		case REMOTE_NEXT:
			motion_config(RIGHT, 128);
			break;
		}
    }
}
