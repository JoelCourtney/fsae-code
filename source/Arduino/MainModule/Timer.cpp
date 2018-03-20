#pragma once

#include "Timer.h"
#include <Arduino.h>

Timer::Timer() {
      running = false;
}

void Timer::Toggle() {
      running = !running;
      if (running) {
            start = millis();
      }
}

int Timer::GetDuration() {
      return millis() - start;
}
