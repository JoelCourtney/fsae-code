#ifndef THROTTLE_H
#define THROTTLE_H

class Throttle {
  static bool active;

  static float tps1, tps2;
  static float outTPS;

public:
  static void initialize();
  static void update();

  static float read();
  static float diff();
  static float expTPS();
  static float expDiff();
  static void write(float throttle);
  static bool isActive();
};

#endif
