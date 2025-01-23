/**
 * @file motor.h
 * @author victorhugosampaio
 * @brief L293D display driver.
 * @version 0.1
 * @date 01-21-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <stdbool.h>

/**
 * @brief Enumerate the inputs.
 */
enum motor_input {
    IN_1,
    IN_2,
    IN_3,
    IN_4,
};

/**
 * @brief Initialize the motor driver.
 *
 * @return 0 on success, a negative integer on failure.
 */
int motor_init(void);

/**
 * @brief Set a motor input value
 *
 * @param input Motor input.
 * @param value Input value (true for 1 and false for 0).
 */
void motor_input_set(const enum motor_input input, const bool value);

#endif /* MOTOR_H */