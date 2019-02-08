#ifndef TIMER_H
#define TIMER_H

struct Timer {
      unsigned long start;
      bool running;
      
      Timer();
      
      void Toggle();
      int GetDuration();
};

#endif
