/*
 * Copyright 2017 Oleg Borodin <onborodin@gmail.com>
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define BAUD 38400
#include <util/setbaud.h>

#include <tools.h>
#include <uartio.h>
#include <spi.h>
#include <cons.h>
#include <contr.h>

#define TIMER_INITVAL 128

/* Timer0 interrupt */
ISR(TIMER0_OVF_vect) {
    volatile uint16_t power_measure = adc_get_fake_measure(0, 700) * 10;
    volatile uint16_t refl_measure = power_measure / 10;
    contr_add_power_measure(power_measure);
    contr_add_refl_measure(refl_measure);

    volatile uint8_t c;
    while ((c = fifo_getc(&uart_outbuf)) > 0) {
        while(!REG_BIT_ISUP(UCSR0A, UDRE0));
        UDR0 = c;
    }
    REG_SETUP(TCNT0, TIMER_INITVAL);
}

/* Timer0 init */
void timer0_init(void) {
    /* Disable comparators */
    REG_SETDOWN_BIT(TCCR0A, COM0A1);
    REG_SETDOWN_BIT(TCCR0A, COM0A0);
    REG_SETDOWN_BIT(TCCR0A, COM0B1);
    REG_SETDOWN_BIT(TCCR0A, COM0B0);
    /* Set normal mode */
    REG_SETDOWN_BIT(TCCR0A, WGM01);
    REG_SETDOWN_BIT(TCCR0A, WGM00);
    /* Set clock to 1/64 */
    REG_SETDOWN_BIT(TCCR0B, CS02);
    REG_SETUP_BIT(TCCR0B, CS01);
    REG_SETUP_BIT(TCCR0B, CS00);
    /* Enable timer interrupt */
    REG_SETUP_BIT(TIMSK0,TOIE0);
    REG_SETUP(TCNT0, TIMER_INITVAL);
}

void uart_init(void) {
    /* Set port speed */
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    /* Disable double speed operation */
    REG_SETDOWN_BIT(UCSR0A, U2X0);
    /* Set character size to 8 bit */
    REG_SETDOWN_BIT(UCSR0B, UCSZ02);
    REG_SETUP_BIT(UCSR0C, UCSZ01);
    REG_SETUP_BIT(UCSR0C, UCSZ00);
    /* Set one stop bit, no parity */
    REG_SETDOWN_BIT(UCSR0C, USBS0);
    REG_SETDOWN_BIT(UCSR0C, UPM00);
    REG_SETDOWN_BIT(UCSR0C, UPM01);
    /* Enable TX and RX */
    REG_SETUP_BIT(UCSR0B, TXEN0);
    REG_SETUP_BIT(UCSR0B, RXEN0);
    /* Disable receive & transmit interrupts */
    REG_SETDOWN_BIT(UCSR0B, RXCIE0);
    REG_SETDOWN_BIT(UCSR0B, UDRIE0);
    _delay_ms(20);
}

void rand_init(void) {
    srand(0);
}

int main() {
    rand_init();
    uartio_init();
    uart_init();
    timer0_init();
    spi_init();
    lcd_init();
    console_init();
    contr_init();
    lcd_clear();
    sei();
    contr_main_loop();
}
