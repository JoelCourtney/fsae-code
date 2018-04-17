#pragma once

#include "PWMTracker.h"

struct Parameters {

// inputs
      double TPS1, TPS2;
      double APPS1, APPS2;
      double BSE1, BSE2;
      bool paddleUp, paddleDown;
      PWMTracker wheelSpeed[4];
      PWMTracker RPM;

// outputs
      double throttle;
      bool shiftUp, shiftDown;
      bool clutch;
      bool brakeLight;

      bool Initialize();

      void ReadInputs();
      void SendOutputs();

      void CutThrottle(int);
      void CutIgnition();
};
