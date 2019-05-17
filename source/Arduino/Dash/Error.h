#ifndef ERROR_H
#define ERROR_H

#include <Arduino.h>

class Error {
  static String warningMessage;
public:
  static void fatalError(String message);
  static void warning(String message);
  static void stopWarning();
  static void warn();
  static bool isWarning();
};

#endif
