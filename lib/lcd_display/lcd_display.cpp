// lib/lcd_display/lcd_display.cpp

#include "lcd_display.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Default I²C address and dimensions for a 16×2 LCD
static const uint8_t LCD_ADDRESS = 0x27;
static const uint8_t LCD_COLUMNS = 16;
static const uint8_t LCD_ROWS    = 2;

// Single global instance of the LCD
static LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void lcd_init() {
  Wire.begin();
  lcd.init();       // Initialize LCD
  lcd.backlight();  // Turn on backlight
  lcd.clear();
}

void lcd_clear() {
  lcd.clear();
}

void lcd_print(uint8_t row, uint8_t col, const char* text) {
  if (row >= LCD_ROWS || col >= LCD_COLUMNS || text == nullptr) {
    return;
  }
  lcd.setCursor(col, row);
  lcd.print(text);
}
