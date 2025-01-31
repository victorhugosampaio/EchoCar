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
    DIRECTION_STANDBY,
    DIRECTION_BREAK,
    DIRECTION_FORWARD,
    DIRECTION_BACKWARD,
    DIRECTION_LEFT,
    DIRECTION_RIGHT,

    DIRECTION_QUANTITY,
};

/**
 * @brief Enumerate the model predictions.
 */
enum prediction {
    PREDICTION_BACKWARD,
    PREDICTION_FIVE,
    PREDICTION_FORWARD,
    PREDICTION_FOUR,
    PREDICTION_GO,
    PREDICTION_LEFT,
    PREDICTION_NOISE,
    PREDICTION_ONE,
    PREDICTION_RIGHT,
    PREDICTION_STOP,
    PREDICTION_THREE,
    PREDICTION_TWO,

    PREDICTION_QUANTITY,
};

#endif /* CAR_HANDLER_H */