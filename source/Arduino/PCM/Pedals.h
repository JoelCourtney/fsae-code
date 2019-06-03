#ifndef PEDALS_H
#define PEDALS_H

class Pedals {
  static bool active;

  static float apps1, apps2;
  static float bse;
  
public:
  static void initialize();
  static void update();
  
  static float readAPPS();
  static float readBSE();

  static float appsDiff();

  static bool isActive();
};

#endif
