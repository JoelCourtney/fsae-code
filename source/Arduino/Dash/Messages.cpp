#include "Messages.h"
#include "Constants.h"

float signedBytesToFloat(byte low, byte high, float res) {
  int hold = high*256 + low;
  if (hold > 32767)
    hold -= 65536;
  return hold * res;
}

unsigned int bytesToInt(byte low, byte high) {
  return high*256 + low;
}

RawMessage RawMessage::none() {
  RawMessage rm;
  rm.id = 0;
  return rm;
}

PEOne::PEOne(RawMessage m) {
  rpm = bytesToInt(m.data[0], m.data[1]);
  
  tps = signedBytesToFloat(m.data[2], m.data[3], 0.1);
  
  fuelOpenTime = signedBytesToFloat(m.data[4], m.data[5], 0.1);

  ignitionAngle = signedBytesToFloat(m.data[6], m.data[7], 0.1);
}

RawMessage PEOne::toRaw() const {
  // This will never be called.
  return RawMessage();
}

ShiftMessage::ShiftMessage(RawMessage m) {
  dir = m.data[0];
}

RawMessage ShiftMessage::toRaw() const {
  RawMessage m;
  m.id = CAN_SHIFT_ID;
  m.data[0] = dir;
  m.length = 1;
  return m;
}
