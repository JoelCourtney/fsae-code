#ifndef IO_H
#define IO_H

#include <SPI.h>
#include <SD.h>
#include "InterruptTracker.h"
#include "Constants.h"

// All information being sent out of PCM
struct Output {
  double throttle, clutch, shiftUp, shiftDown;
  bool ignitionCut, fuelCut, throttleCut, brakelight;
};

// All information being read into PCM
struct Input {
  double TPS1, TPS2;
  double APPS1, APPS2;
  double BSE1, BSE2;
  bool paddleUp, paddleDown;
  InterruptTracker wheelSpeed[4];
  InterruptTracker RPM; // replace with crankSpeed
  int gear;

  double TPSAve();
  double APPSAve();
  double BSEAve();
  double wsAve();
};

struct PassThrough {
  double coolantTemp, intakeTemp, ambientTemp, oilTemp, exhaustTemp;
  double oilPressure;
  double Oxy1, Oxy2;
  double MAF, MAP;
  double knock;
  double fuelPressure;
};

struct IO {
private:
      static unsigned long lastPaddleUpHigh;
      static unsigned long lastPaddleDownHigh;

      static bool canReceived;

      static PassThrough pass;
      static unsigned long lastLog;
      static char logName[12];

public:
      static void CAN_ISR();

      static int Initialize();

      static Input ReadInputs();
      static void SendOutputs(Output);

      static void CutThrottle(int);
      static void CutIgnition();
};

#endif
