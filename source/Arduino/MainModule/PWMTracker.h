#pragma once
#include <Arduino.h>

struct PWMTracker {
      long int lastPulse = millis();
      double rate;
};

struct PWMMonitoring {
  static PWMTracker RPM;
  static PWMTracker wheelSpeed[4];

  static void RPMPulse();

  static void WheelPulse0();
  static void WheelPulse1();
  static void WheelPulse2();
  static void WheelPulse3();
};
