#include "Seg.h"
#include "Constants.h"
#include <Arduino.h>

unsigned short int Seg::plex = 0;
bool Seg::active = false;

void Seg::initialize() {
  pinMode(OUT_DECODER_A, OUTPUT);
  pinMode(OUT_DECODER_B, OUTPUT);
//  pinMode(OUT_DECODER_C, OUTPUT);
//  pinMode(OUT_DECODER_D, OUTPUT);
  pinMode(OUT_DIGIT_1, OUTPUT);
  pinMode(OUT_DIGIT_2, OUTPUT);
  pinMode(OUT_DIGIT_3, OUTPUT);
  pinMode(OUT_DIGIT_4, OUTPUT);
  pinMode(OUT_DIGIT_5, OUTPUT);
  active = true; // no way to tell if failed.
}

void Seg::write(unsigned int n) {
//  plex = (plex + 1) % 5;
//  digitalWrite(OUT_DIGIT_1, LOW);
  digitalWrite(OUT_DIGIT_2, LOW);
  digitalWrite(OUT_DIGIT_3, LOW);
  digitalWrite(OUT_DIGIT_4, LOW);
  digitalWrite(OUT_DIGIT_5, LOW);
digitalWrite(OUT_DIGIT_1,HIGH);
//
//  int mod = 10;
//  for (int i = 0; i < plex; i++) {
//    mod *= 10;
//  }
//  unsigned digit = n % mod / (mod / 10);
//  digitalWrite(OUT_DECODER_A, digit & 1);
//  digitalWrite(OUT_DECODER_B, digit & 2);
//  digitalWrite(OUT_DECODER_C, digit & 4);
//  digitalWrite(OUT_DECODER_D, digit & 8);
  digitalWrite(OUT_DECODER_A, HIGH);
  digitalWrite(OUT_DECODER_B, LOW);
//  digitalWrite(OUT_DECODER_C, HIGH);
//  digitalWrite(OUT_DECODER_D, LOW);
//
//
//  switch (plex) {
//    case 0:
//      digitalWrite(OUT_DIGIT_1, HIGH);
//      break;
////    case 1:
////      digitalWrite(OUT_DIGIT_2, HIGH);
////      break;
////    case 2:
////      digitalWrite(OUT_DIGIT_3, HIGH);
////      break;
////    case 3:
////      digitalWrite(OUT_DIGIT_4, HIGH);
////      break;
////    case 4:
////      digitalWrite(OUT_DIGIT_5, HIGH);
////      break;
//  }
}

bool Seg::isActive() {
  return true;
}
