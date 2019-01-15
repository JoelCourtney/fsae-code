#ifndef CONSTANTS_H
#define CONSTANTS_H

// Labels for input pins
#define IN_TPS1 A0
#define IN_TPS2 A1
#define IN_APPS1 A2
#define IN_APPS2 A3
#define IN_BSE1 A4
#define IN_BSE2 A5
#define IN_SHIFTUP_PADDLE 8
#define IN_SHIFTDOWN_PADDLE 9
#define IN_GEAR_INDICATOR 22
#define IN_WHEEL_SPEED 18
#define IN_RPM 3

// Labels for output pins
#define OUT_SHIFTUP_ACTUATOR 5
#define OUT_SHIFTDOWN_ACTUATOR 6
#define OUT_CLUTCH_ACTUATOR 7
#define OUT_THROTTLE 10
#define OUT_IGNITION_CUT 29
#define OUT_FUEL_CUT 30
#define OUT_THROTTLE_CUT 31
#define OUT_BRAKELIGHT 33

// Labels for communication pins
#define COM_MISO 50
#define COM_MOSI 51
#define COM_SCK 52
#define COM_INT 2
#define COM_CAN_CS 53
#define COM_SD_CS 4

// Required time at low (in ms) before accepting a second shift request
#define PADDLE_DEAD_TIME 100

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

// Error codes
#define ERROR_CAN_INITIALIZATION 1
#define ERROR_SD_INITIALIZATION 2
#define ERROR_LOG_FILE_NAME_SATURATION 3
#define ERROR_

#endif
