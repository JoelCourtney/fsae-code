#include "Clutch.h"
#include "Constants.h"
#include <Arduino.h>

bool Clutch::active = false;
bool Clutch::out = false;

void Clutch::initialize() {
  pinMode(OUT_CLUTCH_ACTUATOR, OUTPUT);
  active = true;
}

void Clutch::write(bool _out) {
  out = _out;
}

void Clutch::update() {
  static float state = 0.0;
}

bool Clutch::isActive() {
  return active;
}
