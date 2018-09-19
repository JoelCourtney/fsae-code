#ifndef BRAIN_H
#define BRAIN_H

#include "PWMTracker.h"
#include "Timer.h"

class Brain {
      int currentGear;
      int targetGear;
      int intermediateGear;
      long int shiftRequestTime;
      long int clutchRampUpCompleteTime;
      long int shiftRampUpCompleteTime;
      long int shiftRampDownCompleteTime;
      int shiftState;

      Timer timers[6];

      double gearRatios[1] = {1};
      bool IsShifting();

      void ShiftUp();
      void ShiftDown();

      double RevMatch(Input);
public:
      bool Initialize();
      Output Update(Input);
};

#endif
