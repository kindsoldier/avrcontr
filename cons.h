/*
 * Copyright 2017 Oleg Borodin <onborodin@gmail.com>
 */

#include <font.h>
#include <lcd.h>
#ifndef CONSOLE_H_ITU
#define CONSOLE_H_ITU

typedef struct console {
    uint8_t width;
    uint8_t height;
    uint8_t line;
    uint8_t row;
    uint16_t xmax;
    uint16_t ymax;
    uint16_t xshift;
    uint16_t yshift;
    font_t *font;
    uint8_t *buffer;
    uint16_t buffer_len;
} console_t;

extern console_t console;

void console_init(void);

void console_render_char(uint8_t line, uint8_t row);
void console_render(void);
void console_shift(void);
void console_putc(uint8_t c);
int console_puts(uint8_t *str);

void console_render_xychar(uint8_t line, uint8_t row, uint8_t c);
void console_xyputc(uint16_t line, uint16_t row, uint8_t c);
int console_xyputs(uint16_t line, uint16_t row, uint8_t *str);

#endif
