/**
 * @file usart.h
 * @author victorhugosampaio
 * @brief Usart driver.
 * @version 0.1
 * @date 01-23-2025
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef USART_H
#define USART_H

/**
 * @brief Initialize the usart driver.
 *
 * @return 0 on success, a negative integer on failure.
 */
int usart_init(void);

/**
 * @brief Returns the received char from usart.
 *
 * @return Received char.
 */
unsigned char *usart_get_char(void);

#endif /* USART_H */