#pragma once

// AVR
#include <avr/io.h>

/**
 * Motion module.
 *
 * TODO document the module
 */

/**
 * Action type.
 */
typedef enum { IDLE, STOP, FORWARD, BACKWARD, LEFT, RIGHT } motion_action_t;

/**
 * Enable the motion module.
 */
void motion_enable();

/**
 * Disable the motion module.
 */
void motion_disable();

/**
 * Configure the module.
 *
 * @param action action type
 * @param speed action speed
 */
void motion_config(motion_action_t action, uint8_t speed);
