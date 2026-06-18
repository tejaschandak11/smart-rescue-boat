/**
 * @file    obstacle.c
 * @brief   HC-SR04 ultrasonic obstacle detection
 * @author  Tejas Chandak
 *
 * Measures distance using ultrasonic echo timing.
 * Trigger pulse → measure echo HIGH duration → convert to cm.
 *
 * Formula: distance_cm = (echo_time_us) / 58
 */

#include "detection.h"
#include "stm32f1xx_hal.h"

/* ─── Pin Definitions (update to match your wiring) ─────────── */
#define TRIG_PIN    GPIO_PIN_0   /* PB0 */
#define ECHO_PIN    GPIO_PIN_1   /* PB1 */
#define SENSOR_PORT GPIOB

/* ─── Private Helper ─────────────────────────────────────────── */

/**
 * @brief Microsecond delay using DWT cycle counter
 *        (Enable DWT in SystemClock_Config for this to work)
 */
static void delay_us(uint32_t us)
{
    uint32_t start = DWT->CYCCNT;
    uint32_t cycles = us * (SystemCoreClock / 1000000U);
    while ((DWT->CYCCNT - start) < cycles);
}

/* ─── Public Implementation ──────────────────────────────────── */

void Detection_Init(void)
{
    /* TODO: Configure PB0 as GPIO_MODE_OUTPUT_PP (trigger)
     *       Configure PB1 as GPIO_MODE_INPUT       (echo)
     *       Enable DWT for microsecond timing */
}

/**
 * @brief Trigger ultrasonic pulse and measure return time
 * @return Distance in centimetres (0 if timeout)
 */
uint16_t Detection_GetObstacleDistance(void)
{
    uint32_t echo_start = 0, echo_end = 0;
    uint32_t timeout = 30000; /* ~30 ms timeout */

    /* Send 10 µs trigger pulse */
    HAL_GPIO_WritePin(SENSOR_PORT, TRIG_PIN, GPIO_PIN_RESET);
    delay_us(2);
    HAL_GPIO_WritePin(SENSOR_PORT, TRIG_PIN, GPIO_PIN_SET);
    delay_us(10);
    HAL_GPIO_WritePin(SENSOR_PORT, TRIG_PIN, GPIO_PIN_RESET);

    /* Wait for echo to go HIGH */
    while (HAL_GPIO_ReadPin(SENSOR_PORT, ECHO_PIN) == GPIO_PIN_RESET) {
        if (--timeout == 0) return ULTRASONIC_MAX_CM;
    }
    echo_start = DWT->CYCCNT;

    /* Wait for echo to go LOW */
    timeout = 30000;
    while (HAL_GPIO_ReadPin(SENSOR_PORT, ECHO_PIN) == GPIO_PIN_SET) {
        if (--timeout == 0) return ULTRASONIC_MAX_CM;
    }
    echo_end = DWT->CYCCNT;

    /* Convert elapsed cycles to microseconds then to cm */
    uint32_t elapsed_us = (echo_end - echo_start) / (SystemCoreClock / 1000000U);
    return (uint16_t)(elapsed_us / 58U);
}
