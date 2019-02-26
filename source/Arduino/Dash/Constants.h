#ifndef CONSTANTS_H
#define CONSTANTS_H

// Pins for LCD screen
#define LCD_RS 12
#define LCD_EN 11
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 2
#define LCD_COLS 16
#define LCD_ROWS 2

// Labels for communication pins
#define COM_MISO 50
#define COM_MOSI 51
#define COM_SCK 52
#define COM_INT 2
#define COM_CAN_CS 53
#define COM_SD_CS 4

// Error codes
#define ERROR_CAN_INITIALIZATION 1
#define ERROR_SD_INITIALIZATION 2
#define ERROR_LOG_FILE_NAME_SATURATION 3
#define ERROR_NO_GEAR_DETECTED 4

// Input pins
#define IN_SHIFTUP_PADDLE 8
#define IN_SHIFTDOWN_PADDLE 9

#endif
