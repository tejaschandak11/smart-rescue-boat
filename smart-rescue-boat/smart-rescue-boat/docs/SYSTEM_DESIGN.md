# System Design — Smart Rescue Boat

## 1. Problem Statement

During flood and natural disaster scenarios, deploying human rescuers in water is dangerous and slow. This project addresses this by providing an autonomous boat that can operate in hazardous flood conditions, detect victims, and relay their locations to rescuers.

---

## 2. System Block Diagram

```
Power Supply (7.4V LiPo)
        │
        ▼
  Voltage Regulator (5V)
        │
        ├──────────────────────────────────────────┐
        │                                          │
        ▼                                          ▼
STM32 Bluepill (MCU)                        L298N Motor Driver
  │   │   │   │                                │         │
  │   │   │   └── ADC PA4 ── Battery Monitor   │         │
  │   │   │                                  Left      Right
  │   │   ├── UART1 (PA9/PA10) ── ESP8266    Motor     Motor
  │   │   │                      (Wi-Fi)
  │   │   ├── UART2 (PA2/PA3)  ── HC-05
  │   │   │                      (Bluetooth)
  │   │   ├── GPIO PB0 ──────── HC-SR04 (Trig)
  │   │   ├── GPIO PB1 ──────── HC-SR04 (Echo)
  │   │   └── GPIO PB5 ──────── FC-51 IR Sensor
  │   │
  │   └── TIM2 PWM (PA0–PA3) ── L298N Enable Pins
  │
  └── PC13 ── Status LED (onboard)
```

---

## 3. Software Architecture

### 3.1 Module Overview

| Module | File(s) | Responsibility |
|---|---|---|
| **Main** | `main.c` | System init, mode state machine, main loop |
| **Navigation** | `navigation.c/h` | Motor control, path planning, obstacle response |
| **Detection** | `obstacle.c`, `victim_detect.c`, `detection.h` | Sensor reading, threat classification |
| **Communication** | `wifi_handler.c`, `bluetooth.c`, `communication.c/h` | Command reception, alert transmission |
| **Power** | `power_mgmt.h` | ADC battery monitoring, low-power events |

### 3.2 Operating Mode State Machine

```
         ┌──────────────┐
  Boot → │  AUTONOMOUS  │ ◄────────────────────────┐
         └──────┬───────┘                          │
                │                                  │
         Victim │                   'A' cmd        │
        detected│                  received        │
                ▼                                  │
         ┌──────────────┐   'M' cmd   ┌────────────┴─────┐
         │    SEARCH    │ ─────────► │     MANUAL        │
         └──────┬───────┘            └──────────────────┘
                │
         Alert  │
           ACK  │
                ▼
         ┌──────────────┐
         │  HOLD POSIT. │
         └──────────────┘

         Battery Critical → RETURN_TO_BASE (from any mode)
```

---

## 4. Communication Protocol

### 4.1 Command Bytes (single-char)

| Byte | Action |
|---|---|
| `F` | Move Forward |
| `B` | Move Backward |
| `L` | Turn Left |
| `R` | Turn Right |
| `S` | Stop |
| `A` | Switch to Autonomous mode |
| `M` | Switch to Manual mode |
| `K` | Acknowledge alert |

### 4.2 Alert Format (sent by boat)

```
ALERT:VICTIM_FOUND\r\n
ALERT:LOW_BATTERY\r\n
ALERT:OBSTACLE_BLOCKED\r\n
ALERT:SYSTEM_OK\r\n
```

---

## 5. Power Budget (Estimated)

| Component | Current Draw |
|---|---|
| STM32 Bluepill | ~30 mA |
| ESP8266 (active TX) | ~215 mA peak, ~80 mA avg |
| HC-05 Bluetooth | ~40 mA |
| L298N + 2× DC Motors | ~500 mA (loaded) |
| HC-SR04 | ~15 mA |
| FC-51 IR | ~20 mA |
| **Total (estimated)** | **~685 mA avg** |

With a **2200 mAh 2S LiPo**, expected run time ≈ **~45 minutes** active operation.

---

## 6. Design Decisions

**Why STM32 over Arduino?**
STM32 Bluepill offers more GPIO, faster clock (72 MHz vs 16 MHz), hardware timers for precise PWM, and is more representative of industry-grade embedded development.

**Why both Wi-Fi and Bluetooth?**
Wi-Fi gives range and network integration; Bluetooth provides low-latency, close-range manual override without needing network infrastructure — critical in disaster scenarios where network may be down.

**Why IR for victim detection?**
IR sensors are cost-effective, lightweight, and work in wet/dark conditions. A camera + ML approach is listed as a future improvement.
