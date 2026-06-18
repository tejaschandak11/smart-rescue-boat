/**
 * @file    communication.h
 * @brief   Wi-Fi (ESP8266) and Bluetooth (HC-05) communication interface
 * @author  Tejas Chandak
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include "navigation/navigation.h"

/* ─── Alert Types ────────────────────────────────────────────── */
typedef enum {
    ALERT_VICTIM_FOUND = 0,
    ALERT_LOW_BATTERY,
    ALERT_OBSTACLE_BLOCKED,
    ALERT_SYSTEM_OK
} AlertType_t;

/* ─── Public API ─────────────────────────────────────────────── */
void            Communication_Init(void);
void            Communication_ProcessIncoming(volatile void *mode_ptr);
DriveCommand_t  Communication_GetLastCommand(void);
void            Communication_SendAlert(AlertType_t alert);
uint8_t         Communication_IsAlertAcknowledged(void);

#endif /* COMMUNICATION_H */
