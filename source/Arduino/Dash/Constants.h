#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "SharedConstants.h"

// Pins for LCD screen
#define LCD_RS 7
#define LCD_RW 8
#define LCD_EN 43
#define LCD_D0 44
#define LCD_D1 45
#define LCD_D2 46
#define LCD_D3 16
#define LCD_D4 17
#define LCD_D5 18
#define LCD_D6 19
#define LCD_D7 20
#define LCD_COLS 16
#define LCD_ROWS 2

// Pins for 7Seg
#define OUT_DECODER_A 15
#define OUT_DECODER_B 14
#define OUT_DECODER_C 0
#define OUT_DECODER_D 1
#define OUT_DIGIT_1 3
#define OUT_DIGIT_2 4
#define OUT_DIGIT_3 5
#define OUT_DIGIT_4 6
#define OUT_DIGIT_5 21

// Input pins
#define IN_SHIFTUP_PADDLE 8
#define IN_SHIFTDOWN_PADDLE 9

// Required time at low (in ms) before accepting a second shift request
#define PADDLE_DEAD_TIME 100

// LED Shift lights
#define LED_LATCH 49
#define LED_CLOCK 47
#define LED_DATA 48

#define SPI_SCK 52
#define SPI_MISO 50
#define SPI_MOSI 51
#define SPI_CAN_CS 53
#define SPI_SD_CS 9

#endif
