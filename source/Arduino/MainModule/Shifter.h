// This is gonna be a LOT more complicated than what I have here.
#pragma once

#include "PWMTracker.h"

class Shifter {
      int currentGear;
      int targetGear;

      double gearRatios[1] = {1};
public:
      bool shifting = false;

      bool Initialize();

      void ShiftUp();
      void ShiftDown();

      double RevMatchTPS(PWMTracker*, PWMTracker);
};
