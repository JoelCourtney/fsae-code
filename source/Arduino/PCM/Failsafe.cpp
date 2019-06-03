#include "Failsafe.h"
#include <avr/wdt.h>

bool Failsafe::active = false;

void Failsafe::initialize() {
  
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
  return enable;
}

ISR(WDT_vect) {
  // cut power to throttle, ignition, fuel, then hang. Must cycle power completely.
  digitalWrite(OUT_IGNITION_CUT, true);
  digitalWrite(OUT_FUEL_CUT, true);
  digitalWrite(OUT_THROTTLE_CUT, true);
  while(true);
}
