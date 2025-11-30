#include "ringbuffer.h"

static volatile ring_buffer_t rb;
static char buffer[RING_BUFFER_SIZE] = {0};

char getch()
{
  if (rb.read == rb.write)
  {
    return 0;
  }

  uint8_t next_read = (rb.read + 1) % RING_BUFFER_SIZE;

  char c = buffer[rb.read];
  rb.read = next_read;
  return c;
}

char peekch()
{
  if (rb.read == rb.write)
  {
    return 0;
  }

  return buffer[rb.read];
}

void putch(char c)
{

  uint8_t next_write = (rb.write + 1) % RING_BUFFER_SIZE;

  // Block until writing is ready
  while (next_write == rb.read)
    ;

  buffer[rb.write] = c;
  rb.write = next_write;
}