/**
 * @file car_handler.h
 * @author victorhugosampaio
 * @brief Car direction handler.
 * @version 0.1
 * @date 01-22-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef CAR_HANDLER_H
#define CAR_HANDLER_H

/**
 * @brief Enumerate the car directions.
 */
enum car_direction {
    STANDBY,
    BREAK,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
};

/**
 * @brief Move the car in the desired direction.
 *
 * @param direction Desired direction.
 */
void move_car(const enum car_direction direction);

#endif /* CAR_HANDLER_H */