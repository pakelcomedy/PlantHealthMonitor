// lib/lcd_display/lcd_display.h

#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Arduino.h>

/**
 * @brief Initialize the I²C LCD display (default address 0x27) and backlight.
 * 
 * Must be called once in setup().
 */
void lcd_init();

/**
 * @brief Clear the entire LCD screen.
 */
void lcd_clear();

/**
 * @brief Print a null‑terminated C‑string at specified row and column.
 * 
 * @param row  Zero‑based row (0 or 1 for 16×2 LCD).
 * @param col  Zero‑based column (0–15 for 16×2 LCD).
 * @param text Null‑terminated C‑string to display.
 */
void lcd_print(uint8_t row, uint8_t col, const char* text);

#endif // LCD_DISPLAY_H
