# Circuit Schematic Notes — Smart Rescue Boat

> Full KiCad schematic file to be added. Pin connections documented here.

---

## STM32 Bluepill Pin Map

| STM32 Pin | Connected To | Function |
|---|---|---|
| PA0 | L298N ENA | Left motor PWM speed |
| PA1 | L298N IN1 | Left motor direction |
| PA2 | L298N IN2 | Left motor direction |
| PA3 | L298N ENB | Right motor PWM speed |
| PA4 | L298N IN3 | Right motor direction |
| PA5 | L298N IN4 | Right motor direction |
| PA9 (UART1 TX) | ESP8266 RX | Wi-Fi AT commands |
| PA10 (UART1 RX) | ESP8266 TX | Wi-Fi data in |
| PA2 (UART2 TX) | HC-05 RX | Bluetooth TX |
| PA3 (UART2 RX) | HC-05 TX | Bluetooth RX |
| PB0 | HC-SR04 TRIG | Ultrasonic trigger |
| PB1 | HC-SR04 ECHO | Ultrasonic echo |
| PB5 | FC-51 OUT | IR victim detection |
| PA6 (ADC) | Voltage divider | Battery voltage sense |
| PC13 | LED (onboard) | Status indicator |
| 3.3V | ESP8266 VCC | ESP8266 power |
| 5V | HC-05 VCC | Bluetooth power |
| 5V | HC-SR04 VCC | Ultrasonic power |
| GND | All GND | Common ground |

---

## Voltage Divider (Battery Monitor)

```
Battery (+) ──── 10kΩ ──── PA6 (ADC) ──── 10kΩ ──── GND
```

- Input range: 0–16.8V (safe for 2S LiPo)
- Output range: 0–3.3V (within STM32 ADC limits)
- Divider ratio: ÷2 → multiply ADC result by 2

---

## Power Rail

```
LiPo 7.4V → LM7805 → 5V rail → L298N logic, HC-05, HC-SR04, FC-51
                   → 3.3V LDO (onboard Bluepill) → STM32, ESP8266
LiPo 7.4V → L298N motor power input (directly)
```
