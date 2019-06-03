#include "Shifter.h"
#include "Constants.h"

bool Shifter::active = false;
short int Shifter::currentGear = -1;
short int Shifter::targetGear = -1;
short int Shifter::state = 0;

void Shifter::initialize() {
  pinMode(OUT_SHIFTUP_ACTUATOR, OUTPUT);
  pinMode(OUT_SHIFTDOWN_ACTUATOR, OUTPUT);
  for (int i = 1; i <= 6; i++)
    pinMode(IN_GEAR_INDICATOR + i, INPUT_PULLUP);
  readGear();
  targetGear = currentGear;
  if (currentGear != -1) {
    active = true;
  } else {
    
  }
}

void Shifter::shiftUp() {
  if (targetGear < TOP_GEAR) {
    targetGear++;
  }
}

void Shifter::shiftDown() {
  if (targetGear > 1 && true /* revlimit */) {
    targetGear--;
  }
}

void Shifter::neutral() {
  // do neutral things
} 

void Shifter::update() {
  readGear();
  if (targetGear > currentGear && state != 1) {
    analogWrite(OUT_SHIFTDOWN_ACTUATOR, 0);
    analogWrite(OUT_SHIFTUP_ACTUATOR, SHIFT_SHIFTUP_MAX);
    state = 1;
  } else if (targetGear < currentGear && state != -1) {
    analogWrite(OUT_SHIFTUP_ACTUATOR, 0);
    analogWrite(OUT_SHIFTDOWN_ACTUATOR, SHIFT_SHIFTUP_MAX);
    state = 0;
  } else if (state != 0) {
    analogWrite(OUT_SHIFTUP_ACTUATOR, 0);
    analogWrite(OUT_SHIFTDOWN_ACTUATOR, 0);
    state = 0;
  }
}

void Shifter::readGear() {
  short int gear = -1;
  for (int i = 1; i <= 6; i++) {
    if (digitalRead(IN_GEAR_INDICATOR + i)) {
      gear = i;
      break;
    }
  }
  currentGear = gear;
}

bool Shifter::isActive() {
  return active;
}

bool Shifter::isShifting() {
  return currentGear != targetGear;
}
