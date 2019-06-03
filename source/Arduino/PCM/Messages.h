#ifndef MESSAGES_H
#define MESSAGES_H

#include <Arduino.h>

struct Message;

struct RawMessage {
  unsigned short int id;
  unsigned short int length = 0;
  byte data[8];

  static RawMessage none();
};

struct Message {
  virtual RawMessage toRaw() const = 0;
};

struct ShiftMessage : Message {
  char dir;

  ShiftMessage() = default;
  explicit ShiftMessage(RawMessage);

  RawMessage toRaw() const override;
};

struct PEOne : Message {
  unsigned int rpm;
  float tps;
  float fuelOpenTime;
  float ignitionAngle;

  PEOne() = default;
  explicit PEOne(RawMessage);
  
  RawMessage toRaw() const override;
};

struct ErrorMessage : Message {
  String message;

  ErrorMessage() = default;
  ErrorMessage(String);
  explicit ErrorMessage(RawMessage);

  RawMessage toRaw() const override;
};

#endif
