/**
 * @file main.c
 * @author victorhugosampaio
 * @brief System main.
 * @version 0.1
 * @date 01-02-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <zephyr/kernel.h>

#include "driver/display.h"
#include "driver/motor.h"
#include "infra/car_handler.h"

int main(void)
{
    display_init();
    motor_init();

    add_string("Hello World!\n");
    add_string("This is a Test.\n");
    add_string("Moving car...");
    display_print();

    k_msleep(2000);

    add_string("Direction:\n");
    add_string("STANDBY");
    display_print();
    move_car(STANDBY);
    k_msleep(3000);

    add_string("Direction:\n");
    add_string("FORWARD");
    display_print();
    move_car(FORWARD);
    k_msleep(3000);

    add_string("Direction:\n");
    add_string("BACKWARD");
    display_print();
    move_car(BACKWARD);
    k_msleep(3000);

    add_string("Direction:\n");
    add_string("LEFT");
    display_print();
    move_car(LEFT);
    k_msleep(3000);

    add_string("Direction:\n");
    add_string("RIGHT");
    display_print();
    move_car(RIGHT);
    k_msleep(3000);

    add_string("Direction:\n");
    add_string("BREAK");
    display_print();
    move_car(BREAK);

    return 0;
}