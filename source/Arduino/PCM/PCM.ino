#include "CAN.h"
#include "Clutch.h"
#include "Shifter.h"
#include "Failsafe.h"
#include "Pedals.h"
#include "Throttle.h"
#include "APPSTPSMap.h"
#include "Constants.h"

unsigned int rpm = 0;

void setup() {
  Failsafe::setDogEnable(false);
  CAN::initialize();
  Pedals::initialize();
  Shifter::initialize();
  Clutch::initialize();
  Throttle::initialize();
  Failsafe::initialize();
}

void loop() {
  // Plausibility checks
  Pedals::update();
  Throttle::update();

  // Read CAN messages
  RawMessage rm = CAN::read();
  parseCAN(rm);
  
  Failsafe::update();

  Shifter::update();
  Clutch::update();
  
  if (Failsafe::isSafe()) {
    float apps = Pedals::readAPPS();
    float throttle = APPSTPSMap::Map(apps);
    Throttle::write(throttle);
  }
}

void parseCAN(RawMessage rm) {
  switch (rm.id) {
    case CAN_PE1_ID: {
      PEOne m(rm);
      rpm = m.rpm;
    }
    case CAN_SHIFT_ID: {
      ShiftMessage m(rm);
      if (m.dir == 'u') {
        Shifter::shiftUp();
      } else if (m.dir == 'd') {
        Shifter::shiftDown();
      } else {
        ErrorMessage em("badshift");
        CAN::write(&em);
      }
    }
  }
}
