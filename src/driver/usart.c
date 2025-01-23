/**
 * @file usart.c
 * @author victorhugosampaio
 * @brief Usart driver.
 * @version 0.1
 * @date 01-23-2025
 *
 * @note: USART 1 - TX: A9 RX: A10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "usart.h"

#include <errno.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(usart1);

/**
 * @brief Container that holds the uart device.
 */
static const struct device *usart1 = DEVICE_DT_GET(DT_NODELABEL(usart1));

/**
 * @brief Usart thread.
 */
_Noreturn static void usart_thread();

/**
 * @brief Create the usart thread.
 */
K_THREAD_DEFINE(usart_thread_id, CONFIG_USART_THREAD_STACK_SIZE, usart_thread,
                NULL, NULL, NULL, CONFIG_USART_THREAD_PRIORITY, K_ESSENTIAL, 0);

/**
 * @brief Holds the received char.
 */
static unsigned char received = '0';

int usart_init(void)
{
    if (usart1 == NULL) {
        LOG_ERR("uart pointer is NULL");
        return -EFAULT;
    }

    if (!device_is_ready(usart1)) {
        LOG_ERR("uart is not ready");
        return -EBUSY;
    }

    return 0;
}

char get_char(void)
{
    return received;
}

_Noreturn static void usart_thread()
{
    while (true) {
        if (uart_poll_in(usart1, &received) < 0) {
            LOG_ERR("uart poll failed");
            k_msleep(500);
        }

        k_msleep(5);
    }
}