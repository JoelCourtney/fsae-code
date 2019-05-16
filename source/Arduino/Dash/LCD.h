#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal.h>

class LCD {
  static LiquidCrystal lcd;
  
public:
  static void Initialize();
  static void Write(String s);
};

#endif
