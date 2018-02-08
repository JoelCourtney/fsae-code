// LEFT TO DO
// Fix includes (easy, can be post pdr)
// figure out PWM inputs / outputs. Interrupts?
// pin C-16 on the ECU.

#include "Parameters.h"
#include "BrakeThrottleMap.cpp"
#include "Timer.h"

Parameters p;
Shifter s;
Timer timers[6];

void setup() {
	while (!p.Initialize()) {};
	while (!s.Initialize(&p)) {};
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
