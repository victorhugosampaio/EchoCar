/**
 * @file motor.c
 * @author victorhugosampaio
 * @brief L293D motor driver.
 * @version 0.1
 * @date 01-21-2025
 *
 * @note: Based on https://www.instructables.com/Tutorial-for-Dual-Channel-DC-Motor-Driver-Board-PW/
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "motor.h"

#include <errno.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(motor);

/**
 * @brief PWM frequency, in KHz.
 */
#define PWM_FREQUENCY 20

/**
 * @brief PWM period, in nanoseconds.
 */
#define PWM_PERIOD (1000000000 / PWM_KHZ(PWM_FREQUENCY))

/**
 * @brief Define the minimum and maximum PWM pulse for each input.
 */
#define IN_1_MIN_PULSE 0
#define IN_1_MAX_PULSE 50000

#define IN_2_MIN_PULSE 0
#define IN_2_MAX_PULSE 50000

#define IN_3_MIN_PULSE 0
#define IN_3_MAX_PULSE 50000

#define IN_4_MIN_PULSE 0
#define IN_4_MAX_PULSE 50000

/**
 * @brief Container that holds the motor device.
 */
static const struct device *motor = DEVICE_DT_GET(DT_NODELABEL(l293d));

int motor_init(void)
{
    if (motor == NULL) {
        LOG_ERR("motor pointer is NULL");
        return -EFAULT;
    }

    if (!device_is_ready(motor)) {
        LOG_ERR("motor is not ready");
        return -EBUSY;
    }

    return 0;
}

int motor_input_set(const enum motor_input input, const bool value)
{
    uint16_t pulse = 0;

    switch (input) {
    case IN_1:
        pulse = value ? IN_1_MAX_PULSE : IN_1_MIN_PULSE;
        break;
    case IN_2:
        pulse = value ? IN_2_MAX_PULSE : IN_2_MIN_PULSE;
        break;
    case IN_3:
        pulse = value ? IN_3_MAX_PULSE : IN_3_MIN_PULSE;
        break;
    case IN_4:
        pulse = value ? IN_4_MAX_PULSE : IN_4_MIN_PULSE;
        break;
    default:
        return -EINVAL;
    }

    if (pwm_set(motor, input + 1, PWM_PERIOD, pulse, 0) != 0) {
        LOG_ERR("pwm set failed on channel %d", input);
        return -EBUSY;
    }

    return 0;
}