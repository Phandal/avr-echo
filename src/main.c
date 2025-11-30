#define F_CPU 16000000
#define BAUD 9600

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stddef.h>
#include <util/delay.h>

#include "ringbuffer.h"

void ioinit();
static int usart_putchar(char c, FILE *stream);

ISR(USART_UDRE_vect)
{
  char c = getch();
  if (c == 0)
  {
    // Clear the interrupt flag from happening
    UCSR0B &= ~_BV(UDRIE0);
  }
  else
  {
    // Load the data register with character to send
    UDR0 = c;
  }
}

static FILE rb_stdout = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
  ioinit();
  sei();
  stdout = &rb_stdout;

  while (1)
  {
    printf("Hello");
    printf("There");
    _delay_ms(10000);
  }

  return 0;
}

void ioinit()
{
  // NOTE: F_CPU and BAUD must be set before including this header
#include <util/setbaud.h>
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;

  // Turn on the transmiter and set character size to 8
  UCSR0B |= _BV(TXEN0);
  UCSR0C |= _BV(UCSZ00) | _BV(UCSZ01);
}

int usart_putchar(char c, FILE *stream)
{

  char p = peekch();
  if (p == 0 && (bit_is_set(UCSR0A, UDRE0) || bit_is_clear(UCSR0B, UDRIE0)))
  {
    UDR0 = (uint8_t)c;
    UCSR0B |= _BV(UDRIE0);
  }
  else
  {
    putch(c);
  }

  // I think the problem is that data register is empty, however the read and write positions are not the same,
  // This means that the interrupt enable flas is turned off and never reenabled.
  if (bit_is_clear(UCSR0B, UDRIE0) && peekch() != 0)
  {
    UDR0 = getch();
    UCSR0B |= _BV(UDRIE0);
  }
  return 0;
}
