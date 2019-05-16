#include "LEDs.h"

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
}

unsigned int LEDs::lastState = 1000;

void LEDs::Initialize() {
  /*
   *  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
   */
}

void LEDs::Write(unsigned int RPM) {
  unsigned int state = 2;
  if (state != lastState) {
    lastState = state;
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    unsigned int bits = 0;
    for (unsigned short int i = 0; i < state; i++) {
      bits |= masks[i];
    }
    shiftOut(dataPin, clockPin, MSBFIRST, bits >> 8);
    shiftOut(dataPin, clockPin, MSBFIRST, bits & mask);  
     
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
  }
}
