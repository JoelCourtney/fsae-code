#include "Pedals.h"
#include "Constants.h"
#include <Arduino.h>

bool Pedals::active = false;

float Pedals::apps1 = 0;
float Pedals::apps2 = 0;
float Pedals::bse = 0;

void Pedals::initialize() {
  pinMode(IN_BSE, INPUT);
  pinMode(IN_APPS1, INPUT);
  pinMode(IN_APPS2, INPUT);
  active = true;
}

void Pedals::update() {
  apps1 = analogRead(IN_APPS1);
  apps2 = analogRead(IN_APPS2);
  bse = analogRead(IN_BSE);
}

float Pedals::readAPPS() {
  return (apps1+apps2)/2;
}

float Pedals::appsDiff() {
  return apps1 - apps2;
}

float Pedals::readBSE() {
  return bse;
}

bool Pedals::isActive() {
  return active;
}
