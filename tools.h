/*
 * Copyright 2017 Oleg Borodin <onborodin@gmail.com>
 *
 */
#ifndef TOOLS_H_IRT
#define TOOLS_H_IRT


#define MAX_LINE_LEN 1024

#define REG_SETUP_BIT(reg, bit)    (reg) |= (1 << (bit))
#define REG_SETDOWN_BIT(reg, bit)  (reg) &= ~(1 << (bit))
#define REG_BIT_ISUP(reg, bit)    ((reg) & (1 << (bit)))
#define REG_SETVAL(reg, value)  ((reg) = (value))

#define REG_SETUP(reg, value)  ((reg) |= (value))
#define BIT(bit)  (1 << (bit))

uint16_t str_len(uint8_t * str);

uint16_t adc_get_fake_measure(int min, int max);
#endif
