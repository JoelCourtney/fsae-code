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
LiquidCrystal IO::lcd = LiquidCrystal(LCD_RS, LCD_RW, LCD_EN, LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

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

  if (Canbus.init(CANSPEED_500)) //Initialise MCP2515 CAN controller at the specified speed
    Serial.println("CAN Init ok");
  else
    Serial.println("Can't init CAN");

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
  //  lcd.print("RPM:" + String(rpm) + " OPRS:" + pressure);
  lcd.setCursor(0, 1);

  if (o.shiftUp || true) {
    SendCANChar('u', 0x0b000002);
  }
  if (o.shiftDown) {
    SendCANChar('d', 0x0b000000);
  }

  plexIndex = (plexIndex + 1) % 4;
  digitalWrite(SEG_P0, LOW);
  digitalWrite(SEG_P1, LOW);
  digitalWrite(SEG_P2, LOW);
  digitalWrite(SEG_P3, LOW);

  int mod = 10;
  for (int i = 0; i < plexIndex; i++) {
    mod *= 10;
  }
  unsigned digit = o.seg % mod / (mod / 10);
  digitalWrite(SEG_A, digit & 1);
  digitalWrite(SEG_B, digit & 2);
  digitalWrite(SEG_C, digit & 4);
  digitalWrite(SEG_D, digit & 8);


  switch (plexIndex) {
    case 0:
      digitalWrite(SEG_P0, HIGH);
      break;
    case 1:
      digitalWrite(SEG_P1, HIGH);
      break;
    case 2:
      digitalWrite(SEG_P2, HIGH);
      break;
    case 3:
      digitalWrite(SEG_P3, HIGH);
      break;
  }
}

void IO::SendCANChar(char c, unsigned long id) {
  tCAN message;
  message.id = id; //formatted in HEX
  message.header.rtr = 0;
  message.header.length = 1; //formatted in DEC
  message.data[0] = c;

  mcp2515_bit_modify(CANCTRL, (1 << REQOP2) | (1 << REQOP1) | (1 << REQOP0), 0);
  mcp2515_send_message(&message);
}
