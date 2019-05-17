#include "Error.h"
#include "CAN.h"
#include "LCD.h"
#include "LEDs.h"
#include "Log.h"
#include "Seg.h"

String Error::warningMessage = "";

void Error::fatalError(String message) {
  if (CAN::isActive()) {
    // send to CAN
  }
  if (LCD::isActive()) {
    LCD::write(message);
  }
  if (LEDs::areActive()) {
    LEDs::write(10000);
  }
  if (Log::isActive()) {
    Log::write(message);
  }
  if (Seg::isActive()) {
    while (true) {
      Seg::write(88888);
      Serial.println(message);
    }
  } else {
    while (true) {
      Serial.println(message);
    }
  }
}

void Error::warning(String message) {
  warningMessage = message;
}

void Error::stopWarning() {
  warningMessage = "";
}

void Error::warn() {
  if (CAN::isActive()) {
    // send to CAN
  }
  if (LCD::isActive()) {
    LCD::write(warningMessage);
    Serial.println(warningMessage);
  }
}

bool Error::isWarning() {
  return warningMessage.length();
}
