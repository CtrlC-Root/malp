// Definitions
#include "motion.h"

// enable the module
void motion_enable()
{
    // configure output pins
    DDRA |= (1<<PA4)|(1<<PA5);
    DDRB |= (1<<PB0)|(1<<PB1);

    // enable the timer
    TCCR0A = (1<<WGM00);            // phase correct PWM mode
    TCCR0B = (1<<CS02)|(1<<CS00);   // 1/1024 clock

    // enable timer interrupts
    // XXX TIMSK0 = (1<<TOIE0);

    // idle the motors
    motion_config(IDLE, 0);
}

// disable the module
void motion_disable()
{
    // idle the motors
    motion_config(IDLE, 0);

    // disable timer interrupts
    // XXX TIMSK0 = 0;

    // disable the timer
    TCCR0A = 0;
    TCCR0B = 0;
}

//ISR(TIM0_OVF_vect)
//{
    // XXX something every 65 milliseconds, or ~15 times a second
//}

// configure the module
void motion_config(motion_action_t action, uint8_t speed)
{
    // check the action
    switch(action)
    {
        // allow the motors to spin freely
        case IDLE:
        {
            PORTA &= ~(1<<PA4) & ~(1<<PA5);
            PORTB &= ~(1<<PB0) & ~(1<<PB1);
        } break;

        // stop the motors from moving
        case STOP:
        {
            PORTA |= (1<<PA4)|(1<<PA5);
            PORTB |= (1<<PB0)|(1<<PB1);
        } break;

        // move the robot
        case FORWARD:
        {
            PORTA &= ~(1<<PA4);
            PORTA |= (1<<PA5);

            PORTB &= ~(1<<PB0);
            PORTB |= (1<<PB1);
        } break;

        case BACKWARD:
        {
            PORTA &= ~(1<<PA5);
            PORTA |= (1<<PA4);

            PORTB &= ~(1<<PB1);
            PORTB |= (1<<PB0);
        } break;

        // turn the robot
        case LEFT:
        {
            PORTA &= ~(1<<PA4);
            PORTA |= (1<<PA5);

            PORTB &= ~(1<<PB1);
            PORTB |= (1<<PB0);
        } break;

        case RIGHT:
        {
            PORTA &= ~(1<<PA5);
            PORTA |= (1<<PA4);

            PORTB &= ~(1<<PB0);
            PORTB |= (1<<PB1);
        } break;
    }

    // check if this is an IDLE action
    if(action == IDLE)
    {
        // disable the PWM output
        TCCR0A &= ~(1<<COM0A1) & ~(1<<COM0A0);
    }
    else
    {
        // update the PWM speed
        OCR0A = speed;

        // enable the PWM output
        TCCR0A |= (1<<COM0A1);
    }
}
