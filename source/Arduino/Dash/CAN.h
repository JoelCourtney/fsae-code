#ifndef CAN_H
#define CAN_H

class CAN {
public:
  static void Initialize();
  static void SendChar(char c, unsigned long id);
  
};

#endif
