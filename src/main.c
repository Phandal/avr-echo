#define F_CPU 16000000
#define BAUD 9600

#include <stdio.h>
#include <util/delay.h>

#include "serial.h"

static FILE rb_stream = FDEV_SETUP_STREAM(serial_putchar, serial_getchar, _FDEV_SETUP_RW);

int main(void)
{
  serial_init();
  stdin = stdout = &rb_stream;

  while (1)
  {
    int c = getchar();
    putchar(c);
    _delay_ms(50);
  }

  return 0;
}