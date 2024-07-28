/*
 * Copyright 2017 Oleg Borodin <onborodin@gmail.com>
 *
 */
#ifndef UART_H_ITU
#define UART_H_ITU

#include <fifo.h>

extern fifo_t uart_inbuf, uart_outbuf;
extern FILE uart_stream;

void uartio_init(void);

int uart_putchar(char c, FILE * stream);
int uart_getchar(FILE * stream);

#endif

