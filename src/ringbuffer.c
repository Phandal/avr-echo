#include "ringbuffer.h"

static volatile ring_buffer_t rb;

int getch() {
  if (rb.tail == rb.head) {
    return -1;
  }

  int c = rb.buffer[rb.tail];
  rb.tail = (rb.tail + 1) % RING_BUFFER_SIZE;
  ;
  return c;
}

int peekch() {
  if (rb.tail == rb.head) {
    return -1;
  }

  return rb.buffer[rb.tail];
}

void putch(char c) {

  uint8_t next_write = (rb.head + 1) % RING_BUFFER_SIZE;

  // Block until writing is ready
  while (next_write == rb.tail)
    ;

  rb.buffer[rb.head] = c;
  rb.head = next_write;
}
