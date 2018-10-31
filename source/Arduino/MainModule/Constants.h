#ifndef CONSTANTS_H
#define CONSTANTS_H

// Labels for input pins
#define IN_TPS1 A0
#define IN_TPS2 A1
#define IN_APPS1 A2
#define IN_APPS2 A3
#define IN_BSE1 A4
#define IN_BSE2 A5
#define IN_PADDLEUP 0
#define IN_PADDLEDOWN 1
#define IN_WHEELSPEED 18
#define IN_RPM 6

// Required time at low (in ms) before accepting a second shift request
#define PADDLE_DEAD_TIME 100

// Labels for output pins
#define OUT_SHIFTUP 2
#define OUT_SHIFTDOWN 3
#define OUT_CLUTCH 4
#define OUT_THROTTLE A6

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

#define TOP_GEAR 4

// Shift sequence phases
#define SHIFT_IDLE 0
#define SHIFT_CLUTCH_RAMPUP 1
#define SHIFT_SHIFTER_RAMPUP 2
#define SHIFT_SHIFTER_RAMPDOWN 3
#define SHIFT_CLUTCH_RAMPDOWN 4

#define FINAL_DRIVE_RATIO 1.4
#define RPM_RED_LINE 5000

#endif
