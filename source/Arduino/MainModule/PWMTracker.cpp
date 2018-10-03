#include "InterruptTracker.h"

InterruptTracker InterruptMonitoring::RPM;
InterruptTracker InterruptMonitoring::wheelSpeed[];

void InterruptMonitoring::RPMPulse() {
    long hold = millis();
    RPM.rate = 1000/(hold - RPM.lastPulse);
    RPM.lastPulse = hold;
}

void InterruptMonitoring::WheelPulse0() {
    long hold = millis();
    wheelSpeed[0].rate = 1000/(hold - wheelSpeed[0].lastPulse);
    wheelSpeed[0].lastPulse = hold;
}

void InterruptMonitoring::WheelPulse1() {
    long hold = millis();
    wheelSpeed[1].rate = 1000/(hold - wheelSpeed[1].lastPulse);
    wheelSpeed[1].lastPulse = hold;
}
void InterruptMonitoring::WheelPulse2() {
    long hold = millis();
    wheelSpeed[2].rate = 1000/(hold - wheelSpeed[2].lastPulse);
    wheelSpeed[2].lastPulse = hold;
}

void InterruptMonitoring::WheelPulse3() {
    long hold = millis();
    wheelSpeed[3].rate = 1000/(hold - wheelSpeed[3].lastPulse);
    wheelSpeed[3].lastPulse = hold;
}
