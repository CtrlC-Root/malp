// Definition
#include "queue.h"

// C Standard Library
#include <stdlib.h>

// create a queue
queue* queue_create(const uint8_t size)
{
    // allocate memory for the queue
    queue* q = (queue*) malloc(sizeof(uint8_t) * (3 + size));
    q->size = size;
    q->count = 0;
    q->pos = 0;
}

// destroy a queue
void queue_destroy(volatile queue* q)
{
    free((void*) q);
}

// push a byte
uint8_t queue_push(volatile queue* q, volatile uint8_t* data)
{
    // check if the queue is full
    if(q->count == q->size)
    {
        // no more room
        return -1;
    }

    // insert the byte at the front
    uint8_t newpos = (q->pos + q->count) % q->size;
    q->data[newpos] = *data;

    // keep track of length
    q->count++;

    // success
    return q->count;
}

// pop a byte
uint8_t queue_pop(volatile queue* q, volatile uint8_t* data)
{
    // check if the queue is empty
    if(q->count == 0)
    {
        // nothing to remove
        return -1;
    }

    // remote the byte from the back
    (*data) = q->data[q->pos];
    q->pos = (q->pos + 1) % q->size;

    // keep track of length
    q->count--;

    // success
    return q->count;
}
