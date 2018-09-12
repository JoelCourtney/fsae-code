#ifndef IO_H
#define IO_H

#include "PWMTracker.h"

struct Output {
  double throttle, clutch, shiftUp, shiftDown;
  bool brakeLight;
  bool Ignition;
};

struct Input {
  double TPS1, TPS2;
  double APPS1, APPS2;
  double BSE1, BSE2;
  bool paddleUp, paddleDown;
  PWMTracker wheelSpeed[4];
  PWMTracker RPM;
};

struct IO {
      bool Initialize();

      Input ReadInputs();
      void SendOutputs(Output);

      void CutThrottle(int);
      void CutIgnition();
};

#endif
