#include "Parameters.h"
#include "BrakeThrottleMap.h"
#include "APPSTPSMap.h"
#include "Timer.h"
#include "Shifter.h"
#include "Constants.h"

Parameters p;
Shifter s;
Timer timers[6];

void setup() {
  millis();
  while (!p.Initialize()) {};
  while (!s.Initialize()) {};
  Serial.begin(9600);
}

bool sortaEquals(double a, double b) { return true; }

void checkPlausibility() {
  if (true) { //check wiring
    timers[TIMER_WIRING].Toggle();
  }
  if (sortaEquals(p.APPS1, p.APPS2) == timers[TIMER_APPSDIFF].running) {
    timers[TIMER_APPSDIFF].Toggle();
  }
  int APPSave = (p.APPS1 + p.APPS2) / 2;
  if ((p.TPS1 == p.TPS2) == timers[TIMER_TPSDIFF].running) {
    timers[TIMER_TPSDIFF].Toggle();
  }
  int TPSave = (p.TPS1 + p.TPS2) / 2;
  if (true == timers[TIMER_SIGNALRANGE].running) { // operating ranges good
    timers[TIMER_SIGNALRANGE].Toggle();
  }
  if (BrakeThrottleMap::CheckMap(TPSave,p.BSE1) == timers[TIMER_BRAKETHROTTLEDIFF].running) {
    timers[TIMER_BRAKETHROTTLEDIFF].Toggle();
  }
  if ((p.TPS1 == p.throttle) == timers[TIMER_EXPTPSDIFF].running) {
    timers[TIMER_EXPTPSDIFF].Toggle();
  }

  for (int i = 5; i >= 0; i--) {
    if (timers[i].running && (timers[i].GetDuration() > 100)) {
      int enforce = 0;
      if (i == 5) {
        enforce += ENFORCE_EXPTPSDIFF;
      }
      if (i == 4) {
        enforce += ENFORCE_BRAKETHROTTLEDIFF;
      }
      p.CutThrottle(enforce);
    }
  }
}

void updateThrottle() {
      if (p.shiftUp) {
           s.ShiftUp();
           //give shifter outputs to p;
      }
      if (p.shiftDown) {
           s.ShiftDown();
           //give shifter outputs to p;
      }
      p.clutch = s.shifting;
      if (s.shifting) {
           p.throttle = s.RevMatchTPS(p.wheelSpeed, p.RPM);
      } else {
           p.throttle = APPSTPSMap::Map(p.APPS1);
      }
}

void loop() {
  p.ReadInputs();
  checkPlausibility();
  updateThrottle();
  p.SendOutputs();
}
