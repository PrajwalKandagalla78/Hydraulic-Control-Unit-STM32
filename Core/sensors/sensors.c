
#include "sensors.h"
#include <math.h>

/*
ADC channel order:

adc_raw[0] = V_SENSE
adc_raw[1] = MOS_TEMP
adc_raw[2] = CR_ADC (current)
adc_raw[3] = MOT_TEMP
adc_raw[4] = PRESS_SENSE
adc_raw[5] = LEVEL_SENSE
*/

/* ----- DMA buffer comes from main.c ----- */
extern uint16_t adc_raw[6];

/* ----- Private State ----- */

static sensor_data_t sdata;

/* ----- Constants ----- */

#define ADC_VREF        3.3f
#define ADC_MAX         4095.0f

/* ----- divider gains ----- */
#define BUS_DIV_GAIN    22.28f     // 100k / 4.7k
#define PRESS_DIV_GAIN  3.0f       // 20k / 10k

/* ----- NTC ----- */
#define NTC_R_FIXED     10000.0f
#define NTC_R0          10000.0f
#define NTC_BETA        3950.0f
#define NTC_T0          298.15f

/* ----- Local Helpers ----- */

static float adc_to_voltage(uint16_t raw)
{
    return (ADC_VREF * raw) / ADC_MAX;
}

/* ----- Individual Conversions ----- */

static float calc_bus_voltage(uint16_t raw)
{
    float v = adc_to_voltage(raw);
    return v * BUS_DIV_GAIN;
}

static float calc_current(uint16_t raw)
{
    float v = adc_to_voltage(raw);
    return (v / ADC_VREF) * 100.0f;   // 0–3.3V → 0–100A
}

static float calc_pressure(uint16_t raw)
{
    float v = adc_to_voltage(raw) * PRESS_DIV_GAIN;

    if(v < 0.5f) v = 0.5f;

    return (v - 0.5f) * (30.0f / 4.0f);
}

static float calc_level(uint16_t raw)
{
    return (raw / ADC_MAX) * 100.0f;
}

static float calc_ntc_temp(uint16_t raw)
{
    float v = adc_to_voltage(raw);

    if(v <= 0.01f) return -40.0f;
    if(v >= (ADC_VREF - 0.01f)) return 150.0f;

    float r = (v * NTC_R_FIXED) / (ADC_VREF - v);

    float tempK =
        1.0f / ((1.0f/NTC_T0) +
        (1.0f/NTC_BETA) * logf(r/NTC_R0));

    return tempK - 273.15f;
}

/* ----- Public API ----- */

void sensors_init(void)
{
    /* nothing required — DMA already started in main */
}

void sensors_update(void)
{
    sdata.bus_v    = calc_bus_voltage(adc_raw[0]);
    sdata.mos_temp = calc_ntc_temp(adc_raw[1]);
    sdata.current  = calc_current(adc_raw[2]);
    sdata.mot_temp = calc_ntc_temp(adc_raw[3]);
    sdata.pressure = calc_pressure(adc_raw[4]);
    sdata.level    = calc_level(adc_raw[5]);
}

sensor_data_t sensors_get(void)
{
    return sdata;
}


