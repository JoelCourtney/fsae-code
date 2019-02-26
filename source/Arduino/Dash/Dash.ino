#include "Constants.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(LCD_COLS,LCD_ROWS);
  lcd.print("VROOM VROOM");
  lcd.setCursor(0,1);
  lcd.print("baby ;)");
}

void loop() {
  // put your main code here, to run repeatedly:
}
