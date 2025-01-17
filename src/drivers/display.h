/**
* @file display.h
 * @author victorhugosampaio
 * @brief SSD1306 display driver.
 * @version 0.1
 * @date 01-15-2025
 *
 * @copyright Copyright (c) 2025
 *
 */


#ifndef DISPLAY_H
#define DISPLAY_H

/**
 * @brief Initialize display driver.
 */
int display_init(void);

/**
 * @brief Add a string to the display buffer.
 */
void add_string(char *str);

/**
 * @brief Print the display buffer.
 */
int display_print(void);

#endif /* DISPLAY_H */