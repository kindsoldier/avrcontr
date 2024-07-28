/*
 * Copyright 2017 Oleg Borodin <onborodin@gmail.com>
 *
 */
#include <stdio.h>
#include <stdbool.h>

#include <fifo.h>
#include <uartio.h>

static uint8_t inbuf[FIFO_BUFFER_SIZE];
static uint8_t outbuf[FIFO_BUFFER_SIZE];

fifo_t uart_inbuf, uart_outbuf;

FILE uart_stream = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

int uart_putchar(char c, FILE * stream) {
    return fifo_putc(&uart_outbuf, c);
}

int uart_getchar(FILE * stream) {
    return (int)fifo_getc(&uart_inbuf);
}

void uartio_init(void) {
    fifo_init(&uart_inbuf, inbuf, sizeof(inbuf));
    fifo_init(&uart_outbuf, outbuf, sizeof(outbuf));
    stdout = &uart_stream;
    stdin = &uart_stream;
    stderr = &uart_stream;
}

