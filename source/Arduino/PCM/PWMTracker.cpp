#include "PWMTracker.h"

PWMTracker PWMMonitoring::RPM;
PWMTracker PWMMonitoring::finalDrive;

void PWMMonitoring::RPMPulse() {
    long hold = millis();
    RPM.rate = 60000./(hold - RPM.lastPulse);
    RPM.lastPulse = hold;
}

void PWMMonitoring::finalDrivePulse() {
    long hold = millis();
    finalDrive.rate = 60000./(hold - finalDrive.lastPulse);
    finalDrive.lastPulse = hold;
}
