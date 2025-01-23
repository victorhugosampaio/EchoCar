/**
 * @file car_handler.c
 * @author victorhugosampaio
 * @brief Car direction handler.
 * @version 0.1
 * @date 01-22-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "car_handler.h"
#include "driver/motor.h"

void move_car(const enum car_direction direction)
{
    switch (direction) {
    case STANDBY:
        motor_input_set(IN_1, 0);
        motor_input_set(IN_2, 0);
        motor_input_set(IN_3, 0);
        motor_input_set(IN_4, 0);
        break;
    case BREAK:
        motor_input_set(IN_1, 1);
        motor_input_set(IN_2, 1);
        motor_input_set(IN_3, 1);
        motor_input_set(IN_4, 1);
        break;
    case FORWARD:
        motor_input_set(IN_1, 1);
        motor_input_set(IN_2, 0);
        motor_input_set(IN_3, 1);
        motor_input_set(IN_4, 0);
        break;
    case BACKWARD:
        motor_input_set(IN_1, 0);
        motor_input_set(IN_2, 1);
        motor_input_set(IN_3, 0);
        motor_input_set(IN_4, 1);
        break;
    case LEFT:
        motor_input_set(IN_1, 0);
        motor_input_set(IN_2, 1);
        motor_input_set(IN_3, 1);
        motor_input_set(IN_4, 0);
        break;
    case RIGHT:
        motor_input_set(IN_1, 1);
        motor_input_set(IN_2, 0);
        motor_input_set(IN_3, 0);
        motor_input_set(IN_4, 1);
        break;
    }
}