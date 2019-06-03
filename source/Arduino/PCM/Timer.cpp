#include "Timer.h"
#include <Arduino.h>

Timer::Timer() {
      running = false;
      name = "";
}

void Timer::toggle() {
      running = !running;
      if (running) {
            start = millis();
      }
}

int Timer::getDuration() {
      return millis() - start;
}
