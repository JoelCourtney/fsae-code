#include "Shifter.h"

bool Shifter::Initialize() {
  for(int i = 0; i < 6; i++) {
    ShiftDown();
  }
  ShiftUp(); // trying to get into neutral.

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

double Shifter::RevMatchTPS(double wheelSpeed, double revs) {
      if (shifting) {
            targetRevs = gearRatios[targetGear] * wheelSpeed;
            if (revs < targetRevs) { // within some range
                  return FULL_THROTTLE;
            } else if (revs > targetRevs) { // within some range
                  return NO_THROTTLE;
            } else {
                  shifting = false;
                  return -1;
            }
      }
      return -1;
}
