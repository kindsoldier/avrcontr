/*
 * Copyright 2017 Oleg Borodin <onborodin@gmail.com>
 *
 */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <tools.h>

uint16_t str_len(uint8_t * str) {
    uint16_t i = 0;
    while (str[i] != 0)
        i++;
    return i;
}

uint16_t adc_get_fake_measure(int min, int max) {
    return (uint16_t)((rand() % (max - min)) + min) % 1024;
}

int get_rand(int min, int max) {
    return (rand() % (max - min)) + min;
}
