#include "IO.h"
#include "Constants.h"
#include "Brain.h"
#include "BrakeThrottleMap.h"
#include "APPSTPSMap.h"

bool Brain::Initialize() {
  // shift into first?
  shiftState = NULL;
  return true; // will update later to return false on failure.
}

bool Brain::Shifting() {
  return shiftState != NULL;
}

void Brain::ShiftUp() {
      if (Shifting()) {
            // push to ShiftState stack
      } else {
            // push head of ShiftState stack
      }
}

void Brain::ShiftDown() {
      if (Shifting()) {
           // push to ShiftState stack
      } else {
            // push head of ShiftState stack
      }
}

bool sortaEquals(double a, double b) { return true; }

Output Brain::Update(Input in) {
    if (true) { //check wiring
    timers[TIMER_WIRING].Toggle();
  }
  if (sortaEquals(in.APPS1, in.APPS2) == timers[TIMER_APPSDIFF].running) {
    timers[TIMER_APPSDIFF].Toggle();
  }
  int APPSave = (in.APPS1 + in.APPS2) / 2;
  if ((in.TPS1 == in.TPS2) == timers[TIMER_TPSDIFF].running) {
    timers[TIMER_TPSDIFF].Toggle();
  }
  int TPSave = (in.TPS1 + in.TPS2) / 2;
  if (true == timers[TIMER_SIGNALRANGE].running) { // operating ranges good
    timers[TIMER_SIGNALRANGE].Toggle();
  }
  if (BrakeThrottleMap::CheckMap(TPSave,in.BSE1) == timers[TIMER_BRAKETHROTTLEDIFF].running) {
    timers[TIMER_BRAKETHROTTLEDIFF].Toggle();
  }
//  if ((in.TPS1 == in.throttle) == timers[TIMER_EXPTPSDIFF].running) {
//    timers[TIMER_EXPTPSDIFF].Toggle();
//  } THIS NEEDS TO CHECK AFTER THE THROTTLE HAS BEEN CALCULATED

  for (int i = 5; i >= 0; i--) {
    if (timers[i].running && (timers[i].GetDuration() > 100)) {
      int enforce = 0;
      if (i == 5) {
        enforce += ENFORCE_EXPTPSDIFF;
      }
      if (i == 4) {
        enforce += ENFORCE_BRAKETHROTTLEDIFF;
      }
//      io.CutThrottle(enforce);
      // FOR THIS WE ACTUALLY SEND THE CUT SIGNAL THROUGH THE NORMAL ROUTE.
    }
  }
//      if (shifting) {
//            int targetRevs = gearRatios[targetGear] * wheelSpeed[0].rate;
//            if (revs.rate < targetRevs) { // within some range
//                  return FULL_THROTTLE;
//            } else if (revs.rate > targetRevs) { // within some range
//                  return NO_THROTTLE;
//            } else {
//                  shifting = false;
//                  return -1;
//            }
//      }
//      return -1;
Output o;
return o;
}
