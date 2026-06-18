/**
 * @file    navigation.c
 * @brief   Motor control and autonomous navigation logic
 * @author  Tejas Chandak
 *
 * Controls two DC motors via L298N motor driver.
 * Handles autonomous path planning and obstacle avoidance.
 */

#include "navigation.h"
#include "stm32f1xx_hal.h"

/* ─── Private Motor Control Helpers ─────────────────────────── */

/**
 * @brief Set speed and direction for left and right motors
 * @param left_speed   PWM duty cycle for left motor  (0–255)
 * @param right_speed  PWM duty cycle for right motor (0–255)
 * @param direction    0 = forward, 1 = reverse
 */
static void Motor_Set(uint8_t left_speed, uint8_t right_speed, uint8_t direction)
{
    /* TODO: Write PWM values to TIM2 channels (PA0, PA1 = left; PA2, PA3 = right)
     *       Set direction pins on L298N IN1/IN2/IN3/IN4 accordingly */
    (void)left_speed;
    (void)right_speed;
    (void)direction;
}

/* ─── Public API Implementation ──────────────────────────────── */

void Navigation_Init(void)
{
    /* TODO: Initialize TIM2 in PWM mode for motor speed control
     *       Set all motor pins as GPIO_MODE_AF_PP
     *       Start all PWM channels with HAL_TIM_PWM_Start() */
    Navigation_Stop();
}

void Navigation_MoveForward(void)
{
    Motor_Set(MOTOR_SPEED_FULL, MOTOR_SPEED_FULL, 0);
}

void Navigation_MoveBackward(void)
{
    Motor_Set(MOTOR_SPEED_FULL, MOTOR_SPEED_FULL, 1);
}

void Navigation_TurnLeft(void)
{
    /* Reduce left motor speed to pivot left */
    Motor_Set(MOTOR_SPEED_SLOW / 2, MOTOR_SPEED_SLOW, 0);
    HAL_Delay(300);
    Navigation_Stop();
}

void Navigation_TurnRight(void)
{
    /* Reduce right motor speed to pivot right */
    Motor_Set(MOTOR_SPEED_SLOW, MOTOR_SPEED_SLOW / 2, 0);
    HAL_Delay(300);
    Navigation_Stop();
}

void Navigation_Stop(void)
{
    Motor_Set(MOTOR_SPEED_STOP, MOTOR_SPEED_STOP, 0);
}

void Navigation_SlowPatrol(void)
{
    /* Slow circular movement around last known victim position */
    Motor_Set(MOTOR_SPEED_SLOW, MOTOR_SPEED_SLOW / 2, 0);
}

void Navigation_HoldPosition(void)
{
    Navigation_Stop();
    /* TODO: If GPS is available, implement station-keeping */
}

void Navigation_ReturnToBase(void)
{
    /* TODO: Implement GPS-guided return-to-home
     *       For now: reverse direction for fixed duration */
    Navigation_MoveBackward();
    HAL_Delay(5000);
    Navigation_Stop();
}

/**
 * @brief Obstacle avoidance — back up and turn away
 * @param distance_cm  Measured obstacle distance from ultrasonic sensor
 */
void Navigation_AvoidObstacle(uint16_t distance_cm)
{
    Navigation_Stop();
    HAL_Delay(200);
    Navigation_MoveBackward();
    HAL_Delay(400);

    /* Turn direction based on last heading — simple 90-degree turn */
    Navigation_TurnRight();
}

void Navigation_ExecuteCommand(DriveCommand_t cmd)
{
    switch (cmd) {
        case CMD_FORWARD:    Navigation_MoveForward();  break;
        case CMD_BACKWARD:   Navigation_MoveBackward(); break;
        case CMD_TURN_LEFT:  Navigation_TurnLeft();     break;
        case CMD_TURN_RIGHT: Navigation_TurnRight();    break;
        case CMD_STOP:       Navigation_Stop();         break;
        default:             Navigation_Stop();         break;
    }
}
