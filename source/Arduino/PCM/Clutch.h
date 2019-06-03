#ifndef CLUTCH_H
#define CLUTCH_H

class Clutch {
  static bool active;
  static bool out;
  
public:
  static void initialize();
  static void write(bool _out);
  static void update();
  static bool isActive();
};

#endif
