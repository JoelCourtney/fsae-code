#include "PWMTracker.h"

void PWMTracker::Pulse() {
      int hold = millis();
      rate = hold - lastPulse;
      lastPulse = hold;
}