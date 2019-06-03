#include "Pedals.h"
#include "Constants.h"

bool Pedals::active = false;

void Pedals::initialize() {
  pinMode(IN_BSE1, INPUT);
  pinMode(IN_BSE2, INPUT);
  pinMode(IN_APPS1, INPUT);
  pinMode(IN_APPS2, INPUT);
  active = true;
}

float Pedals::readAPPS() {
  return (analogRead(IN_APPS1) + analogRead(IN_APPS2)) / 2;
}

float Pedals::readBSE() {
  return analogRead(IN_BSE);
}

bool Pedals::isActive() {
  return active;
}
