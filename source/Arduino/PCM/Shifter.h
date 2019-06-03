#ifndef SHIFTER_H
#define SHIFTER_H

class Shifter {
  static bool active;
  static short int currentGear;
  static short int targetGear;
  static short int state;

public:
  static void initialize();
  static void shiftUp();
  static void shiftDown();
  static void neutral();
  
  static void update();

  static void readGear();

  static bool isActive();
  static bool isShifting();
};

#endif
