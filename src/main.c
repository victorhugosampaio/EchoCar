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

#include "drivers/display.h"
#include "drivers/motor.h"

int main(void)
{
    display_init();
    motor_init();

    add_string("Hello World!\n");
    add_string("This is a Test.");
    display_print();

    return 0;
}