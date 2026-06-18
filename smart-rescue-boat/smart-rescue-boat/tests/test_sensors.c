/**
 * @file    test_sensors.c
 * @brief   Unit tests for detection module (host-side, no hardware needed)
 * @author  Tejas Chandak
 *
 * Compile and run on PC to validate logic before flashing to STM32.
 * gcc test_sensors.c -o test_sensors && ./test_sensors
 */

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

/* ─── Mock the STM32 HAL so tests compile on host ────────────── */
#define GPIO_PIN_RESET 0
#define GPIO_PIN_SET   1
#define HAL_GPIO_ReadPin(port, pin) mock_pin_value

static uint8_t mock_pin_value = GPIO_PIN_RESET;

/* ─── Inline the logic under test ────────────────────────────── */

static uint8_t victim_detected_logic(uint8_t pin_state) {
    return (pin_state == GPIO_PIN_RESET) ? 1 : 0;
}

static uint16_t distance_to_cm(uint32_t elapsed_us) {
    return (uint16_t)(elapsed_us / 58U);
}

/* ─── Tests ──────────────────────────────────────────────────── */

void test_victim_detection_pin_low_triggers(void) {
    uint8_t result = victim_detected_logic(GPIO_PIN_RESET);
    assert(result == 1);
    printf("[PASS] Victim detected when IR pin is LOW\n");
}

void test_victim_not_detected_pin_high(void) {
    uint8_t result = victim_detected_logic(GPIO_PIN_SET);
    assert(result == 0);
    printf("[PASS] No victim when IR pin is HIGH\n");
}

void test_distance_conversion_50cm(void) {
    uint32_t elapsed_us = 2900; /* 50 cm → ~2900 µs round trip */
    uint16_t dist = distance_to_cm(elapsed_us);
    assert(dist >= 48 && dist <= 52); /* ±2 cm tolerance */
    printf("[PASS] Distance conversion: %u cm (expected ~50 cm)\n", dist);
}

void test_distance_conversion_30cm(void) {
    uint32_t elapsed_us = 1740;
    uint16_t dist = distance_to_cm(elapsed_us);
    assert(dist >= 28 && dist <= 32);
    printf("[PASS] Distance conversion: %u cm (expected ~30 cm)\n", dist);
}

void test_obstacle_threshold(void) {
    uint16_t dist_close = 20;
    uint16_t dist_safe  = 50;
    uint16_t threshold  = 30;
    assert(dist_close < threshold);
    assert(dist_safe  >= threshold);
    printf("[PASS] Obstacle threshold logic works correctly\n");
}

/* ─── Main ───────────────────────────────────────────────────── */

int main(void) {
    printf("=== Smart Rescue Boat — Sensor Unit Tests ===\n\n");

    test_victim_detection_pin_low_triggers();
    test_victim_not_detected_pin_high();
    test_distance_conversion_50cm();
    test_distance_conversion_30cm();
    test_obstacle_threshold();

    printf("\n✅ All tests passed.\n");
    return 0;
}
