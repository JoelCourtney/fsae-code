#include "Pedals.h"
#include "Constants.h"
#include <Arduino.h>

bool Pedals::active = false;

float Pedals::apps1 = 0;
float Pedals::apps2 = 0;
float Pedals::bse = 0;

short Pedals::apps1Raw = 0;
short Pedals::apps2Raw = 0;
short Pedals::bseRaw = 0;

void Pedals::initialize() {
  pinMode(IN_BSE, INPUT);
  pinMode(IN_APPS1, INPUT);
  pinMode(IN_APPS2, INPUT);
  active = true;
}

void Pedals::update() {
  apps1Raw = analogRead(IN_APPS1);
  apps2Raw = analogRead(IN_APPS2);
  bseRaw = analogRead(IN_BSE);
  apps1 = 100*(apps1Raw/1023.);
  apps2 = 100*(apps2Raw/1023.);
  bse = 100*(bseRaw/1023.);
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

short Pedals::readAPPSRaw() {
  return (apps1Raw + apps2Raw) / 2;
}

//short Pedals::readAPPS2Raw() {
//  return apps2Raw;
//}

short Pedals::readBSERaw() {
  return bseRaw;
}

bool Pedals::isActive() {
  return active;
}
