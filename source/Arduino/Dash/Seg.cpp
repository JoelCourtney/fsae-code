#include "Seg.h"
#include "Constants.h"
#include <Arduino.h>

unsigned short int Seg::plex = 0;
bool Seg::active = false;

void Seg::initialize() {
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_P0, OUTPUT);
  pinMode(SEG_P1, OUTPUT);
  pinMode(SEG_P2, OUTPUT);
  pinMode(SEG_P3, OUTPUT);
  pinMode(SEG_P4, OUTPUT);
  active = true; // no way to tell if failed.
}

void Seg::write(unsigned int n) {
  plex = (plex + 1) % 4;
  digitalWrite(SEG_P0, LOW);
  digitalWrite(SEG_P1, LOW);
  digitalWrite(SEG_P2, LOW);
  digitalWrite(SEG_P3, LOW);

  int mod = 10;
  for (int i = 0; i < plex; i++) {
    mod *= 10;
  }
  unsigned digit = n % mod / (mod / 10);
  digitalWrite(SEG_A, digit & 1);
  digitalWrite(SEG_B, digit & 2);
  digitalWrite(SEG_C, digit & 4);
  digitalWrite(SEG_D, digit & 8);


  switch (plex) {
    case 0:
      digitalWrite(SEG_P0, HIGH);
      break;
    case 1:
      digitalWrite(SEG_P1, HIGH);
      break;
    case 2:
      digitalWrite(SEG_P2, HIGH);
      break;
    case 3:
      digitalWrite(SEG_P3, HIGH);
      break;
  }
}

bool Seg::isActive() {
  return true;
}
