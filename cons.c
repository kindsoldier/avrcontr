/*
 * Copyright 2017 Oleg Borodin <onborodin@gmail.com>
 */
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <avr/pgmspace.h>

#include <lcd.h>
#include <font.h>
#include <cons.h>

console_t console;

#define BUFFER_SIZE LCD_WIDTH/BASEFONT_WIDTH * LCD_HEIGHT/BASEFONT_HEIGTH + 1
uint8_t console_buffer[BUFFER_SIZE];

void console_init(void) {
    console.line = 0;
    console.row = 0;
    console.xshift = 1;
    console.yshift = 1;
    console.xmax = LCD_WIDTH;
    console.ymax = LCD_HEIGHT;
    console.font = &basefont;
    console.width = LCD_WIDTH/BASEFONT_WIDTH;
    console.height = LCD_HEIGHT/BASEFONT_HEIGTH;
    console.buffer_len = console.width * console.height + 1;
    console.buffer = console_buffer;
}

void console_render_char(uint8_t line, uint8_t row) {
    uint8_t c = console.buffer[(console.width * line) + row];
    lcd_draw_char((console.xmax - (console.font->height * (line + 1))) + console.yshift,
                   (console.font->width * row) + console.xshift,
                    console.font, c);
}

void console_render(void) {
#if 0
    for (uint8_t line = console.height; line > 0; --line) {
        for (uint8_t row = console.width; row > 0; --row) {
            console_render_char(line - 1, row - 1);
        }
    }
#else
    for (uint8_t line = 0; line < console.height; line++) {
        for (uint8_t row = 0; row < console.width; row++) {
            console_render_char(line, row);
        }
    }
#endif
}

void console_shift(void) {
    uint16_t i = 0;
    uint16_t pos = console.width * (console.line - 1) + console.row;
    uint16_t end = console.width * console.height;

    while (i < (end - console.width)) {
        console.buffer[i] = console.buffer[i + console.width];
        i++;
    }
    while (i < end) {
        console.buffer[i] = ' ';
        i++;
    }

    if (console.line > 0)
        console.line--;
    else
        console.line = 0;
}

void console_putc(uint8_t c) {

    if ((console.row + 1) > console.width) {
        console.line++;
        console.row = 0;
    }

    if (console.line >= console.height) {
        console_shift();
        console_render();
    }
    console.buffer[(console.line * console.width) + console.row] = c;
    console_render_char(console.line, console.row);
    console.row++;
}

int console_puts(uint8_t *str) {
    uint8_t i = 0;
    while (str[i] != 0) {
        console_putc(str[i]);
        i++;
    }
    return i;
}

void console_render_xychar(uint8_t line, uint8_t row, uint8_t c) {
    lcd_draw_char(
        (console.xmax - (console.font->height * (line + 1))) + console.yshift,
        (console.font->width * row) + console.xshift,
        console.font, c);
}

void console_xyputc(uint16_t line, uint16_t row, uint8_t c) {
    if (row < console.width && line < console.height) {
        console_render_xychar(line, row, c);
    }
}

int console_xyputs(uint16_t line, uint16_t row, uint8_t *str) {
    uint8_t i = 0;
    while (str[i] != 0 && row < console.width && line < console.height) {
        console_render_xychar(line, row, str[i]);
        i++;
        row++;
    }
    return i;
}
