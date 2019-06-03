#ifndef THROTTLE_H
#define THROTTLE_H

class Throttle {
  static bool active;

public:
  static void initialize();
  static float read();
  static float write(float throttle);
  static isActive();
};

#endif
