#pragma once

// C Standard Library
#include <stdint.h>

/**
 * A FIFO queue.
 */
typedef struct {
    /**
     * Size.
     */
    uint8_t size;

    /**
     * Data index.
     */
    uint8_t pos;

    /**
     * Data count.
     */
    uint8_t count;

    /**
     * Data.
     */
    uint8_t data[1];
} queue;

/**
 * Create a queue.
 *
 * @param size queue size
 * @returns queue pointer
 */
queue* queue_create(const uint8_t size);

/**
 * Destroy a queue.
 *
 * @param q queue pointer
 */
void queue_destroy(volatile queue* q);

/**
 * Push a byte.
 *
 * @param q queue pointer
 * @param data data byte
 * @returns queue size on success, -1 on failure
 */
uint8_t queue_push(volatile queue* q, volatile uint8_t* data);

/**
 * Pop a byte.
 *
 * @param q queue pointer
 * @param data data byte
 * @returns queue size on success, -1 on failure
 */
uint8_t queue_pop(volatile queue* q, volatile uint8_t* data);
