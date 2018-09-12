// This is gonna be a LOT more complicated than what I have here.
#ifndef BRAIN_H
#define BRAIN_H

#include "PWMTracker.h"
#include "Timer.h"

struct ShiftState {
  int currentGear;
  int targetGear;

  long int requestTime;
  long int clutchCompleteTime;
  long int shiftCompleteTime;

  ShiftState* next;
};

class Brain {
      ShiftState* shiftState;

      Timer timers[6];

      double gearRatios[1] = {1};
      bool Shifting();

      void ShiftUp();
      void ShiftDown();
public:
      bool Initialize();
      Output Update(Input);
};

#endif
