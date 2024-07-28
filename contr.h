
/*
 * Copyright 2024 Oleg Borodin <onborodin@gmail.com>
 */

#ifndef CONTR_H_IUI
#define CONTR_H_IUI

#include <stdbool.h>
#include <stdint.h>

#ifndef CONTR_POWSUM_CAPA
#define CONTR_POWSUM_CAPA 42
#endif

#ifndef CONTR_POWMEAS_CAPA
#define CONTR_POWMEAS_CAPA 30
#endif

#ifndef DEFALUT_POWER_LIMIT
#define DEFALUT_POWER_LIMIT 3500
#endif

typedef struct {
        size_t power_summary_capa;
        size_t power_summary_pos;
        uint32_t power_summary[CONTR_POWSUM_CAPA];
        size_t power_measure_capa;
        size_t power_measure_pos;
        uint32_t power_measure[CONTR_POWMEAS_CAPA];

        size_t refl_summary_capa;
        size_t refl_summary_pos;
        uint16_t refl_summary[CONTR_POWSUM_CAPA];
        size_t refl_measure_capa;
        size_t refl_measure_pos;
        uint16_t refl_measure[CONTR_POWMEAS_CAPA];
        bool power_warning;
        bool refl_warning;
        int16_t power_limit;
} contr_t;

extern contr_t contr;

void contr_init(void);
void contr_main_loop(void);

void contr_add_power_measure(uint16_t measure);
uint32_t contr_calc_power(void);

void contr_add_refl_measure(uint16_t measure);
uint32_t contr_calc_refl(void);

#endif

