#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H

#include <stdint.h>

#define RING_BUFFER_SIZE 64

typedef struct
{
  volatile uint8_t write;
  volatile uint8_t read;
} ring_buffer_t;

/**
 * @brief Get a character from the ring buffer or \0 if empty
 */
char getch();

/**
 * @brief View a character from the ring buffer without advancing read head
 */
char peekch();

/**
 * @brief Put a character into the ring buffer
 * @param c Character to put in the ring buffer
 * @note Blocks until buffer is ready to be written
 */
void putch(char c);

#endif // _RINGBUFFER_H
