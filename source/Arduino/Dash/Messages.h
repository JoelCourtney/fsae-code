#ifndef MESSAGES_H
#define MESSAGES_H

#include <Arduino.h>

struct RawMessage {
  byte data[8];
};

struct Message {
  virtual RawMessage toRaw() const = 0;
};

struct RPM_TPS : Message {
  unsigned int rpm;
  float tps;
  float fuelOpenTime;
  float ignitionAngle;

  RPM_TPS() = default;
  explicit RPM_TPS(RawMessage);
  
  RawMessage toRaw() const override;
};

#endif
