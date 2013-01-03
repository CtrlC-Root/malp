// MALP
#include "remote.h"

// AVR
#include <avr/interrupt.h>

// control code queue
volatile queue* remote_codes;

// module state
volatile enum { IDLE, SENSE, DATA_HIGH, DATA_LOW } state;

// pulse start timestamp
volatile uint16_t start;

// received bits
volatile uint8_t bits;

// control code
volatile uint8_t code;

// timer overflows
volatile uint8_t overflows;

// enable module
void remote_enable(uint8_t queue_size)
{
    // create the queue
    remote_codes = queue_create(queue_size);

    // initial state
    state = IDLE;

    // enable the timer
    TCCR1A = 0;             // normal operation mode
    TCCR1B = (1<<CS11);     // 1/8 clock, input capture on falling edge

    // enable the timer interrupts
    TIMSK1 = (1<<TOIE1)|(1<<ICIE1);
}

// disable module
void remote_disable()
{
    // disable the timer interrupts
    TIMSK1 = 0;

    // disable the timer
    TCCR1A = 0;
    TCCR1B = 0;

    // destroy the queue
    queue_destroy(remote_codes);
}

// timer 1 overflow interrupt.
ISR(TIM1_OVF_vect)
{
    // count overflows
    overflows++;
}

// timer 1 input capture interrupt.
ISR(TIM1_CAPT_vect)
{
    // capture the timer value
    uint16_t value = (ICR1H<<8)|ICR1L;

    // check if we're in the IDLE or DATA_HIGH states
    if(state == IDLE || state == DATA_HIGH)
    {
        // configure the input capture for a rising edge
        TCCR1B |= (1<<ICES1);

        // keep track of the pulse start
        start = value;
        overflows = 0;

        // check if this is the first pulse
        if(state == IDLE)
        {
            state = SENSE;
        }
        // start of a data pulse
        else
        {
            state = DATA_LOW;
        }

        // done
        return;
    }

    // check if the pulse is too long to measure
    if(overflows > 1)
    {
        // start over
        state = IDLE;
        return;
    }

    // configure the input capture for a falling edge
    TCCR1B &= ~(1<<ICES1);

    // calculate the pulse width
    uint16_t width = value - start;

    // check if we were measuring the first pulse
    if(state == SENSE)
    {
        // was it a start pulse
        if(width > 20480)
        {
            // clear the code
            code = 0;
            bits = 0;

            // start recording data bits
            state = DATA_HIGH;
        }
        else
        {
            // start over
            state = IDLE;
        }
    }
    // measuring a data pulse
    else
    {
        // check if it was valid
        if(width < 2048)
        {
            // record the bit
            code = (code << 1) | (width > 1024);
            bits++;

            // check if there are more bits
            if(bits < 8)
            {
                // wait for the next data pulse
                state = DATA_HIGH;
            }
            // no more bits
            else
            {
                // store the code
                code = code >> 5;
                queue_push(remote_codes, &code);

                // start over
                state = IDLE;
            }
        }
        // noise or interference
        else
        {
            // start over
            state = IDLE;
        }
    }
}
