#ifndef PEDALS_H
#define PEDALS_H

class APPS {
  static bool active;
  
public:
  static void initialize();
  static float readAPPS();
  static float readBSE();

  static bool isActive();
};

#endif
