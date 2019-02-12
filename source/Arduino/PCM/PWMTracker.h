#ifndef PWMTRACKER_H
#define PWMTRACKER_H

#include <Arduino.h>

// Keeps track of wheel speed and RPM sensors via PWMs.

struct PWMTracker {
      long int lastPulse = millis();
      double rate = 0;
};

struct PWMMonitoring {
  static PWMTracker RPM;
  static PWMTracker wheelSpeed[4];

  // Individual methods for PWM handlers.  
  static void RPMPulse();
  static void WheelPulse0();
  static void WheelPulse1();
  static void WheelPulse2();
  static void WheelPulse3();
};

#endif
