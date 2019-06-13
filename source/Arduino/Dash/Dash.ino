#include "Constants.h"
#include "CAN.h"
#include "LCD.h"
#include "LEDs.h"
#include "Log.h"
#include "Paddles.h"
#include "Seg.h"
#include "Messages.h"
#include "Error.h"
#include <avr/wdt.h>

int hold = 900;

bool up = false;
bool down = false;
unsigned int rpm = 30001;
int tps = -1; 
short int gear = -2;

void setup() {
  wdt_disable();
//  Serial.begin(115200);
//  Serial.println("Hello. Am Dash.");
  LCD::initialize(); 
  LEDs::initialize();
  Seg::initialize();
//  CAN::initialize();
//  Log::initialize();
//  Paddles::initialize();
}

void loop() {
//  // Read CAN messages
//  RawMessage rm = CAN::read();
//  parseCAN(rm);
//  
//  // Read paddles and send shift messages
//  up = Paddles::readUp();
//  down = Paddles::readDown();
//  if (up) {
//    ShiftMessage m;
//    m.dir = 'u';
//    CAN::write(&m);
//  }
//  if (down) {
//    ShiftMessage m;
//    m.dir = 'd';
//    CAN::write(&m);
//  }

  LEDs::write(1000);

//  Seg::write(rpm*10+gear);
Seg::write(33333);

//  if (Error::isWarning()) {
//    Error::warn();
//  } else {
      LCD::write("hello world");
//  }
}

void parseCAN(RawMessage rm) {
  switch (rm.id) {
    case CAN_PE1_ID: {
      PEOne m(rm);
      rpm = m.rpm;
      tps = m.tps;
    }
  }
}
