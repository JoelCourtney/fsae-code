#ifndef IO_H
#define IO_H

#include <SPI.h>
#include <SD.h>
#include "PWMTracker.h"
#include "Constants.h"

// All information being sent out of PCM
struct Output {
  double throttle = 0, clutch = 0, shiftUp = 0, shiftDown = 0;
  bool ignitionCut = false, fuelCut = false, throttleCut = false, brakelight = false;
};

// All information being read into PCM
struct Input {
  double TPS1 = 0, TPS2 = 0;
  double APPS1 = 0, APPS2 = 0;
  double BSE1 = 0, BSE2 = 0;
  bool paddleUp = false, paddleDown = false;
  PWMTracker finalDrive;
  PWMTracker RPM;
  bool clutchButton = false;
  int gear = -1;

  double TPSAve();
  double APPSAve();
  double BSEAve();
  double wsAve();
};

struct PassThrough {
  double coolantTemp = 0, intakeTemp = 0, ambientTemp = 0, oilTemp = 0, exhaustTemp = 0;
  double oilPressure = 0;
  double Oxy1 = 0, Oxy2 = 0;
  double MAF = 0, MAP = 0;
  double knock = 0;
  double fuelPressure = 0;
};

class IO {
private:
      static unsigned long lastPaddleUpHigh;
      static unsigned long lastPaddleDownHigh;

      static bool canReceived;

      static PassThrough pass;
      static unsigned long lastLog;
      static char logName[12];

      static void SendCANChar(char, unsigned long);

public:
      static void CAN_ISR();

      static int Initialize();

      static Input ReadInputs();
      static void SendOutputs(Output);

//      static void CutThrottle(int);
//      static void CutIgnition();
};

#endif
