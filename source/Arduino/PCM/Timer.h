#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

struct Timer {
      unsigned long start = millis();
      bool running = false;
      String name;
      
      Timer();
      
      void toggle();
      int getDuration();
};

#endif
