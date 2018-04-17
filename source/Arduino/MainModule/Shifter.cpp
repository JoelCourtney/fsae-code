#include "Shifter.h"
#include "Constants.h"

bool Shifter::Initialize() {
  // shift into first?
  return true; // will update later to return false on failure.
}

void Shifter::ShiftUp() {
      if (shifting) {
            targetGear = targetGear + 1;
      } else {
            shifting = true;
            targetGear = currentGear + 1;
            // some other stuff
      }
}

void Shifter::ShiftDown() {
      if (shifting) {
            targetGear = targetGear + 1;
      } else {
            shifting = true;
            targetGear = currentGear - 1;
            // some other stuff
      }
}

double Shifter::RevMatchTPS(PWMTracker* wheelSpeed, PWMTracker revs) {
      if (shifting) {
            int targetRevs = gearRatios[targetGear] * wheelSpeed[0].rate;
            if (revs.rate < targetRevs) { // within some range
                  return FULL_THROTTLE;
            } else if (revs.rate > targetRevs) { // within some range
                  return NO_THROTTLE;
            } else {
                  shifting = false;
                  return -1;
            }
      }
      return -1;
}
