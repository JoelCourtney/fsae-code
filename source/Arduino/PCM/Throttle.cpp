#include "Throttle.cpp"

bool Throttle::active = false;

void Throttle::initialize() {
  pinMode(IN_TPS1, INPUT);
  pinMode(IN_TPS2, INPUT);
  pinMode(OUT_THROTTLE, OUTPUT);
  active = true;
}

float Throttle::read() {
  return (analogRead(IN_TPS1) + analogRead(IN_TPS2)) / 2;
}

void Throttle::write(float throttle) {
  analogWrite(OUT_THROTTLE, throttle);
}

bool Throttle::isActive() {
  return active;
}
