#pragma once
#include <Arduino.h>

struct PWMTracker {
      long int lastPulse = millis();
      double rate;
};

struct PWMMonitoring {
  static PWMTracker RPM;
  static PWMTracker wheelSpeed[4];

  static void RPMPulse() {
    long hold = millis();
    RPM.rate = 1000/(hold - RPM.lastPulse);
    RPM.lastPulse = hold;
  }

  static void WheelPulse0() {
    long hold = millis();
    wheelSpeed[0].rate = 1000/(hold - wheelSpeed[0].lastPulse);
    wheelSpeed[0].lastPulse = hold;
  }
  static void WheelPulse1() {
    long hold = millis();
    wheelSpeed[1].rate = 1000/(hold - wheelSpeed[1].lastPulse);
    wheelSpeed[1].lastPulse = hold;
  }
  static void WheelPulse2() {
    long hold = millis();
    wheelSpeed[2].rate = 1000/(hold - wheelSpeed[2].lastPulse);
    wheelSpeed[2].lastPulse = hold;
  }
  static void WheelPulse3() {
    long hold = millis();
    wheelSpeed[3].rate = 1000/(hold - wheelSpeed[3].lastPulse);
    wheelSpeed[3].lastPulse = hold;
  }
};

PWMTracker PWMMonitoring::RPM;

