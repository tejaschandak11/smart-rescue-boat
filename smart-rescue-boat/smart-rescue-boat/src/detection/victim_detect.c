/**
 * @file    victim_detect.c
 * @brief   IR sensor-based victim detection logic
 * @author  Tejas Chandak
 *
 * Uses FC-51 IR sensor (digital output) on PB5.
 * A LOW signal indicates an object/person detected within range.
 */

#include "detection.h"
#include "stm32f1xx_hal.h"

#define IR_SENSOR_PIN   GPIO_PIN_5   /* PB5 */
#define IR_SENSOR_PORT  GPIOB

/**
 * @brief Check if IR sensor has triggered (victim/object detected)
 * @return 1 if victim detected, 0 otherwise
 */
uint8_t Detection_IsVictimDetected(void)
{
    /* FC-51 outputs LOW when object is detected */
    return (HAL_GPIO_ReadPin(IR_SENSOR_PORT, IR_SENSOR_PIN) == GPIO_PIN_RESET) ? 1 : 0;

    /* TODO: Add debouncing — require N consecutive detections
     *       to avoid false positives from water reflections */
}
