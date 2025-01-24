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
#include "driver/display.h"
#include "driver/motor.h"
#include "driver/usart.h"

#include <stdio.h>
#include <zephyr/kernel.h>

/**
 * @brief Car handler thread.
 */
_Noreturn static void car_handler_thread();

/**
 * @brief Move the car in the desired direction.
 *
 * @param direction Desired direction.
 */
static void move_car(enum car_direction direction);

/**
 * @brief Create the car handler thread.
 */
K_THREAD_DEFINE(car_handler_thread_id, CONFIG_CAR_HANDLER_THREAD_STACK_SIZE, car_handler_thread,
                NULL, NULL, NULL, CONFIG_CAR_HANDLER_THREAD_PRIORITY, K_ESSENTIAL, 0);

static const char *directions[] = {
    [WAITING] = "WAITING",
    [STANDBY] = "STANDBY",
    [BREAK] = "BREAK",
    [FORWARD] = "FORWARD",
    [BACKWARD] = "BACKWARD",
    [LEFT] = "LEFT",
    [RIGHT] = "RIGHT",
};

_Noreturn static void car_handler_thread()
{
    enum car_direction last_direction = STANDBY;
    uint8_t current_direction = STANDBY;

    while (true) {
        current_direction = get_char()[0] - '0';

        switch (current_direction) {
            case STANDBY:
            case BREAK:
            case FORWARD:
            case BACKWARD:
            case LEFT:
            case RIGHT:
                move_car(current_direction);
                last_direction = current_direction;
                display_add_string("Moving:\n");
                display_add_string(directions[current_direction]);
                break;

            default:
                if (last_direction == STANDBY) {
                    continue;
                }

                last_direction = STANDBY;
                move_car(STANDBY);
                display_add_string("Waiting...");
                break;
        }

        display_print();
    }
}

static void move_car(const enum car_direction direction)
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
    default:
        break;
    }
}