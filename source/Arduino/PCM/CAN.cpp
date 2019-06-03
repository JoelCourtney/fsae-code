#include "CAN.h"

#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>
#include <Arduino.h>

unsigned short int trim_id(unsigned short int id) {
  return id & 0b11111111111;
}

bool CAN::active = false;

void CAN::initialize() {
  if (Canbus.init(CANSPEED_500)) //Initialise MCP2515 CAN controller at the specified speed
    Serial.println("CAN Init ok");
  else {
    active = false;
  }
  active = true;
}

//void CAN::sendChar(char c, unsigned long id) {
//  tCAN message;
//  message.id = id; //formatted in HEX
//  message.header.rtr = 0;
//  message.header.length = 1; //formatted in DEC
//  message.data[0] = c;
//
//  mcp2515_bit_modify(CANCTRL, (1 << REQOP2) | (1 << REQOP1) | (1 << REQOP0), 0);
//  mcp2515_send_message(&message);
//}

void CAN::write(Message* m) {
  tCAN message;
  RawMessage rm = m->toRaw();
  message.id = trim_id(rm.id);
  message.header.rtr = 0;
  message.header.length = rm.length;
  for (int i = 0; i < rm.length; i++) {
    message.data[i] = rm.data[i];
  }

  mcp2515_bit_modify(CANCTRL, (1 << REQOP2) | (1 << REQOP1) | (1 << REQOP0), 0);
  mcp2515_send_message(&message);
}

RawMessage CAN::read() {
  tCAN message;
  if (mcp2515_check_message()) {
    if (mcp2515_get_message(&message)) {
      RawMessage rm;
      rm.id = trim_id(message.id);
      rm.length = message.header.length;
      for (int i = 0; i < rm.length; i++) {
        rm.data[i] = message.data[i];
      }
      return rm;
    }
  }
  return RawMessage::none();
}

bool CAN::isActive() {
  return active;
}
