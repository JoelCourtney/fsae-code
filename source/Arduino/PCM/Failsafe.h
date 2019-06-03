#ifndef WATCHDOG_H
#define WATCHDOG_H

class Failsafe {
  static bool active;
public:
  static void initialize();
  static void 
  static void setDogEnable(bool enable);
  static void feedDog();
  static bool isActive();
};

#endif
