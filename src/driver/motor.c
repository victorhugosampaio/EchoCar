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
 * @brief Container that holds the PWM devices.
 */
static const struct pwm_dt_spec in_1 = PWM_DT_SPEC_GET_BY_NAME(DT_PATH(zephyr_user), in_1);
static const struct pwm_dt_spec in_2 = PWM_DT_SPEC_GET_BY_NAME(DT_PATH(zephyr_user), in_2);
static const struct pwm_dt_spec in_3 = PWM_DT_SPEC_GET_BY_NAME(DT_PATH(zephyr_user), in_3);
static const struct pwm_dt_spec in_4 = PWM_DT_SPEC_GET_BY_NAME(DT_PATH(zephyr_user), in_4);

int motor_init(void)
{
    if (!pwm_is_ready_dt(&in_1) || !pwm_is_ready_dt(&in_2) || !pwm_is_ready_dt(&in_3) || !pwm_is_ready_dt(&in_4)) {
        LOG_ERR("motor is not ready");
        return -EBUSY;
    }

    motor_input_set(IN_1, 0);
    motor_input_set(IN_2, 0);
    motor_input_set(IN_3, 0);
    motor_input_set(IN_4, 0);

    return 0;
}

void motor_input_set(const enum motor_input input, const bool value)
{
    uint32_t pulse = 0;

    switch (input) {
    case IN_1:
        pulse = value ? CONFIG_IN_1_MAX_PULSE : CONFIG_IN_1_MIN_PULSE;
        pwm_set_pulse_dt(&in_1, pulse);
        break;
    case IN_2:
        pulse = value ? CONFIG_IN_2_MAX_PULSE : CONFIG_IN_2_MIN_PULSE;
        pwm_set_pulse_dt(&in_2, pulse);
        break;
    case IN_3:
        pulse = value ? CONFIG_IN_3_MAX_PULSE : CONFIG_IN_3_MIN_PULSE;
        pwm_set_pulse_dt(&in_3, pulse);
        break;
    case IN_4:
        pulse = value ? CONFIG_IN_4_MAX_PULSE : CONFIG_IN_4_MIN_PULSE;
        pwm_set_pulse_dt(&in_4, pulse);
        break;
    }
}