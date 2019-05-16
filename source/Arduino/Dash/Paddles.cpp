#include "Paddles.h"
#include "Constants.h"

void Paddles::Initialize() {
  // output pins
}

bool Paddles::ReadUp() {
  bool up = digitalRead(IN_SHIFTUP_PADDLE);
  if (up)
    int diff =  millis() - lastUp;
    lastUp = millis();
    if (diff < PADDLE_DEAD_TIME) {
      up = false;
    }
  }
  return up;
}

bool Paddles::ReadDown() {
  bool down = digitalRead(IN_SHIFTUP_PADDLE);
  if (down)
    int diff =  millis() - lastDown;
    lastDown = millis();
    if (diff < PADDLE_DEAD_TIME) {
      down = false;
    }
  }
  return down;
}
