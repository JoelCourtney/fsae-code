#ifndef LEDS_H
#define LEDS_H

class LEDs {
  static unsigned int masks[];
  static unsigned int lastState;
  
public:
  static void Initialize();
  static void Write(unsigned int RPM);
}

#endif
