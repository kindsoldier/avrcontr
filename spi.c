/*
 * Copyright 2017 Oleg Borodin <onborodin@gmail.com>
 *
 */

#include <avr/io.h>
#include <tools.h>
#include <spi.h>

void spi_init(void) {
    /* Set PIN_MISO as input */
    REG_SETDOWN_BIT(DDRB, PIN_MISO);
    /* Set PIN_SS as output */
    REG_SETUP_BIT(DDRB, PIN_SS);
    REG_SETUP_BIT(DDRB, PIN_MOSI);
    REG_SETUP_BIT(DDRB, PIN_SCK);
    REG_SETUP_BIT(DDRB, PIN_RESET);
    REG_SETUP_BIT(DDRB, PIN_A0);
    /* Down SS */
    REG_SETUP_BIT(PORTB, PIN_SS);
    /* Set master mode */
    REG_SETUP_BIT(SPCR, MSTR);
    /* Set speed */
    REG_SETDOWN_BIT(SPCR, SPR0);
    REG_SETDOWN_BIT(SPCR, SPR1);
    /* Set duble speed */
    REG_SETUP_BIT(SPCR, SPI2X);
    /* Set order */
    REG_SETDOWN_BIT(SPCR, DORD);
    /* Set mode */
    REG_SETDOWN_BIT(SPCR, CPOL);
    REG_SETDOWN_BIT(SPCR, CPHA);
    /* Enable SPI */
    REG_SETUP_BIT(SPCR, SPE);
}

inline void spi_write_byte(uint8_t data) {
    SPDR = data;
    while (!(SPSR & (1 << SPIF)));
}

inline uint8_t spi_read_byte(void) {
    SPDR = 0xFF;
    while (!(SPSR & (1 << SPIF)));
    return SPDR;
}

inline void spi_select_mcp(void) {
    REG_SETDOWN_BIT(PORTB, PIN_SS);
}

inline void spi_unselect_mcp(void) {
    REG_SETUP_BIT(PORTB, PIN_SS);
}

void spi_enable(void) {
    REG_SETUP_BIT(SPCR, SPE);
}

void spi_disable(void) {
    REG_SETDOWN_BIT(SPCR, SPE);
}

void spi_write_word(uint16_t w) {
    spi_write_byte(w >> 8);
    spi_write_byte(w & 0xff);
}

void spi_write_word_array(uint16_t w, uint16_t n) {
    while (n--)
        spi_write_word(w);
}



