#ifndef INTERRUPTTRACKER_H
#define INTERRUPTTRACKER_H

#include <Arduino.h>

// Keeps track of wheel speed and RPM sensors via interrupts.

struct InterruptTracker {
      long int lastPulse = millis();
      double rate;
};

struct InterruptMonitoring {
  static InterruptTracker RPM;
  static InterruptTracker wheelSpeed[4];

  // Individual methods for interrupt handlers.  
  static void RPMPulse();
  static void WheelPulse0();
  static void WheelPulse1();
  static void WheelPulse2();
  static void WheelPulse3();
};

#endif
