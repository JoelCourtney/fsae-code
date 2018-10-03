#ifndef IO_H
#define IO_H

#include "InterruptTracker.h"

// All information being sent out of PCM
struct Output {
  double throttle, clutch, shiftUp, shiftDown;
  bool ignitionCut, fuelCut, throttleCut;
};

// All information being read into PCM
struct Input {
  double TPS1, TPS2;
  double APPS1, APPS2;
  double BSE1, BSE2;
  bool paddleUp, paddleDown;
  InterruptTracker wheelSpeed[4];
  InterruptTracker RPM;

  double TPSAve();
  double APPSAve();
  double BSEAve();
  double wsAve();
};

struct IO {
      bool Initialize();

      Input ReadInputs();
      void SendOutputs(Output);

      void CutThrottle(int);
      void CutIgnition();
};

#endif
