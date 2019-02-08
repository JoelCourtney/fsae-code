#ifndef IO_H
#define IO_H

#include <SPI.h>
#include <SD.h>

// All information being sent out of PCM
struct Output {
  bool shiftUp, shiftDown;
};

// All information being read into PCM
struct Input {
  bool paddleUp, paddleDown;
};

class IO {
private:
      static unsigned long lastPaddleUpHigh;
      static unsigned long lastPaddleDownHigh;

      static bool canReceived;

      static unsigned long lastLog;
      static char logName[12];

public:
      static void CAN_ISR();

      static int Initialize();

      static Input ReadInputs();
      static void SendOutputs(Output);

//      static void CutThrottle(int);
//      static void CutIgnition();
};

#endif
