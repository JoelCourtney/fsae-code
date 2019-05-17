#ifndef CAN_H
#define CAN_H

#include "Messages.h"

class CAN {
  static bool active;
public:
  static void initialize();
  static void sendChar(char c, unsigned long id);
  static void write(RawMessage m, unsigned long id);
  static bool isActive();
};

#endif
