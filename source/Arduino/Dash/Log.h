#ifndef LOG_H
#define LOG_H

#include <Arduino.h>

class Log {
  static String fileName;

  static bool active;
  
public:
  static void initialize();

  static void write(String data);

  static bool isActive();
};

#endif
