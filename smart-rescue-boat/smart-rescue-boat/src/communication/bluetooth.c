/**
 * @file    bluetooth.c
 * @brief   HC-05 Bluetooth communication via UART2
 * @author  Tejas Chandak
 *
 * UART2: PA2 (TX) → HC-05 RX,  PA3 (RX) → HC-05 TX  @ 9600 baud
 *
 * Paired with a phone app (e.g. Bluetooth Terminal) for manual override.
 * Uses same single-byte command protocol as Wi-Fi handler.
 */

#include "communication.h"
#include "stm32f1xx_hal.h"

static DriveCommand_t bt_last_command = CMD_STOP;

void Bluetooth_Init(void)
{
    /* TODO: Configure UART2 at 9600 baud (HC-05 default)
     *       Enable UART2 RX interrupt with HAL_UART_Receive_IT() */
}

void Bluetooth_ProcessIncoming(void)
{
    /* TODO: Read UART2 RX data
     *       Parse single-byte commands: F/B/L/R/S/A/M
     *       Update bt_last_command accordingly */
}

DriveCommand_t Bluetooth_GetLastCommand(void)
{
    return bt_last_command;
}
