#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "Timer.h"

class Failsafe {
  static bool active;

  static Timer appsDiff;
  static Timer tpsDiff;
  static Timer brakeThrottleConflict;
  static Timer tpsExpected;

  static bool safe;

  static bool check(Timer t);
  
public:
  static void initialize();
  static void update();
  static void setDogEnable(bool enable);
  static void feedDog();
  static bool isActive();
  
  static void cutThrottle();
  static void setFuel(bool b);
  static void setIgnition(bool b);

  static bool isSafe();
};

#endif
