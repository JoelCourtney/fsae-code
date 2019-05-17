#include "Messages.h"

RPM_TPS::RPM_TPS(RawMessage m) {
  rpm = m.data[1] * 256 + m.data[0];
  
  int tpsHold = m.data[3] * 256 + m.data[2];
  if (tpsHold > 32767)
    tpsHold -= 65536;
  tps = tpsHold * 0.1;

  int fuelOpenTimeHold = m.data[5] * 256 + m.data[4];
  if (fuelOpenTimeHold > 32767)
    fuelOpenTimeHold -= 65536;
  fuelOpenTime = fuelOpenTimeHold * 0.1;

  int ignitionAngleHold = m.data[7] * 256 + m.data[6];
  if (ignitionAngleHold > 32767)
    ignitionAngleHold -= 65536;
  ignitionAngle = ignitionAngleHold * 0.1;
}

RawMessage RPM_TPS::toRaw() const {
  // This will never be called.
  return RawMessage();
}
