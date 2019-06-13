#include "Log.h"
#include "Constants.h"
#include "Error.h"
#include <SD.h>

String Log::fileName = "";
bool Log::active = false;

void Log::initialize() {
  if (!SD.begin(SPI_SD_CS)) {
    Error::fatalError("Cant init SD");
  }
  for (unsigned int tag = 0; tag < 1000; tag++) {
    String nameHold = String(tag) + ".csv";
    unsigned int zeros = 8 - nameHold.length();
    while (zeros --> 0) {
      nameHold = "0" + nameHold;
    }
    nameHold = "log" + nameHold;
    if (!SD.exists(nameHold)) {
      fileName = nameHold;
      break;
    }
  }
  File file = SD.open(fileName, FILE_WRITE);
  if (file) {
    String header = "header";
    file.println(header);
    file.close();
//    Serial.println(header);
    active = true;
  } else {
    Error::fatalError("Cant open log file");
  }
}

void Log::write(String data) {
  File file = SD.open(fileName, FILE_WRITE);
  if (file) {
    file.println(data);
    file.close();
//    Serial.println(data);
  } else {
    Error::warning("Cant open log file");
  }
}

bool Log::isActive() {
  return active;
}
