#include "Constants.h"
#include "CAN.h"
#include "LCD.h"
#include "LEDs.h"
#include "Log.h"
#include "Paddles.h"
#include "Seg.h"

int hold = 900;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello. Am Dash.");
  LCD::initialize(); 
  LEDs::initialize();
  Seg::initialize();
  CAN::initialize();
  Log::initialize();
  Paddles::initialize();
}

void loop() {
  
}
