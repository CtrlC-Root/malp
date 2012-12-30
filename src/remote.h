// MALP
#include "config.h"

/**
 * Remote Control Module
 *
 * Protocol:
 * 1x 18 ms - Start Pulse
 * 8x  2 ms - Data Bits (PWC)
 *
 * The data bits are encoded with pulse width encoding. A pulse that is less
 * than 50% on is a zero and a pulse that is more than 50% on is a one.
 *
 * Volume Down - 000 11100 - 0
 * Volume Up   - 100 11100 - 4
 * Previous    - 001 11100 - 1
 * Next        - 101 11100 - 5
 * Play/Pause  - 011 11100 - 3
 *
 * The last 5 bits are always 11100 and may be intended to signal the end of
 * a message.
 */

/**
 * Remote control code.
 */
typedef uint8_t remote_code_t;

/**
 * Remote control buffer.
 */
typedef struct
{
    /**
     * Buffer size.
     */
    uint8_t size;

    /**
     * Buffer count.
     */
    uint8_t count;

    /**
     * Buffer data.
     */
    remote_code_t* data;
} remote_buffer_t;

/**
 * Remote control buffer. This is a circular buffer that is used to store
 * control codes. When the buffer fills up, no more remote control codes will
 * be stored.
 */
extern remote_buffer_t remote_buffer;

/**
 * Initialize the remote control module.
 */
void remote_init(uint8_t size);
