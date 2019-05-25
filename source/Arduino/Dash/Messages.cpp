#include "Messages.h"

float signedBytesToFloat(byte low, byte high, float res) {
  int hold = high*256 + low;
  if (hold > 32767)
    hold -= 65536;
  return hold * res;
}

unsigned int bytesToInt(byte low, byte high) {
  return high*256 + low;
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

unsigned long int PEOne::getID() const {
  return 0x0cfff048;
}

ShiftMessage::ShiftMessage(RawMessage m) {
  dir = m.data[0];
}

RawMessage ShiftMessage::toRaw() const {
  RawMessage m;
  m.id = 0xb0001000;
  m.data[0] = dir;
  return m;
}
