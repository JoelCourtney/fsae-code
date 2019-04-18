// This handles all logic for the module, including Plausibility checks, throttle, clutch, and shifting.

#ifndef BRAIN_H
#define BRAIN_H

#include "PWMTracker.h"
#include "Timer.h"
#include "IO.h"

class Brain {
      // for shifting
      int targetGear;
      int finalGear;
//      long int shiftRequestTime;
//      long int clutchRampUpCompleteTime;
//      long int shiftRampUpCompleteTime;
//      long int shiftRampDownCompleteTime;
      int shiftState;

      // for keeping track of plausibility failures
      Timer timers[6];

      // empty for now. Will be used for rev matching
      static const double gearRatios[];

      // for simplicity
      inline bool IsShifting();

      void ShiftUp();
      void ShiftDown();

      // calculates the revmatched TPS output given input wheelspeeds
      double RevMatch(Input);

      void CheckPlausibility(Input,Output&);
      void ShiftAndThrottle(Input,Output&);
      
public:
      // will somehow need to detect which gear its in, then shift to first.
      bool Initialize();

      // do all the things
      Output Update(Input);
};

#endif
