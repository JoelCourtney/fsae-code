#ifndef MESSAGES_H
#define MESSAGES_H

#include <Arduino.h>

struct RawMessage {
  unsigned long int id;
  unsigned short int len = 0;
  byte data[8];
};

struct Message {
  virtual RawMessage toRaw() const = 0;
  virtual unsigned long int getID() const = 0;
};

struct ShiftMessage : Message {
  char dir;

  ShiftMessage() = default;
  explicit ShiftMessage(RawMessage);

  RawMessage toRaw() const override;
  unsigned long int getID() const override;
};

struct PEOne : Message {
  unsigned int rpm;
  float tps;
  float fuelOpenTime;
  float ignitionAngle;

  PEOne() = default;
  explicit PEOne(RawMessage);
  
  RawMessage toRaw() const override;
  unsigned long int getID() const override;
};

#endif
