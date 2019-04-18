#include "IO.h"
#include "Constants.h"
#include "Brain.h"
#include "APPSTPSMap.h"

const double Brain::gearRatios[6] = {2.846, 2.125, 1.632, 1.3, 1.091, 0.964};

bool Brain::Initialize() {
  targetGear = 1;
  finalGear = 1;
  return true;
}

bool Brain::IsShifting() {
  return shiftState != SHIFT_IDLE;
}

void Brain::ShiftUp() {
  if (finalGear < TOP_GEAR) {
    finalGear++;
  }
}

void Brain::ShiftDown() {
  if (finalGear > 1) {
    finalGear--;
  }
}

double Brain::RevMatch(Input in) {
  double fdHypo = in.RPM.rate * (Brain::gearRatios[finalGear - 1] * FINAL_DRIVE_RATIO);
  if (fdHypo < in.finalDrive.rate) {
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
  //  Serial.println("Tick:");
  //  Serial.println(in.TPS2);
  //  Serial.println(in.TPS2);
  //  Serial.println(in.APPS1);
  //  Serial.println(in.APPS2);
  //  Serial.println(in.BSE1);
  //  Serial.println(in.BSE2);
  //  Serial.println(in.paddleUp);
  //  Serial.println(in.paddleDown);
//  if (in.paddleUp) Serial.println("Up: " + String(millis()));
//  if (in.paddleDown) {
//    Serial.println("Down: " + String(millis()));
//    Serial.println("Final Drive: " + String(in.finalDrive.rate));
//  }

  //  Serial.println("");

  Output out;
  // default cut indicators.
  out.throttleCut = false;
  out.fuelCut = false;
  out.ignitionCut = false;

  ShiftAndThrottle(in,out);
  CheckPlausibility(in,out);

  return out;
}

void Brain::CheckPlausibility(Input in, Output& out) {
   /* PLAUSIBILITY CHECKS
      IC.4.4.3: 10% difference in TPS inputs for 100 ms -> shut down throttle
      IC.4.4.7-8: TPS signals outside normal operating range for any amount of time -> shut down throttle
      IC.4.7.1: Brakes actuated + throttle is open for 1 second -> shut down throttle
        1 second allowed to return to idle. Failure -> shut down fuel and ignition
      IC.4.76.2: TPS and expected TPS 10% different for 1 second -> shut down throttle
        1 second allowed for discrepancy to stop. Failure -> shut down fuel and ignition
      IC.4.7.3: All shutdowns must remain in effect until TPS signals are at or below unpowered default for > 1 second
      T.6.2.4: 10% difference in APPS inputs for 100 ms -> shut down throttle
      T.6.2.8-9: APPS signals outside normal operating range for any amount of time -> shut down throttle
      T.6.3.3-4: 10% difference in BSE inputs for 100 ms or BSE signals outside normal operating range for any time -> shut down throttle
  */

  // Update all timers for plausibility.

  if (false) { //check wiring. Cannot be filled in until normal operating ranges are known.
    // operating range failed for any of TPS, APPS, or BSE. shut down throttle
  }
  if (sortaEquals(in.APPS1, in.APPS2) == timers[TIMER_APPS_DIFF].running) {
    timers[TIMER_APPS_DIFF].Toggle();
  }
  if (sortaEquals(in.TPS1, in.TPS2) == timers[TIMER_TPS_DIFF].running) {
    timers[TIMER_TPS_DIFF].Toggle();
  }
  if (sortaEquals(in.BSE1, in.BSE2) == timers[TIMER_BSE_DIFF].running) {
    timers[TIMER_BSE_DIFF].Toggle();
  }
  if ((in.BSEAve() < 0.15 || in.TPSAve() < 0.15) == timers[TIMER_BRAKETHROTTLE_DIFF].running) {
    timers[TIMER_BRAKETHROTTLE_DIFF].Toggle();
  }
  if (sortaEquals(in.TPSAve(), out.throttle) == timers[TIMER_EXPTPS_DIFF].running) {
    timers[TIMER_EXPTPS_DIFF].Toggle();
  }

  for (int i = 0; i <= 4; i++) {
    if (timers[i].running) {
      int duration = timers[i].GetDuration();
      if (duration > 1000) {
        Serial.println("timer " + String(i) + " failed");
        out.fuelCut = true;
        out.ignitionCut = true;
        out.throttleCut = true;
      } else if (duration > 100) {
        out.throttleCut = true;
      }
    }
  }
}

void Brain::ShiftAndThrottle(Input in, Output& out) {
  if (in.paddleUp) {
    ShiftUp();
  }
  if (in.paddleDown) {
    ShiftDown();
  }

  if (in.gear != finalGear) {
    if (in.gear == targetGear) {
      if (targetGear < finalGear) {
        targetGear++;
      } else if (targetGear > finalGear) {
        targetGear--;
      } else {
        // how
      }
    }
    if (in.gear < targetGear) {
      shiftState = SHIFT_UP;
    } else if (in.gear > targetGear) {
      shiftState = SHIFT_DOWN;
    } else {
      // how
    }
  } else {
    shiftState = SHIFT_IDLE;
  }
  switch (shiftState) {
    case SHIFT_IDLE: {
        out.shiftUp = 0;
        out.shiftDown = 0;
        out.throttle = APPSTPSMap::Map(in.TPSAve());
      }
    case SHIFT_UP: {
        out.shiftUp = SHIFT_SHIFTER_MAX;
        out.shiftDown = 0;
        out.throttle = RevMatch(in);
      }
    case SHIFT_DOWN: {
        out.shiftUp = 0;
        out.shiftDown = SHIFT_SHIFTER_MAX;
        out.throttle = RevMatch(in);
      }
  }
  // RevMatching or no, if RPM is redlining we need to limit it
  if (in.RPM.rate > RPM_RED_LINE) {
    out.throttle = 0.0;
    Serial.println("hi");
  }
}
