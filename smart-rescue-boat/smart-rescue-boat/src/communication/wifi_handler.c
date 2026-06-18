/**
 * @file    wifi_handler.c
 * @brief   ESP8266 Wi-Fi communication via AT commands over UART1
 * @author  Tejas Chandak
 *
 * Communicates with ESP8266 using AT command set.
 * UART1: PA9 (TX) → ESP RX,  PA10 (RX) → ESP TX  @ 115200 baud
 *
 * Command protocol (simple TCP packet):
 *   'F' = Forward  |  'B' = Backward
 *   'L' = Left     |  'R' = Right
 *   'S' = Stop     |  'A' = Autonomous mode
 *   'M' = Manual mode
 */

#include "communication.h"
#include "stm32f1xx_hal.h"
#include <string.h>

/* ─── Configuration ──────────────────────────────────────────── */
#define WIFI_SSID       "your_network_name"    /* <-- UPDATE THIS */
#define WIFI_PASSWORD   "your_password"        /* <-- UPDATE THIS */
#define SERVER_PORT     8080

/* ─── Private State ──────────────────────────────────────────── */
static DriveCommand_t last_command    = CMD_STOP;
static uint8_t        alert_ack_flag  = 0;
static uint8_t        rx_buffer[32]   = {0};

/* ─── Private Helpers ────────────────────────────────────────── */

static void WiFi_SendAT(const char *cmd)
{
    /* TODO: Transmit AT command string via UART1 using HAL_UART_Transmit() */
    (void)cmd;
}

static void WiFi_ParseCommand(uint8_t byte)
{
    switch (byte) {
        case 'F': last_command = CMD_FORWARD;    break;
        case 'B': last_command = CMD_BACKWARD;   break;
        case 'L': last_command = CMD_TURN_LEFT;  break;
        case 'R': last_command = CMD_TURN_RIGHT; break;
        case 'S': last_command = CMD_STOP;       break;
        case 'K': alert_ack_flag = 1;            break; /* ACK from remote */
        default:  break;
    }
}

/* ─── Public Implementation ──────────────────────────────────── */

void WiFi_Init(void)
{
    /* TODO:
     * 1. HAL_Delay(1000) — wait for ESP8266 to boot
     * 2. WiFi_SendAT("AT\r\n")             — check alive
     * 3. WiFi_SendAT("AT+CWMODE=1\r\n")    — set station mode
     * 4. WiFi_SendAT("AT+CWJAP=\"" WIFI_SSID "\",\"" WIFI_PASSWORD "\"\r\n")
     * 5. WiFi_SendAT("AT+CIPSTART=...")    — open TCP server connection
     */
}

void WiFi_ProcessIncoming(void)
{
    /* TODO: Check UART1 RX buffer (DMA or interrupt-driven)
     *       Call WiFi_ParseCommand() for each received byte */
}
