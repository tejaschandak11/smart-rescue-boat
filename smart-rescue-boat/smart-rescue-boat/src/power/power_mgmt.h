/**
 * @file    power_mgmt.h / power_mgmt.c
 * @brief   Battery voltage monitoring and power state management
 * @author  Tejas Chandak
 *
 * Reads battery voltage via ADC on PA4 (through voltage divider).
 * 7.4V 2S LiPo: full = ~8.4V, critical = ~6.6V
 * Voltage divider (10kΩ / 10kΩ) halves the voltage for 3.3V ADC input.
 */

/* ── power_mgmt.h ── */
#ifndef POWER_MGMT_H
#define POWER_MGMT_H

#include <stdint.h>

#define BATTERY_CRITICAL_MV   6600   /* 6.6V — stop operation */
#define BATTERY_LOW_MV        7000   /* 7.0V — send low battery alert */
#define BATTERY_FULL_MV       8400   /* 8.4V — fully charged */

void     PowerMgmt_Init(void);
uint16_t PowerMgmt_GetBatteryMV(void);   /* Returns millivolts */
uint8_t  PowerMgmt_IsBatteryCritical(void);
uint8_t  PowerMgmt_IsBatteryLow(void);

#endif /* POWER_MGMT_H */


/* ── power_mgmt.c ── */
#include "power_mgmt.h"
#include "stm32f1xx_hal.h"

/* ADC handle — configured for PA4, single conversion, 12-bit */
/* extern ADC_HandleTypeDef hadc1; */  /* Uncomment after CubeMX config */

void PowerMgmt_Init(void)
{
    /* TODO: Configure ADC1 Channel 4 (PA4) in STM32CubeMX
     *       12-bit resolution, single conversion mode
     *       Call HAL_ADC_Start() here */
}

/**
 * @brief Read battery voltage via ADC and voltage divider
 * @return Battery voltage in millivolts
 */
uint16_t PowerMgmt_GetBatteryMV(void)
{
    /* TODO:
     * HAL_ADC_Start(&hadc1);
     * HAL_ADC_PollForConversion(&hadc1, 10);
     * uint32_t raw = HAL_ADC_GetValue(&hadc1);
     *
     * Conversion:
     *   adc_voltage_mv = (raw * 3300) / 4095
     *   battery_mv     = adc_voltage_mv * 2   (voltage divider ×2)
     *
     * return (uint16_t)battery_mv;
     */
    return BATTERY_FULL_MV; /* Placeholder until ADC is wired */
}

uint8_t PowerMgmt_IsBatteryCritical(void)
{
    return (PowerMgmt_GetBatteryMV() <= BATTERY_CRITICAL_MV) ? 1 : 0;
}

uint8_t PowerMgmt_IsBatteryLow(void)
{
    return (PowerMgmt_GetBatteryMV() <= BATTERY_LOW_MV) ? 1 : 0;
}
