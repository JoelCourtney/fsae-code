#include "LEDs.h"
#include "Constants.h"
#include <Arduino.h>

unsigned int LEDs::lastState = 30001;

bool LEDs::active = false;

void LEDs::initialize() {
  pinMode(LED_LATCH, OUTPUT);
  pinMode(LED_CLOCK, OUTPUT);
  pinMode(LED_DATA, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT);
  active = true; // no way to tell if failed
}

void LEDs::write(unsigned int RPM) {
  digitalWrite(41, HIGH);
  digitalWrite(42, HIGH);
  unsigned int state = RPM / 10;
  if (state != lastState) {
    lastState = state;
    digitalWrite(LED_LATCH, HIGH);
    // shift out the bits:
    unsigned int bits = (1 << state) - 1;
    shiftOut(LED_DATA, LED_CLOCK, MSBFIRST, bits >> 8);
    shiftOut(LED_DATA, LED_CLOCK, MSBFIRST, bits);
     
    //take the latch pin high so the LEDs will light up:
    digitalWrite(LED_LATCH, LOW);
  }
//digitalWrite(LED_LATCH, HIGH);
//shiftOut(LED_DATA, LED_CLOCK, MSBFIRST, (millis()/1000)%256);
//shiftOut(LED_DATA, LED_CLOCK, MSBFIRST, (millis()/1000)%256);
//digitalWrite(LED_LATCH, LOW);
}

bool LEDs::areActive() {
  return active;
}
