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

#include "driver/display.h"
#include "driver/motor.h"
#include "driver/usart.h"

int main(void)
{
    display_init();
    motor_init();
    usart_init();

    return 0;
}