#include "Timer.h"

Timer::Timer() {
      start = millis();
}

void Timer::Restart() {
      start = millis();
}

int Timer::GetDuration() {
      return millis() - start;
}