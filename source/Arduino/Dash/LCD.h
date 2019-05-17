#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal.h>

class LCD {
  static LiquidCrystal lcd;

  static bool active;
  
public:
  static void initialize();
  static void write(String s);

  static bool isActive();
};

#endif
