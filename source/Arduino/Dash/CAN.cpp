#include "CAN.h"

#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>
#include <Arduino.h>

void CAN::Initialize() {
  if (Canbus.init(CANSPEED_500)) //Initialise MCP2515 CAN controller at the specified speed
    Serial.println("CAN Init ok");
  else
    Serial.println("Can't init CAN");
}

void CAN::SendChar(char c, unsigned long id) {
  tCAN message;
  message.id = id; //formatted in HEX
  message.header.rtr = 0;
  message.header.length = 1; //formatted in DEC
  message.data[0] = c;

  mcp2515_bit_modify(CANCTRL, (1 << REQOP2) | (1 << REQOP1) | (1 << REQOP0), 0);
  mcp2515_send_message(&message);
}
