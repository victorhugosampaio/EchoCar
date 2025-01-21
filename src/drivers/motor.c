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
 * @brief PWM frequency, in Hz.
 */
#define PWM_FREQUENCY 20000

/**
 * @brief PWM period, in microseconds.
 */
#define PWM_PERIOD (1000000 / PWM_FREQUENCY)

/**
 * @brief Set the PWM percentage for a channel.
 *
 * @param ch Channel.
 * @param percentage PWM percentage.
 */
static int set_ch_pwm(uint8_t ch, uint8_t percentage);

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

static int set_ch_pwm(uint8_t ch, uint8_t percentage)
{
    if (ch < 1 || ch > 4 || percentage < 0 || percentage > 100) {
        return -EINVAL;
    }

    if (pwm_set(motor, ch, PWM_USEC(PWM_PERIOD), PWM_USEC((PWM_PERIOD * percentage) / 100), 0) != 0) {
        LOG_ERR("set pwm failed");
        return -EBUSY;
    }

    return 0;
}