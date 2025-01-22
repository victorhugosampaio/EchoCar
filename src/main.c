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
    add_string("This is a Test.");

    add_string("Moving car...");
    display_print();

    k_msleep(2000);

    for (enum car_direction dir = STANDBY; dir <= RIGHT; dir++) {
        add_string("Direction:\n");
        add_string((char)dir);
        display_print();

        move_car(dir);
        k_msleep(2000);
    }

    return 0;
}