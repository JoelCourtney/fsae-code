#include "IO.h"
#include "Constants.h"
#include "Brain.h"
#include "BrakeThrottleMap.h"
#include "APPSTPSMap.h"

bool Brain::Initialize() {
  // shift into first?
  currentGear = 1;
  targetGear = 1;
  intermediateGear = 1;
  shiftRequestTime = 0;
  clutchRampUpCompleteTime = 0;
  shiftRampUpCompleteTime = 0;
  shiftRampDownCompleteTime = 0;
  shiftState = SHIFT_IDLE;
  return true; // will update later to return false on failure.
}

bool Brain::IsShifting() {
  return shiftState != SHIFT_IDLE;
}

void Brain::ShiftUp() {
  if (targetGear < TOP_GEAR) {
    targetGear++;
    if (shiftState == SHIFT_IDLE) {
      shiftState = SHIFT_CLUTCH_RAMPUP;
      shiftRequestTime = millis();
    }
  }
}

void Brain::ShiftDown() {
  if (targetGear < TOP_GEAR) {
    targetGear++;
    if (shiftState == SHIFT_IDLE) {
      shiftState = SHIFT_CLUTCH_RAMPUP;
      shiftRequestTime = millis();
    }
  }
}

double Brain::RevMatch(Input in) {
  double ws = in.wsAve();
  return 0.5;
}

inline bool sortaEquals(double a, double b) {
  return (abs(a - b) / ((a + b) / 2)) < 0.1;
}

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
  if (BrakeThrottleMap::CheckMap(TPSave, in.BSE1) == timers[TIMER_BRAKETHROTTLEDIFF].running) {
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

  // NEED TO ACTUALLY READ PADDLE INPUTS
  
  Output out;
  if (IsShifting()) {
    switch (shiftState) {
      case SHIFT_IDLE: {
        // this should never happen. like this is actually impossible
      }
      case SHIFT_CLUTCH_RAMPUP: { // 1
        long int currentTime = millis();
        if (currentTime - shiftRequestTime > PULSE_CLUTCHOUT_TIME) {
          out.clutch = (currentTime - shiftRequestTime) * PULSE_CLUTCH_AMPLITUDE / PULSE_CLUTCHOUT_TIME;
          out.shiftUp = 0;
          out.shiftDown = 0;
          out.throttle = APPSTPSMap::Map(in.TPSAve());
        } else {
          if (targetGear != currentGear) {
            clutchRampUpCompleteTime = currentTime;
            int diff = targetGear - currentGear;
            intermediateGear = targetGear + (diff > 0) - (diff < 0);
            shiftState = SHIFT_SHIFTER_RAMPUP;
          } else {
            shiftRampDownCompleteTime = currentTime;
            shiftState = SHIFT_CLUTCH_RAMPDOWN;
          }
        }
      }
      case SHIFT_SHIFTER_RAMPUP: { // 2
        long int currentTime = millis();
        if (intermediateGear > currentGear) {
          if (currentTime - clutchRampUpCompleteTime > PULSE_SHIFTUP_TIME) {
            out.clutch = PULSE_CLUTCH_AMPLITUDE;
            out.shiftUp = (currentTime - clutchRampUpCompleteTime) * PULSE_SHIFTUP_AMPLITUDE / PULSE_SHIFTUP_TIME;
            out.shiftDown = 0;
            out.throttle = RevMatch(in);
          } else {
            shiftRampUpCompleteTime = currentTime;
            shiftState = SHIFT_SHIFTER_RAMPDOWN;
          }
        } else {
          if (currentTime - clutchRampUpCompleteTime > PULSE_SHIFTDOWN_TIME) {
            out.clutch = PULSE_CLUTCH_AMPLITUDE;
            out.shiftUp = 0;
            out.shiftDown = (currentTime - clutchRampUpCompleteTime) * PULSE_SHIFTDOWN_AMPLITUDE / PULSE_SHIFTDOWN_TIME;
            out.throttle = RevMatch(in);
          } else {
            shiftRampUpCompleteTime = currentTime;
            shiftState = SHIFT_SHIFTER_RAMPDOWN;
          }
        }
      }
      case SHIFT_SHIFTER_RAMPDOWN: { // 3
        long int currentTime = millis();
        if (intermediateGear > currentGear) {
          if (currentTime - shiftRampUpCompleteTime > PULSE_SHIFTUP_TIME) {
            out.clutch = PULSE_CLUTCH_AMPLITUDE;
            out.shiftUp = PULSE_SHIFTUP_AMPLITUDE - ((currentTime - shiftRampUpCompleteTime) * PULSE_SHIFTUP_AMPLITUDE / PULSE_SHIFTUP_TIME);
            out.shiftDown = 0;
            out.throttle = RevMatch(in);
          } else {
            currentGear = intermediateGear;
            if (targetGear != currentGear) {
              clutchRampUpCompleteTime = currentTime;
              int diff = targetGear - currentGear;
              intermediateGear = targetGear + (diff > 0) - (diff < 0);
              shiftState = SHIFT_SHIFTER_RAMPUP;
            } else {
              shiftRampDownCompleteTime = currentTime;
              shiftState = SHIFT_CLUTCH_RAMPDOWN;
            }
          }
        } else {
          if (currentTime - shiftRequestTime > PULSE_SHIFTDOWN_TIME) {
            out.clutch = PULSE_CLUTCH_AMPLITUDE;
            out.shiftUp = 0;
            out.shiftDown = PULSE_SHIFTDOWN_AMPLITUDE - ((currentTime - shiftRampUpCompleteTime) * PULSE_SHIFTDOWN_AMPLITUDE / PULSE_SHIFTDOWN_TIME);
            out.throttle = RevMatch(in);
          } else {
            currentGear = intermediateGear;
            if (targetGear != currentGear) {
              clutchRampUpCompleteTime = currentTime;
              int diff = targetGear - currentGear;
              intermediateGear = targetGear + (diff > 0) - (diff < 0);
              shiftState = SHIFT_SHIFTER_RAMPUP;
            } else {
              shiftRampDownCompleteTime = currentTime;
              shiftState = SHIFT_CLUTCH_RAMPDOWN;
            }
          }
        }
      }
      case SHIFT_CLUTCH_RAMPDOWN: { // 4
        long int currentTime = millis();
        if (currentTime - shiftRequestTime > PULSE_CLUTCHIN_TIME) {
          out.clutch = PULSE_CLUTCH_AMPLITUDE - ((currentTime - shiftRequestTime) * PULSE_CLUTCH_AMPLITUDE / PULSE_CLUTCHIN_TIME);
          out.shiftUp = 0;
          out.shiftDown = 0;
          out.throttle = APPSTPSMap::Map(in.TPSAve());
        } else {
          if (targetGear != currentGear) {
            shiftState = SHIFT_CLUTCH_RAMPUP;
            shiftRequestTime = currentTime;
          } else {
            shiftState = SHIFT_IDLE;
          }
        }
      }
    }
  } else {
    out.throttle = APPSTPSMap::Map(in.TPSAve());
    out.clutch = 0;
    out.shiftUp = 0;
    out.shiftDown = 0;
  }
  out.brakeLight = in.BSEAve() > 0.1;
  out.ignition = true;
  return out;
}
