#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "SharedConstants.h"

// Labels for input pins
#define IN_TPS1 A0
#define IN_TPS2 A1
#define IN_APPS1 A2
#define IN_APPS2 A3
#define IN_BSE A4
#define IN_GEAR_INDICATOR 21
#define IN_FINAL_DRIVE 18
#define IN_RPM 3
#define IN_CLUTCH_BUTTON 49

// Labels for output pins
#define OUT_SHIFTUP_ACTUATOR 5
#define OUT_SHIFTDOWN_ACTUATOR 6
#define OUT_CLUTCH_ACTUATOR 7
#define OUT_THROTTLE 10
#define OUT_IGNITION_CUT 29
#define OUT_FUEL_CUT 30
#define OUT_THROTTLE_CUT 31
#define OUT_BRAKELIGHT 33


#define NO_THROTTLE 0
#define FULL_THROTTLE 1

// labels for plausibility timers
#define TIMER_APPS_DIFF 0
#define TIMER_TPS_DIFF 1
#define TIMER_BSE_DIFF 2
#define TIMER_BRAKETHROTTLE_DIFF 3
#define TIMER_EXPTPS_DIFF 4
#define TIMER_RESOLVE 5

// Constants for pulse widths and heights when shifting
#define PULSE_SHIFTUP_TIME 1000.
#define PULSE_SHIFTUP_AMPLITUDE 1.
#define PULSE_SHIFTDOWN_TIME 1000.
#define PULSE_SHIFTDOWN_AMPLITUDE 1.
#define PULSE_CLUTCHOUT_TIME 100.
#define PULSE_CLUTCHIN_TIME 100.
#define PULSE_CLUTCH_AMPLITUDE 1.

#define TOP_GEAR 6

// Shift sequence phases
#define SHIFT_IDLE 0
#define SHIFT_UP 1
#define SHIFT_DOWN 2

// Shift parameters
#define SHIFT_CLUTCH_MAX 4.
#define SHIFT_SHIFTER_MAX 4.
#define SHIFT_RAMPUP_LOWPASS 0.8
#define CLUTCH_RAMPUP_LOWPASS 0.8

#define FINAL_DRIVE_RATIO 1.4
#define RPM_RED_LINE 5000

#endif
