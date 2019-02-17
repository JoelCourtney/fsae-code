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
  static PWMTracker finalDrive;

  // Individual methods for PWM handlers.  
  static void RPMPulse();
  static void finalDrivePulse();
};

#endif
