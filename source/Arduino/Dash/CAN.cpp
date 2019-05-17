#include "CAN.h"
#include "Error.h"

#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>
#include <Arduino.h>

bool CAN::active = false;

void CAN::initialize() {
  if (Canbus.init(CANSPEED_500)) //Initialise MCP2515 CAN controller at the specified speed
    Serial.println("CAN Init ok");
  else {
    Error::fatalError("Can't init CAN");
  }
  active = true;
}

void CAN::sendChar(char c, unsigned long id) {
  tCAN message;
  message.id = id; //formatted in HEX
  message.header.rtr = 0;
  message.header.length = 1; //formatted in DEC
  message.data[0] = c;

  mcp2515_bit_modify(CANCTRL, (1 << REQOP2) | (1 << REQOP1) | (1 << REQOP0), 0);
  mcp2515_send_message(&message);
}

bool CAN::isActive() {
  return active;
}
