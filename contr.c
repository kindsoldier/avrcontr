/*
 * Copyright 2024 Oleg Borodin <onborodin@gmail.com>
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include <util/delay.h>

#include <cons.h>
#include <contr.h>

contr_t contr;

void contr_init(void) {
        contr.power_warning = false;
        contr.refl_warning = false;

        contr.power_limit = DEFALUT_POWER_LIMIT;

        contr.power_summary_capa = CONTR_POWSUM_CAPA;
        contr.power_summary_pos = 0;
        for (size_t i = 0; i < contr.power_summary_capa; i++) {
                contr.power_summary[i] = 0;
        }
        contr.power_measure_capa = CONTR_POWMEAS_CAPA;
        contr.power_measure_pos = 0;
        for (size_t i = 0; i < contr.power_measure_capa; i++) {
                contr.power_measure[i] = 0;
        }
        contr.refl_summary_capa = CONTR_POWSUM_CAPA;
        contr.refl_summary_pos = 0;
        for (size_t i = 0; i < contr.refl_summary_capa; i++) {
                contr.refl_summary[i] = 0;
        }
        contr.refl_measure_capa = CONTR_POWMEAS_CAPA;
        contr.refl_measure_pos = 0;
        for (size_t i = 0; i < contr.refl_measure_capa; i++) {
                contr.refl_measure[i] = 0;
        }
}

void contr_add_power_measure(uint16_t measure) {
        contr.power_measure_pos++;
        if (contr.power_measure_pos >= contr.power_measure_capa) {
                contr.power_measure_pos = 0;
                int32_t power_summary = 0;
                for (size_t i = 0; i < contr.power_measure_capa; i++) {
                        power_summary += contr.power_measure[i];
                }
                contr.power_summary_pos++;
                if (contr.power_summary_pos >= contr.power_summary_capa) {
                        contr.power_summary_pos = 0;
                }
                contr.power_summary[contr.power_summary_pos] = power_summary;
        }
        contr.power_measure[contr.power_measure_pos] = measure;
}

uint32_t contr_calc_power(void) {
        uint32_t power_summary = 0;
        for (size_t i = 0; i < contr.power_summary_capa; i++) {
                power_summary += (contr.power_summary[i] / contr.power_measure_capa);
        }
        return (power_summary / contr.power_summary_capa);
}

void contr_add_refl_measure(uint16_t measure) {
        contr.refl_measure_pos++;
        if (contr.refl_measure_pos >= contr.refl_measure_capa) {
                contr.refl_measure_pos = 0;
                int32_t refl_summary = 0;
                for (size_t i = 0; i < contr.refl_measure_capa; i++) {
                        refl_summary += contr.refl_measure[i];
                }
                contr.refl_summary_pos++;
                if (contr.refl_summary_pos >= contr.refl_summary_capa) {
                        contr.refl_summary_pos = 0;
                }
                contr.refl_summary[contr.refl_summary_pos] = refl_summary;
        }
        contr.refl_measure[contr.refl_measure_pos] = measure;
}

uint32_t contr_calc_refl(void) {
        uint32_t refl_summary = 0;
        for (size_t i = 0; i < contr.refl_summary_capa; i++) {
                refl_summary += (contr.refl_summary[i] / contr.refl_measure_capa);
        }
        return (refl_summary / contr.refl_summary_capa);
}

void contr_main_loop(void) {
        int16_t counter = 0;
        uint8_t power_sum_str[12];
        uint8_t refl_sum_str[12];
        uint8_t counter_str[12];

        int32_t power_sum = 0;
        int32_t refl_sum = 0;
        while (true) {
                if ((counter % 2) == 1) {
                        power_sum = contr_calc_power();
                        refl_sum = contr_calc_refl();

                        uint8_t power_warn_char = ' ';
                        contr.power_warning = false;
                        if (power_sum > contr.power_limit) {
                                contr.power_warning = true;
                                power_warn_char = '!';
                        }
                        sprintf(power_sum_str, "PWR: %5.1f %c",
                                ((float)power_sum) / 100, power_warn_char);
                        console_xyputs(2, 2, power_sum_str);

                        sprintf(refl_sum_str, "REF: %5.1f", ((float)refl_sum) / 100);
                        console_xyputs(3, 2, refl_sum_str);
                }
                sprintf(counter_str, "CNT: %05d", counter++ % 100);
                console_xyputs(6, 2, counter_str);
                _delay_ms(100);
                if (counter >= 1000) { counter = 0; }
        }
}
