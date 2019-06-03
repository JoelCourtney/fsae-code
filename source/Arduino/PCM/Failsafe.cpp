#include "Failsafe.h"
#include <avr/wdt.h>
#include "CAN.h"
#include "Throttle.h"
#include "Pedals.h"
#include "Constants.h"

bool Failsafe::active = false;

Timer Failsafe::appsDiff;
Timer Failsafe::tpsDiff;
Timer Failsafe::brakeThrottleConflict;
Timer Failsafe::tpsExpected;

bool Failsafe::safe = false;

void Failsafe::initialize() {
  appsDiff.name = "APPSDIFF";
  tpsDiff.name = "TPSDIFF";
  brakeThrottleConflict.name = "BRAKETPS";
  tpsExpected.name = "TPSEXPEC";
  
  setDogEnable(true);
  safe = true;
  active = true;
}

void Failsafe::update() {
  feedDog();

  safe = true;

  /* Plausibility Checks */
  
  if (false) /* Check wiring operating ranges */ {
    Throttle::write(0);
    safe = false;
    ErrorMessage em("badwires");
    CAN::write(&em);
  }

  if ((abs(Pedals::appsDiff()) / Pedals::readAPPS() < 0.1) == appsDiff.running) {
    appsDiff.toggle();
  }
  if (appsDiff.running)
    safe &= check(appsDiff);

  if ((abs(Throttle::diff()) / Throttle::read() < 0.1) == tpsDiff.running) {
    tpsDiff.toggle();
  }
  if (tpsDiff.running)
    safe &= check(tpsDiff);

  if ((Pedals::readBSE() < 0.15 || Throttle::read() < 0.15) == brakeThrottleConflict.running) {
    brakeThrottleConflict.toggle();
  }
  if (brakeThrottleConflict.running)
    safe &= check(brakeThrottleConflict);

  if (((2*Throttle::expDiff() / (Throttle::read() + Throttle::expTPS())) < 0.1) == tpsExpected.running) {
    tpsExpected.toggle();
  }
  if (tpsExpected.running)
    safe &= check(tpsExpected);

  /* Shutdowns must last until throttle is at 0 for 1 sec */

  static int lastUnsafe = 0;
  if (safe) {
    if (millis() - lastUnsafe < 1000) {
      safe = false;
      if (Throttle::read() != 0) {
        lastUnsafe = millis();
      }
    }
  } else {
    lastUnsafe = millis();
  }

  if (safe) {
    setFuel(true);
    setIgnition(true);
  }
}

void Failsafe::setDogEnable(bool enable) {
  active = enable;
  if (enable) {
    wdt_enable(WDTO_500MS);
  } else {
    wdt_disable();
  }
}

void Failsafe::feedDog() {
  wdt_reset();
}

bool Failsafe::isActive() {
  return active;
}

bool Failsafe::check(Timer t) {
  int dur = t.getDuration();
  if (dur >= 1000) {
    setIgnition(false);
    setFuel(false);
    cutThrottle();
    static int lastHardError = 0;
    int now = millis();
    if (now - lastHardError > 50) {
      ErrorMessage em(t.name);
      CAN::write(&em);
      lastHardError = now;
    }
    return false;
  }
  if (dur >= 100) {
    cutThrottle();
    static int lastSoftError = 0;
    int now = millis();
    if (now - lastSoftError > 40) {
      ErrorMessage em(t.name);
      CAN::write(&em);
      lastSoftError = now;
    }
    return false;
  }
}

void Failsafe::cutThrottle() {
  Throttle::write(0);
}

void Failsafe::setFuel(bool b) {
  digitalWrite(OUT_FUEL_CUT, b);
}

void Failsafe::setIgnition(bool b) {
  digitalWrite(OUT_IGNITION_CUT, b);
}

bool Failsafe::isSafe() {
  return safe;
}

ISR(WDT_vect) {
  // cut power to throttle, ignition, fuel, then hang. Must cycle power completely.
  Failsafe::cutThrottle();
  Failsafe::setFuel(false);
  Failsafe::setIgnition(false);
  while(true);
}
