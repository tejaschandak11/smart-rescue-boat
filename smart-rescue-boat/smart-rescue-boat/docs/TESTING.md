# Testing & Validation — Smart Rescue Boat

## Test Environment

All field tests conducted in a controlled shallow-water tank (1.5m × 3m) simulating flood conditions, and in an open outdoor pool for range testing.

---

## Test Results Summary

| Test | Metric | Result | Status |
|---|---|---|---|
| Ultrasonic range | Detection at 200 cm | ✅ Detected | PASS |
| Ultrasonic accuracy | Error at 50 cm | ±2 cm | PASS |
| IR victim detection | Detection at 30 cm | ~92% accuracy | PASS |
| IR false positives | Water surface reflection | 8% rate | ACCEPTABLE |
| Wi-Fi range | Reliable command receive | 30 m open water | PASS |
| BT override latency | Command to motor response | < 100 ms | PASS |
| Obstacle avoidance | 10 consecutive obstacles | 10/10 avoided | PASS |
| Autonomous runtime | On full 2200 mAh charge | ~45 minutes | PASS |
| Mode switching | AUTO ↔ MANUAL transitions | Instant | PASS |
| Low battery alert | Trigger at 7.0V | Triggered correctly | PASS |

---

## Detailed Test Cases

### TC-01: Obstacle Avoidance in Narrow Channel

**Setup:** Two foam boards placed 60 cm apart forming a channel.
**Procedure:** Boat entered autonomously. Obstacle placed mid-channel.
**Expected:** Boat detects, reverses, turns, navigates around.
**Result:** ✅ Passed 9/10 runs. 1 failure due to motor stall (hardware, not firmware).

---

### TC-02: Victim Detection Rate

**Setup:** A foam mannequin (30×20 cm) placed at varying distances.
**Procedure:** Boat approaches autonomously, IR sensor reading logged.
**Expected:** Trigger `MODE_SEARCH` within 30 cm.

| Distance (cm) | Detections / 10 trials | Result |
|---|---|---|
| 10 | 10/10 | ✅ |
| 20 | 10/10 | ✅ |
| 30 | 9/10 | ✅ |
| 40 | 3/10 | ❌ (outside IR range) |

**Conclusion:** Reliable within 30 cm. Future IR with longer range or camera recommended.

---

### TC-03: Wi-Fi Remote Control Latency

**Setup:** Phone connected to ESP8266 via TCP socket app.
**Procedure:** Send F/B/L/R commands, measure time to motor response with oscilloscope.
**Result:** Average 85 ms latency (UART + ESP processing). Max observed: 130 ms.

---

### TC-04: Battery Monitoring Accuracy

**Setup:** Bench power supply set to known voltages, ADC reading compared.
**Calibration:** Voltage divider ratio verified with multimeter.

| PSU Voltage | ADC Reading | Error |
|---|---|---|
| 8.4V | 8.38V | 0.2% |
| 7.4V | 7.42V | 0.3% |
| 6.6V | 6.63V | 0.5% |

---

## Known Issues / Limitations

1. **IR false positives on water surface** — Water reflectivity occasionally triggers victim detection. Debounce (N consecutive reads) mitigates this.
2. **Wi-Fi reconnection** — If ESP8266 loses AP connection, firmware does not auto-reconnect. Needs watchdog + reconnect logic.
3. **No GPS** — Return-to-base is time-based reverse, not coordinate-guided. GPS integration is planned.
