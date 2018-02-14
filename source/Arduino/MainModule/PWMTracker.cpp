#include "PWMTracker.h"

void PWMTracker::Pulse() {
      int hold = millis();
      period = hold - lastPulse;
      lastPulse = hold;
}
