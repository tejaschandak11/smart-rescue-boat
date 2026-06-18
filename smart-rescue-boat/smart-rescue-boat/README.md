# 🚤 Smart Rescue Boat — Autonomous IoT System

![Platform](https://img.shields.io/badge/Platform-STM32%20Bluepill-blue)
![Language](https://img.shields.io/badge/Language-Embedded%20C-green)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)
![Year](https://img.shields.io/badge/Year-2025-orange)

> **Final Year Project** — An autonomous rescue boat designed for disaster response scenarios, capable of real-time navigation, victim detection, and obstacle avoidance during flood rescue simulations.

---

## 📌 Overview

The Smart Rescue Boat is an autonomous IoT-based system built to assist in flood and disaster rescue operations. It navigates without human intervention, detects obstacles in its path, identifies potential victims, and can be overridden remotely via Wi-Fi or Bluetooth for manual control.

Traditional rescue operations in flooded environments put rescue workers at risk. This system aims to reduce that risk by deploying an autonomous boat that can reach victims faster and more safely.

---

## ✨ Features

- 🤖 **Autonomous Navigation** — Real-time controller-based path planning
- 📡 **Wireless Communication** — Wi-Fi and Bluetooth for remote monitoring and control
- 🔄 **Manual Override** — Switch between autonomous and manual mode on the fly
- 👁️ **Victim Detection** — Sensor-based detection of humans in water
- 🚧 **Obstacle Avoidance** — Real-time obstacle detection and path correction
- ⚡ **Low Power Design** — Optimized firmware for extended battery operation

---

## 🏗️ System Architecture

```
┌─────────────────────────────────────────────────────────┐
│                   STM32 Bluepill (MCU)                   │
│                                                         │
│  ┌──────────────┐    ┌──────────────┐    ┌───────────┐  │
│  │  Navigation  │    │  Detection   │    │  Comms    │  │
│  │   Module     │    │   Module     │    │  Module   │  │
│  └──────┬───────┘    └──────┬───────┘    └─────┬─────┘  │
└─────────┼────────────────────┼─────────────────┼────────┘
          │                    │                 │
    ┌─────▼──────┐    ┌────────▼───────┐  ┌──────▼──────┐
    │  Motors &  │    │ Ultrasonic +   │  │  Wi-Fi /    │
    │  Servos    │    │ IR Sensors     │  │  Bluetooth  │
    └────────────┘    └────────────────┘  └─────────────┘
```

---

## 🛠️ Hardware Components

| Component | Model | Purpose |
|---|---|---|
| Microcontroller | STM32F103C8T6 (Bluepill) | Main processing unit |
| Motor Driver | L298N | DC motor control |
| Ultrasonic Sensor | HC-SR04 | Obstacle detection |
| IR Sensor | FC-51 | Victim/object detection |
| Wi-Fi Module | ESP8266 (ESP-01) | Wireless communication |
| Bluetooth Module | HC-05 | Short-range manual control |
| DC Motors | BO Motor 150 RPM | Boat propulsion |
| Power Supply | 7.4V 2S LiPo | Main power source |
| Voltage Regulator | LM7805 | 5V regulated supply |

---

## 📁 Repository Structure

```
smart-rescue-boat/
│
├── src/                        # All source code
│   ├── main.c                  # Entry point, system init
│   ├── navigation/
│   │   ├── navigation.c        # Autonomous path planning
│   │   └── navigation.h
│   ├── detection/
│   │   ├── obstacle.c          # Obstacle avoidance logic
│   │   ├── victim_detect.c     # Victim detection logic
│   │   └── detection.h
│   ├── communication/
│   │   ├── wifi_handler.c      # ESP8266 Wi-Fi interface
│   │   ├── bluetooth.c         # HC-05 Bluetooth interface
│   │   └── communication.h
│   └── power/
│       ├── power_mgmt.c        # Battery monitoring
│       └── power_mgmt.h
│
├── hardware/
│   ├── schematics/             # Circuit diagrams
│   │   └── main_schematic.md
│   └── bom/
│       └── bill_of_materials.md
│
├── docs/
│   ├── SYSTEM_DESIGN.md        # Detailed system design
│   └── TESTING.md              # Test results and validation
│
├── tests/
│   └── test_sensors.c          # Sensor unit tests
│
├── .gitignore
└── README.md
```

---

## 🚀 Getting Started

### Prerequisites

- STM32CubeIDE (v1.13+)
- STM32CubeProgrammer (for flashing)
- ST-Link V2 debugger/programmer
- All hardware components listed above

### Setup & Flash

```bash
# 1. Clone the repository
git clone https://github.com/tejaschandak11/smart-rescue-boat.git
cd smart-rescue-boat

# 2. Open in STM32CubeIDE
#    File → Open Projects from File System → select this folder

# 3. Build the project
#    Project → Build All  (Ctrl+B)

# 4. Connect ST-Link to STM32 Bluepill
#    SWDIO → A13, SWCLK → A14, GND → GND, 3.3V → 3.3V

# 5. Flash the firmware
#    Run → Debug (F11) or use STM32CubeProgrammer
```

### Wi-Fi Configuration

Edit `src/communication/wifi_handler.c` and update your credentials:

```c
#define WIFI_SSID     "your_network_name"
#define WIFI_PASSWORD "your_password"
#define SERVER_PORT   8080
```

---

## 📊 Operating Modes

| Mode | Trigger | Behaviour |
|---|---|---|
| `AUTONOMOUS` | Default on boot | Self-navigates, avoids obstacles |
| `MANUAL` | Bluetooth/Wi-Fi command | User controls direction |
| `SEARCH` | Victim detected | Slows down, circles area |
| `RETURN` | Low battery | Returns to base station |

---

## 🧪 Test Results

Field testing conducted in simulated flood environments:

- ✅ Obstacle detection range: **20–200 cm** (HC-SR04)
- ✅ Victim detection accuracy: **~92%** in test scenarios
- ✅ Wi-Fi range: **~30 m** open water
- ✅ Bluetooth override latency: **< 100 ms**
- ✅ Autonomous run time: **~45 minutes** on full charge

---

## 📸 Project Images

> *Hardware photos and demo videos will be added here.*

---

## 🔮 Future Improvements

- [ ] Add GPS module for geo-tagged victim location reporting
- [ ] Integrate camera module for visual victim detection
- [ ] Implement ML-based water current prediction
- [ ] Build a mobile app for monitoring dashboard
- [ ] Add LoRa module for long-range communication

---

## 👨‍💻 Author

**Tejas Chandak**
- 📧 tejaschandak3511@gmail.com
- 💼 [LinkedIn](https://linkedin.com/in/tejaschandak-727b46257)
- 🎓 B.Tech E&TC — K.K.W.I.E.E.R, Nashik (2022–2026)

---

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).

---

*Built with ❤️ for disaster response and human safety.*
