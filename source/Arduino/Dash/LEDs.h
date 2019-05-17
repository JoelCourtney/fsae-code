#ifndef LEDS_H
#define LEDS_H

class LEDs {
  static unsigned int masks[];
  static unsigned int lastState;

  static bool active;
  
public:
  static void initialize();
  static void write(unsigned int RPM);

  static bool areActive();
};

#endif
