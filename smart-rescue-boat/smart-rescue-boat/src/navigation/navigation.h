/**
 * @file    navigation.h
 * @brief   Autonomous navigation interface
 * @author  Tejas Chandak
 */

#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <stdint.h>

/* ─── Constants ─────────────────────────────────────────────── */
#define MOTOR_SPEED_FULL     255
#define MOTOR_SPEED_SLOW     120
#define MOTOR_SPEED_STOP     0
#define OBSTACLE_THRESHOLD_CM 30   /* Obstacle avoidance trigger distance */

/* ─── Drive Commands (used in manual mode) ──────────────────── */
typedef enum {
    CMD_FORWARD = 0,
    CMD_BACKWARD,
    CMD_TURN_LEFT,
    CMD_TURN_RIGHT,
    CMD_STOP
} DriveCommand_t;

/* ─── Public API ─────────────────────────────────────────────── */
void Navigation_Init(void);
void Navigation_MoveForward(void);
void Navigation_MoveBackward(void);
void Navigation_TurnLeft(void);
void Navigation_TurnRight(void);
void Navigation_Stop(void);
void Navigation_SlowPatrol(void);
void Navigation_HoldPosition(void);
void Navigation_ReturnToBase(void);
void Navigation_AvoidObstacle(uint16_t distance_cm);
void Navigation_ExecuteCommand(DriveCommand_t cmd);

#endif /* NAVIGATION_H */
