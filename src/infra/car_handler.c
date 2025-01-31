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

/**
 * @brief LUT with the directions strings.
 */
static const char *directions[DIRECTION_QUANTITY] = {
    [DIRECTION_STANDBY] = "STANDBY",
    [DIRECTION_BREAK] = "BREAK",
    [DIRECTION_FORWARD] = "FORWARD",
    [DIRECTION_BACKWARD] = "BACKWARD",
    [DIRECTION_LEFT] = "LEFT",
    [DIRECTION_RIGHT] = "RIGHT",
};

/**
 * @brief LUT with the directions inputs.
 */
static const uint8_t dir_table[DIRECTION_QUANTITY][IN_QUANTITY] = {
    [DIRECTION_STANDBY] = {0, 0, 0, 0},
    [DIRECTION_BREAK] = {1, 1, 1, 1},
    [DIRECTION_FORWARD] = {1, 0, 1, 0},
    [DIRECTION_BACKWARD] = {0, 1, 0, 1},
    [DIRECTION_LEFT] = {0, 1, 1, 0},
    [DIRECTION_RIGHT] = {1, 0, 0, 1},
};

_Noreturn static void car_handler_thread()
{
    enum car_direction current_direction = DIRECTION_STANDBY;
    enum car_direction last_direction = current_direction;

    while (true) {
        current_direction = get_char()[0] - '0';

        switch (current_direction) {
        case DIRECTION_STANDBY:
        case DIRECTION_BREAK:
        case DIRECTION_FORWARD:
        case DIRECTION_BACKWARD:
        case DIRECTION_LEFT:
        case DIRECTION_RIGHT:
            move_car(current_direction);
            last_direction = current_direction;
            display_add_string("Moving:\n");
            display_add_string(directions[current_direction]);
            break;

        default:
            if (last_direction == DIRECTION_STANDBY) {
                continue;
            }

            last_direction = DIRECTION_STANDBY;
            move_car(DIRECTION_STANDBY);
            display_add_string("Waiting...");
            break;
        }

        display_print();
    }
}

static void move_car(const enum car_direction direction)
{
    motor_input_set(IN_1, dir_table[direction][0]);
    motor_input_set(IN_2, dir_table[direction][1]);
    motor_input_set(IN_3, dir_table[direction][2]);
    motor_input_set(IN_4, dir_table[direction][3]);
}