/*
 * Copyright 2017 Oleg Borodin <onborodin@gmail.com>
 *
 */
#ifndef FONT8x14_H
#define FONT8x14_H

typedef struct {
    uint8_t width;
    uint8_t height;
    uint8_t start;
    uint8_t length;
    const uint8_t *bitmap;
} font_t;

#define BASEFONT_WIDTH  8
#define BASEFONT_HEIGTH 14

extern font_t basefont;

#endif
