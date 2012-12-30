// MALP
#include "remote.h"

// remote buffer
remote_buffer_t remote_buffer;

// initialize remote module
void remote_init(uint8_t size)
{
    // initialize the buffer
    remote_buffer.count = 0;
    remote_buffer.size = size;
    remote_buffer.data = (remote_code_t*) malloc(sizeof(remote_code_t) * size);
}
