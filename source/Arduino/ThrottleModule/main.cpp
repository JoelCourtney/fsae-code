// Pseudo code for main ThrottleArduino code
// Module-level inputs: throttleCut, APPS, shiftUp, shiftDown, wheelSpeed, revs
// Module-level outputs: TPSexp, clutch, shifter controls of some variety

#include "Parameters.h"
#include "APPSTPSMap.cpp"
#include "Shifter.h"

Parameters p;
Shifter s;

void setup() {
	// initialize input and output pins
	// initialize any libraries (CAN, at least)
      // need to find the current gear.
      // make sure shifter is in neutral, or something
}

void loop() {
	p.ReadInputs();
      if (p.shiftUp) {
            s.ShiftUp();
            give shifter outputs to p;
      }
      if (p.shiftDown) {
            s.ShiftDown();
            give shifter outputs to p;
      }
      p.clutch = s.shifting;
      if (!p.throttleCut) {
            p.expTPS = APPSTPSMap::Map(p.APPS);
      } else if (s.shifting) {
            p.expTPS = s.RevMatchTPS(p.wheelSpeed)
      } else {
            p.expTPS = 0;
      }
      p.SendOutputs();
}

