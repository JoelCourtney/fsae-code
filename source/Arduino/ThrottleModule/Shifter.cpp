#include "Shifter.h"

void Shifter::ShiftUp() {
      if (shifting) {
            panic();
      } else {
            shifting = true;
            targetGear = currentGear + 1;
            // some other stuff
      }
}

void Shifter::ShiftDown() {
      if (shifting) {
            panic();
      } else {
            shifting = true;
            targetGear = currentGear - 1;
            // some other stuff
      }
}

double Shifter::RevMatchTPS(double wheelSpeed, double revs) {
      if (shifting) {
            targetRevs = gearRatios[targetGear] * wheelSpeed;
            if (revs < targetRevs) {
                  return full throttle;
            } else if (revs > targetRevs) {
                  return zero throttle;
            } else {
                  shifting = false;
                  return -1;
            }
      }
      return -1;
}