// Pseudo code for main FailureModule code
// Module-level inputs: APPS1/2, TPS1/2, BSE, TPSexp
// Module-level outputs: APPSave, TPSave, throttleCut, ignitionCut

#define TIMER_WIRING 0
#define TIMER_APPSDIFF 1
#define TIMER_TPSDIFF 2
#define TIMER_SIGNALRANGE 3
#define TIMER_BRAKETHROTTLEDIFF 4
#define TIMER_EXPTPSDIFF 5

#include "Parameters.h"
#include "BrakeThrottleMap.cpp"
#include "Timer.h"

Parameters p;
Timer timers[6];

void setup() {
	while (!p.Initialize()) {};
}

void loop() {
	p.ReadInputs();
	if (somehow check wiring?) {
		timers[TIMER_WIRING].Restart();
	}
	if ((p.APPS1 == p.APPS2) == timers[TIMER_APPSDIFF].running) {
		timers[TIMER_APPSDIFF].Toggle();
	}
	int APPSave = (p.APPS1 + p.APPS2) / 2;
	if ((p.TPS1 == p.TPS2) == timers[TIMER_TPSDIFF].running) {
		timers[TIMER_TPSDIFF].Toggle();
	}
	int TPSave = (p.TPS1 + p.TPS2) / 2;
	if ((operating ranges good) == timers[TIMER_SIGNALRANGE].running) {
		timers[TIMER_SIGNALRANGE].Toggle();
	}
	if (BrakeThrottleMap::CheckMap(TPSave,p.BSE) == timers[TIMER_BRAKETHROTTLEDIFF].running) {
		timers[TIMER_BRAKETHROTTLEDIFF].Toggle();
	}
	if ((p.TPS == p.TPSexp) == timers[TIMER_EXPTPSDIFF].running) {
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
      
      if (p.shiftUp) {
           s.ShiftUp();
           give shifter outputs to p;
      }
      if (p.shiftDown) {
           s.ShiftDown();
           give shifter outputs to p;
      }
      p.clutch = s.shifting;
      if (s.shifting) {
           p.expTPS = s.RevMatchTPS(p.wheelSpeed);
      } else {
           p.expTPS = !p.throttleCut * APPSTPSMap::Map(p.APPS);
      }
	p.SendOutputs();
}

