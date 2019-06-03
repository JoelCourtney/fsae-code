// Constants shared between PCM and Dash

#ifndef SHAREDCONSTANTS_H
#define SHAREDCONSTANTS_H

// Error Codes
#define ERROR_CAN_INITIALIZATION 1
#define ERROR_SD_INITIALIZATION 2
#define ERROR_LOG_FILE_NAME_SATURATION 3
#define ERROR_NO_GEAR_DETECTED 4

// Labels for communication pins
#define COM_MISO 50
#define COM_MOSI 51
#define COM_SCK 52
#define COM_INT 2
#define COM_CAN_CS 53
#define COM_SD_CS 4

// CAN IDs
#define CAN_SHIFT_ID 0xb0001000&0b11111111111
#define CAN_PE1_ID 0x0CFFF048&0b11111111111
#define CAN_ERROR_ID 0xa0000100&0b11111111111

#endif
