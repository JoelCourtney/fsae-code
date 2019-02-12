#include "Constants.h"

bool up = false;
int upLast = 0;
bool down = false;
int downLast = 0;
int gear = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(OUT_TPS1, OUTPUT);
  pinMode(OUT_TPS2, OUTPUT);
  pinMode(OUT_APPS1, OUTPUT);
  pinMode(OUT_APPS2, OUTPUT);
  pinMode(OUT_BSE1, OUTPUT);
  pinMode(OUT_BSE2, OUTPUT);
  pinMode(OUT_SHIFTUP_PADDLE, OUTPUT);
  pinMode(OUT_SHIFTDOWN_PADDLE, OUTPUT);
  for(int i = 1; i <= 6; i++)
    pinMode(OUT_GEAR_INDICATOR + i, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int t = millis();
  if (t - upLast > 2500) {
    up = !up;
    upLast = t;
    gear = (gear + 1) % 6
  }
  if (t - downLast > 100) {
    down = !down;
    downLast = t;
  }
//  if (up) Serial.println(millis());
  // put your main code here, to run repeatedly:
  analogWrite(OUT_TPS1,millis() % 256);
  analogWrite(OUT_TPS2,millis() % 256);
  analogWrite(OUT_APPS1,millis() % 256);
  analogWrite(OUT_APPS2,millis() % 256);
  analogWrite(OUT_BSE1,millis() % 256);
  analogWrite(OUT_BSE2,millis() % 256);
  digitalWrite(OUT_SHIFTUP_PADDLE, up);
  digitalWrite(OUT_SHIFTDOWN_PADDLE, down);
}
