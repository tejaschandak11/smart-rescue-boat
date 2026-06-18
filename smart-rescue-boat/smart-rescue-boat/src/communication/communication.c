/**
 * @file    communication.c
 * @brief   Unified communication manager (Wi-Fi + Bluetooth)
 * @author  Tejas Chandak
 *
 * Aggregates commands from both Wi-Fi and Bluetooth.
 * Wi-Fi commands take priority over Bluetooth.
 */

#include "communication.h"
#include "main.h"  /* For SystemMode_t */

extern void WiFi_Init(void);
extern void WiFi_ProcessIncoming(void);
extern void Bluetooth_Init(void);
extern void Bluetooth_ProcessIncoming(void);
extern DriveCommand_t Bluetooth_GetLastCommand(void);

static DriveCommand_t active_command  = CMD_STOP;
static uint8_t        alert_ack       = 0;

void Communication_Init(void)
{
    WiFi_Init();
    Bluetooth_Init();
}

void Communication_ProcessIncoming(volatile void *mode_ptr)
{
    WiFi_ProcessIncoming();
    Bluetooth_ProcessIncoming();

    /* TODO: If mode-switch command received ('A' or 'M'),
     *       update *(SystemMode_t*)mode_ptr accordingly */
}

DriveCommand_t Communication_GetLastCommand(void)
{
    /* Wi-Fi takes priority; fall back to Bluetooth */
    return active_command;
}

void Communication_SendAlert(AlertType_t alert)
{
    /* TODO: Transmit alert string via UART1 (Wi-Fi) and UART2 (BT)
     *       Format: "ALERT:VICTIM_FOUND\r\n" etc. */
    alert_ack = 0; /* Reset ack flag on new alert */
    (void)alert;
}

uint8_t Communication_IsAlertAcknowledged(void)
{
    return alert_ack;
}
