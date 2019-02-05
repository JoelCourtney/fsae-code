#include "IO.h"
#include "Constants.h"
#include "Brain.h"
#include "BSETPSMap.h"
#include "APPSTPSMap.h"

const double Brain::gearRatios[6] = {2.846, 2.125, 1.632, 1.3, 1.091, 0.964};

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
  return true; // will update later to return false on failure. Cant do that now because we don't yet have a way to know which gear we start in
}

bool Brain::IsShifting() {
  return shiftState != SHIFT_IDLE;
}

void Brain::ShiftUp() {
  if (targetGear < TOP_GEAR) {
    targetGear++;
    if (targetGear != currentGear && shiftState == SHIFT_IDLE) {
      shiftState = SHIFT_CLUTCH_RAMPUP;
      shiftRequestTime = millis();
    }
  }
}

void Brain::ShiftDown() {
  if (targetGear > 1) {
    targetGear--;
    if (targetGear != currentGear && shiftState == SHIFT_IDLE) {
      shiftState = SHIFT_CLUTCH_RAMPUP;
      shiftRequestTime = millis();
    }
  }
}

double Brain::RevMatch(Input in) {
  double ws = in.wsAve();
  double wsHypo = in.RPM.rate * (Brain::gearRatios[targetGear-1] * FINAL_DRIVE_RATIO);
  if (wsHypo < ws) {
    return 1.0;
  } else {
    return 0.0;
  }
}

// returns true if a and b are within 10% of each other
inline bool sortaEquals(double a, double b) {
  return (abs(a - b) / ((a + b) / 2)) < 0.1;
}

Output Brain::Update(Input in) {
  
  Output out;

  // default cut indicators.
  out.throttleCut = false;
  out.fuelCut = false;
  out.ignitionCut = false;
  
  /* PLAUSIBILITY CHECKS
   *  IC.4.4.3: 10% difference in TPS inputs for 100 ms -> shut down throttle
   *  IC.4.4.7-8: TPS signals outside normal operating range for any amount of time -> shut down throttle
   *  IC.4.7.1: Brakes actuated + throttle is open for 1 second -> shut down throttle
   *    1 second allowed to return to idle. Failure -> shut down fuel and ignition
   *  IC.4.76.2: TPS and expected TPS 10% different for 1 second -> shut down throttle
   *    1 second allowed for discrepancy to stop. Failure -> shut down fuel and ignition
   *  IC.4.7.3: All shutdowns must remain in effect until TPS signals are at or below unpowered default for > 1 second
   *  T.6.2.4: 10% difference in APPS inputs for 100 ms -> shut down throttle
   *  T.6.2.8-9: APPS signals outside normal operating range for any amount of time -> shut down throttle
   *  T.6.3.3-4: 10% difference in BSE inputs for 100 ms or BSE signals outside normal operating range for any time -> shut down throttle
   */

  // Update all timers for plausibility.
  
  if (false) { //check wiring. Cannot be filled in until normal operating ranges are known.
    // operating range failed for any of TPS, APPS, or BSE. shut down throttle
  }
  if (sortaEquals(in.APPS1, in.APPS2) == timers[TIMER_APPS_DIFF].running) {
    timers[TIMER_APPS_DIFF].Toggle();
  }
  if (sortaEquals(in.TPS1,in.TPS2) == timers[TIMER_TPS_DIFF].running) {
    timers[TIMER_TPS_DIFF].Toggle();
  }
  if (sortaEquals(in.BSE1,in.BSE2) == timers[TIMER_BSE_DIFF].running) {
    timers[TIMER_BSE_DIFF].Toggle();
  }
  if (BSETPSMap::CheckMap(in.TPSAve(), in.BSE1) == timers[TIMER_BRAKETHROTTLE_DIFF].running) {
    timers[TIMER_BRAKETHROTTLE_DIFF].Toggle();
  }

  for (int i = 0; i <= 4; i++) {
    if (timers[i].running) {
      int duration = timers[i].GetDuration();
      if (duration > 1000) {
        out.fuelCut = true;
        out.ignitionCut = true;
        out.throttleCut = true;
      } else if (duration > 100) {
        out.throttleCut = true;
      }
    }
  }

  if (in.paddleUp) {
    ShiftUp();
  }
  if (in.paddleDown) {
    ShiftDown();
  }

  /*
   * SHIFTING
   * Consists of four phases:
   *  1. Ramp up signal on clutch. Clutch is in at the end
   *  2. Ramp up signal to shift actuator. Shifter is in between gears at end
   *  3. Ramp down signal to shift actuator. Shifter is at target gear at end
   *  4. Ramp down signal to clutch. Shift is complete.
   *  
   *  Revmatch during 2 and 3.
   *  Reevaluate target gear at ends of 1 and 3. (in case of multiple inputs)
   */

  if (IsShifting()) {
    switch (shiftState) {
      case SHIFT_IDLE: {
        // this should never happen. like this is actually impossible. you should probably cry if you ever manage to get here
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

  // RevMatching or no, if RPM is redlining we need to limit it
  if (in.RPM.rate > RPM_RED_LINE) {
    out.throttle = 0.0;
  }

  if (sortaEquals(in.TPSAve(),out.throttle) == timers[TIMER_EXPTPS_DIFF].running) {
    timers[TIMER_EXPTPS_DIFF].Toggle();
  }
  
  return out;
}
