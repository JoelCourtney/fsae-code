#include "IO.h"
#include "Constants.h"
#include <Arduino.h>
#include <math.h>

#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>

int IO::plexIndex = 0;
unsigned long IO::lastPaddleUpHigh = 0;
unsigned long IO::lastPaddleDownHigh = 0;
unsigned long IO::lastLog = 0;
char IO::logName[12];

void printDirectory(File dir, int numTabs);
void clearDirectory(File dir);

int IO::Initialize() {

//  lcd.begin(LCD_COLS, LCD_ROWS);
  delay(100);

  Serial.begin(9600);
  Serial.println("Hello. Am Dash.");

//  pinMode(SEG_A, OUTPUT);
//  pinMode(SEG_B, OUTPUT);
//  pinMode(SEG_C, OUTPUT);
//  pinMode(SEG_D, OUTPUT);
//  pinMode(SEG_P0, OUTPUT);
//  pinMode(SEG_P1, OUTPUT);
//  pinMode(SEG_P2, OUTPUT);
//  pinMode(SEG_P3, OUTPUT);

  return 0;
}

Input IO::ReadInputs() {
  Input in;

  bool up = digitalRead(IN_SHIFTUP_PADDLE);
  bool down = digitalRead(IN_SHIFTDOWN_PADDLE);
  in.paddleUp = false;
  in.paddleDown = false;
  if (up) {
    int diff =  millis() - lastPaddleUpHigh;
    //        Serial.println(diff);
    lastPaddleUpHigh = millis();
    if (diff > PADDLE_DEAD_TIME) {
      in.paddleUp = true;
    }
  }
  if (down) {
    int diff =  millis() - lastPaddleDownHigh;
    lastPaddleDownHigh = millis();
    if (diff > PADDLE_DEAD_TIME) {
      in.paddleDown = true;
    }
  }
  return in;
}

void IO::SendOutputs(Output o) {
  lcd.setCursor(0, 0);
  String rpm = String(((double)round(o.RPM / 100)) / 10);
  rpm.remove(rpm.length() - 1, 1);
  String pressure = String(round(o.oilPressure));
  //  
  lcd.setCursor(0, 1);

  if (o.shiftUp || true) {
    SendCANChar('u', 0x0b000002);
    Serial.println("why");
  }
  if (o.shiftDown) {
    SendCANChar('d', 0x0b000000);
  }

  
 /*
  * unsigned int masks[] = {
  0b1,
  0b10,
  0b100,
  0b1000,
  0b100000000000,
  0b10000000000,
  0b1000000000,
  0b100000000,
  0b10010000,
  0b1100000
};
  * In setup:
  * pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  Here:
  *   // count from 0 to 255 and display the number 
  // on the LEDs
  unsigned int n = 0;
  unsigned int mask = 0b11111111;
  while (true) {
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    unsigned int numberToDisplay = 0;
    for (unsigned short int i = 0; i < n; i++) {
      numberToDisplay |= masks[i];
    }
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay >> 8);
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay & mask);  
     
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    Serial.println(numberToDisplay);
    // pause before next value:
    delay(500);
    if (n >= 10) {
      n = 0;
    } else {
      n += 1;
    }
  }
  */
}
