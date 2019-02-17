#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

struct Timer {
      unsigned long start = millis();
      bool running = false;
      
      Timer();
      
      void Toggle();
      int GetDuration();
};

#endif
