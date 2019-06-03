#include "Throttle.h"
#include <Arduino.h>
#include "Constants.h"

bool Throttle::active = false;
float Throttle::tps1 = 0;
float Throttle::tps2 = 0;
float Throttle::outTPS = 0;

void Throttle::initialize() {
  pinMode(IN_TPS1, INPUT);
  pinMode(IN_TPS2, INPUT);
  pinMode(OUT_THROTTLE, OUTPUT);
  active = true;
}

void Throttle::update() {
  tps1 = analogRead(IN_TPS1);
  tps2 = analogRead(IN_TPS2);
}

float Throttle::read() {
  return (tps1 + tps2) / 2;
}

float Throttle::diff() {
  return tps1 - tps2;
}

float Throttle::expTPS() {
  return outTPS;
}

float Throttle::expDiff() {
  return outTPS - read();
}

void Throttle::write(float throttle) {
  outTPS = throttle;
  analogWrite(OUT_THROTTLE, throttle);
}

bool Throttle::isActive() {
  return active;
}
