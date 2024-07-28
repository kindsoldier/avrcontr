
/*
 * Copyright 2017 Oleg Borodin <onborodin@gmail.com>
 *
 */

#ifndef SPI_H_ITU
#define SPI_H_ITU

#define PIN_SCK   PB5  // PIN 13
#define PIN_MISO  PB4  // PIN 12 MISO<-SDO
#define PIN_MOSI  PB3  // PIN 11 MOSI->SDA
#define PIN_SS    PB2  // PIN 10
#define PIN_RESET PB1  // PIN 09
#define PIN_A0    PB0  // PIN 08

void spi_init(void);
void spi_write_byte(uint8_t data);
uint8_t spi_read_byte(void);
void spi_write_word(uint16_t w);
void spi_write_word_array(uint16_t w, uint16_t n);

#endif

