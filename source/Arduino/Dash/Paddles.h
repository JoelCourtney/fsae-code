#ifndef PADDLES_H
#define PADDLES_H

class Paddles {
  static unsigned long lastUp;
  static unsigned long lastDown;
public:
  static void Initialize();
  static bool ReadUp();
  static bool ReadDown();
}

#endif
