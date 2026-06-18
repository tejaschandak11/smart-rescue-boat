/**
 * @file    detection.h
 * @brief   Obstacle and victim detection interface
 * @author  Tejas Chandak
 */

#ifndef DETECTION_H
#define DETECTION_H

#include <stdint.h>

#define VICTIM_IR_THRESHOLD   500   /* ADC threshold for IR victim detection */
#define ULTRASONIC_MAX_CM     400   /* Max reliable range of HC-SR04 */

void     Detection_Init(void);
uint16_t Detection_GetObstacleDistance(void);   /* Returns cm */
uint8_t  Detection_IsVictimDetected(void);       /* Returns 1 if victim found */

#endif /* DETECTION_H */
