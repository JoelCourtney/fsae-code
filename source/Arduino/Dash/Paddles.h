#ifndef PADDLES_H
#define PADDLES_H

class Paddles {
  static unsigned long lastUp;
  static unsigned long lastDown;

  static bool active;
  
public:
  static void initialize();
  static bool readUp();
  static bool readDown();

  static bool isActive();
};

#endif
