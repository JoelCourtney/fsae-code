#include "LCD.h"
#include "Constants.h"
#include <Arduino.h>

LiquidCrystal LCD::lcd = LiquidCrystal(LCD_RS, LCD_RW, LCD_EN, LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
bool LCD::active = false;

void LCD::initialize() {
  lcd.begin(LCD_COLS, LCD_ROWS);
  delay(100);
  active = true; // no way to tell if failed
}

void LCD::write(String s) {
  lcd.setCursor(0,0);
  lcd.print(s);
  lcd.setCursor(2, 0);
}

bool LCD::isActive() {
  return true;
}
