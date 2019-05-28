#include "Paddles.h"
#include "Constants.h"
#include <Arduino.h>

bool Paddles::active = false;

unsigned long Paddles::lastUp = -PADDLE_DEAD_TIME;
unsigned long Paddles::lastDown = -PADDLE_DEAD_TIME;

void Paddles::initialize() {
  pinMode(IN_SHIFTUP_PADDLE, INPUT);
  pinMode(IN_SHIFTDOWN_PADDLE, INPUT);
  active = true; // no way to tell if failed.
}

bool Paddles::readUp() {
  bool up = digitalRead(IN_SHIFTUP_PADDLE);
  if (up) {
    int diff = millis() - lastUp;
    lastUp = millis();
    if (diff < PADDLE_DEAD_TIME) {
      up = false;
    }
  }
  return up;
}

bool Paddles::readDown() {
  bool down = digitalRead(IN_SHIFTUP_PADDLE);
  if (down) {
    int diff =  millis() - lastDown;
    lastDown = millis();
    if (diff < PADDLE_DEAD_TIME) {
      down = false;
    }
  }
  return down;
}

bool Paddles::isActive() {
  return active;
}
