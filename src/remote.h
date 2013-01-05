#pragma once

// MALP
#include "queue.h"

// C Standard Library
#include <stdint.h>

/**
 * Remote Control Module. The module requires an 8 MHz clock, the 16bit timer,
 * and an IR reciever connected to the ICP pin.
 *
 * 1x 18 ms - Start Pulse
 * 8x  2 ms - Data Bits (PWC)
 *
 * The data bits are encoded with pulse width encoding. A pulse that is less
 * than 50% on is a zero and a pulse that is more than 50% on is a one.
 *
 * Volume Down - 000 11100 - 0
 * Previous    - 001 11100 - 1
 * Play/Pause  - 011 11100 - 3
 * Volume Up   - 100 11100 - 4
 * Next        - 101 11100 - 5
 *
 * The last 5 bits are always 11100 and may be intended to signal the end of
 * a message.
 */

/**
 * Control code queue.
 */
extern volatile queue* remote_codes;

/**
 * Enable the remote control module.
 *
 * @param queue_size size of the control code queue
 */
void remote_enable(uint8_t queue_size);

/**
 * Disable the remote control module.
 */
void remote_disable();
