#include "serial.h"

#include <avr/interrupt.h>
#include <avr/sfr_defs.h>

#include "ringbuffer.h"

void serial_init(void) {
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;

  // Turn on the transmiter/receiver and set character size to 8
  UCSR0B |= _BV(TXEN0) | _BV(RXEN0);
  UCSR0C |= _BV(UCSZ00) | _BV(UCSZ01);

  // Turn on interrupts
  sei();
}

ISR(USART_UDRE_vect) {
  char c = getch();

  if (c == 0) {
    // Clear the interrupt flag from happening
    UCSR0B &= ~_BV(UDRIE0);
  } else {
    // Load the data register with character to send
    UDR0 = c;
  }
}

int serial_putchar(char c, FILE *stream) {
  char p = peekch();

  // Start of transmission means nothing in buffer
  if (p == 0 && bit_is_set(UCSR0A, UDRE0)) {
    UDR0 = (uint8_t)c;
    UCSR0B |= _BV(UDRIE0);
  } else {
    putch(c);

    // Transmission has completed and buffer is not empty
    if (p != 0 && bit_is_clear(UCSR0B, UDRIE0)) {
      UDR0 = getch();
      UCSR0B |= _BV(UDRIE0);
    }
  }

  return 0;
}

int serial_getchar(FILE *stream) {
  loop_until_bit_is_set(UCSR0A, RXC0);

  return UDR0;
}
