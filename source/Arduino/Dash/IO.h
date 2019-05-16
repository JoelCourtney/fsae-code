#ifndef IO_H
#define IO_H

#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>
#include "Constants.h"

// All information being sent out of PCM
struct Output {
  bool shiftUp, shiftDown;
  double RPM;
  double oilTemp, oilPressure;
  unsigned int seg;
};

// All information being read into PCM
struct Input {
  bool paddleUp, paddleDown;
};

class IO {
private:
      static int plexIndex;
      
      

      static unsigned long lastLog;
      static char logName[12];

      static void SendCANChar(char, unsigned long);
public:

      static int Initialize();

      static Input ReadInputs();
      static void SendOutputs(Output);

//      static void CutThrottle(int);
//      static void CutIgnition();
};

#endif
