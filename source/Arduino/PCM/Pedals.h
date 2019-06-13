#ifndef PEDALS_H
#define PEDALS_H

class Pedals {
  static bool active;

  static short apps1, apps2;
  static float bse;

  static short apps1Raw, apps2Raw;
  static short bseRaw;
  
public:
  static void initialize();
  static void update();
  
  static float readAPPS();
  static float readBSE();

  static short int readAPPSRaw();
  static short int readBSERaw();

  static float appsDiff();

  static bool isActive();
};

#endif
