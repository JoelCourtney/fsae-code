#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "SharedConstants.h"

// Pins for LCD screen
#define LCD_RS 32
#define LCD_RW 33
#define LCD_EN 31
#define LCD_D0 22
#define LCD_D1 23
#define LCD_D2 24
#define LCD_D3 25
#define LCD_D4 26
#define LCD_D5 27
#define LCD_D6 28
#define LCD_D7 29
#define LCD_COLS 16
#define LCD_ROWS 2

// Pins for 7Seg
#define SEG_A 41
#define SEG_B 43
#define SEG_C 45
#define SEG_D 47
#define SEG_P0 40
#define SEG_P1 42
#define SEG_P2 44
#define SEG_P3 46
#define SEG_P4 47

// Input pins
#define IN_SHIFTUP_PADDLE 8
#define IN_SHIFTDOWN_PADDLE 9

// Required time at low (in ms) before accepting a second shift request
#define PADDLE_DEAD_TIME 100

// LED Shift lights
#define LED_LATCH 30
#define LED_CLOCK 31
#define LED_DATA 32

#define SPI_SCK 52
#define SPI_MISO 50
#define SPI_MOSI 51
#define SPI_CAN_CS 53
#define SPI_SD_CS 9

#endif
