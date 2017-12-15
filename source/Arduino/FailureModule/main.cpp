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
	// initialize input and output pins
	// initialize any libraries (probably none?)
}

void loop() {
	p.ReadInputs();
	if (somehow check wiring?) {
		timers[TIMER_WIRING].Restart();
	}
	if (p.APPS1 == p.APPS2) {
		timers[TIMER_APPSDIFF].Restart();
	}
	p.APPSave = (p.APPS1 + p.APPS2) / 2;
	if (p.TPS1 == p.TPS2) {
		timers[TIMER_TPSDIFF].Restart();
	}
	p.TPSave = (p.TPS1 + p.TPS2) / 2;
	if (check operating ranges) {
		timers[TIMER_SIGNALRANGE].Restart();
	}
	if (BrakeThrottleMap::CheckMap(p.TPSave,p.BSE)) {
		timers[TIMER_BRAKETHROTTLEDIFF].Restart();
	}
	if (p.TPS == p.TPSexp) {
		timers[TIMER_EXPTPSDIFF].Restart();
	}
	
	for (int i = 5; i >= 0; i--) {
		if (timers[i].GetDuration() > 100) {
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

