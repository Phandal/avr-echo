#ifndef _SERIAL_H
#define _SERIAL_H

// NOTE: F_CPU and BAUD must be defined before including this header
#ifndef F_CPU
#define F_CPU 16000000
#endif

#ifndef BAUD
#define BAUD 9600
#endif

#include <stdio.h>
#include <util/setbaud.h>

#include "ringbuffer.h"

/**
 * @brief Initialize the serial communication device
 */
void serial_init(void);

/**
 * @brief Used for setting up Write Stream with `stdio`.
 *
 * @note `FDEV_SETUP_STEAM`
 */
int serial_putchar(char c, FILE *stream);

/**
 * @brief Used for setting up Read Stream with `stdio`.
 *
 * @note `FDEV_SETUP_STREAM`
 */
int serial_getchar(FILE *stream);

#endif // SERIAL_H