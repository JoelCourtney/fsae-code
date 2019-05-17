#include "LEDs.h"
#include "Constants.h"
#include <Arduino.h>

unsigned int LEDs::masks[] = {
  0b1,
  0b10,
  0b100,
  0b1000,
  0b100000000000,
  0b10000000000,
  0b1000000000,
  0b100000000,
  0b10010000,
  0b1100000
};

unsigned int LEDs::lastState = 30001;

bool LEDs::active = false;

void LEDs::initialize() {
  pinMode(LED_LATCH, OUTPUT);
  pinMode(LED_CLOCK, OUTPUT);
  pinMode(LED_DATA, OUTPUT);
  active = true; // no way to tell if failed
}

void LEDs::write(unsigned int RPM) {
  unsigned int state = 2;
  if (state != lastState) {
    lastState = state;
    digitalWrite(LED_LATCH, LOW);
    // shift out the bits:
    unsigned int bits = 0;
    for (unsigned short int i = 0; i < state; i++) {
      bits |= masks[i];
    }
    shiftOut(LED_DATA, LED_CLOCK, MSBFIRST, bits >> 8);
    shiftOut(LED_DATA, LED_CLOCK, MSBFIRST, bits);  
     
    //take the latch pin high so the LEDs will light up:
    digitalWrite(LED_LATCH, HIGH);
  }
}

bool LEDs::areActive() {
  return active;
}
