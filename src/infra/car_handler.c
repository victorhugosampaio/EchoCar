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

#include <stdlib.h>
#include <zephyr/kernel.h>

/**
 * @brief Car handler thread.
 */
_Noreturn static void car_handler_thread();

/**
 * @brief Car moving timer callback.
 */
static void car_moving_timer_cb();

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
 * @brief Create the car moving timer.
 */
K_TIMER_DEFINE(car_moving_timer, car_moving_timer_cb, NULL);

/**
 * @brief LUT with the directions strings.
 */
static const char *directions[DIRECTION_QUANTITY] = {
    [DIRECTION_STANDBY] = "Standby\n",
    [DIRECTION_BREAK] = "Break\n",
    [DIRECTION_FORWARD] = "Forward\n",
    [DIRECTION_BACKWARD] = "Backward\n",
    [DIRECTION_LEFT] = "Left\n",
    [DIRECTION_RIGHT] = "Right\n",
};

/**
 * @brief LUT with the delay strings.
 */
static const char *delays[DELAY_QUANTITY] = {
    [DELAY_ONE] = "1",
    [DELAY_TWO] = "2",
    [DELAY_THREE] = "3",
    [DELAY_FOUR] = "4",
    [DELAY_FIVE] = "5",
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

static struct car_handler
{
    enum car_direction direction;
    uint8_t counter;
    bool available;
    bool moving;
} self = {
    .direction = DIRECTION_STANDBY,
    .counter = 0,
    .available = false,
    .moving = false,
};

_Noreturn static void car_handler_thread()
{
    uint8_t prediction;

    k_timer_start(&car_moving_timer, K_NO_WAIT, K_SECONDS(1));

    while (true) {
        prediction = usart_get_char()[0] - 'a';

        if (self.available) {
            if (self.direction == DIRECTION_STANDBY) {
                switch (prediction) {
                case PREDICTION_BACKWARD:
                    self.direction = DIRECTION_BACKWARD;
                    break;
                case PREDICTION_FORWARD:
                    self.direction = DIRECTION_FORWARD;
                    break;
                case PREDICTION_LEFT:
                    self.direction = DIRECTION_LEFT;
                    break;
                case PREDICTION_RIGHT:
                    self.direction = DIRECTION_RIGHT;
                    break;
                default:
                    display_add_string("Waiting\nDirection");
                    break;
                }
            } else if (self.counter == 0) {
                switch (prediction) {
                case PREDICTION_ONE:
                    self.counter = 1;
                    break;
                case PREDICTION_TWO:
                    self.counter = 2;
                    break;
                case PREDICTION_THREE:
                    self.counter = 3;
                    break;
                case PREDICTION_FOUR:
                    self.counter = 4;
                    break;
                case PREDICTION_FIVE:
                    self.counter = 5;
                    break;
                default:
                    display_add_string("Direction:\n");
                    display_add_string(directions[self.direction]);
                    display_add_string("\n");
                    display_add_string("Waiting delay");
                    break;
                }
            } else {
                self.available = false;
                self.moving = true;

                display_add_string("Starting!\n");
                display_add_string("\n");
                display_add_string("Direction:\n");
                display_add_string(directions[self.direction]);
                display_add_string("\n");
                display_add_string(delays[self.counter - 1]);
            }

            display_print();
        } else {
            if (prediction == PREDICTION_STOP) {
                self.moving = false;
            }

            if (prediction == PREDICTION_GO) {
                self.moving = true;
            }
        }
    }
}

static void car_moving_timer_cb()
{
    if (self.available == false) {
        if (self.counter == 0) {
            self.moving = false;
            self.direction = DIRECTION_STANDBY;
            move_car(self.direction);
            self.available = true;

        } else if (self.moving) {
            display_add_string("Moving:\n");
            display_add_string(directions[self.direction]);
            display_add_string("\n");
            display_add_string("Remaining:\n");
            display_add_string(delays[self.counter - 1]);

            self.counter--;
            move_car(self.direction);
        } else {
            display_add_string("STOPPED!\n");
            move_car(DIRECTION_BREAK);
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