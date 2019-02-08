#include "IO.h"
#include "Constants.h"
#include <Arduino.h>
#include <mcp_can.h>

unsigned long IO::lastPaddleUpHigh = 0;
unsigned long IO::lastPaddleDownHigh = 0;
unsigned long IO::lastLog = 0;
char IO::logName[12];
bool IO::canReceived = false;

MCP_CAN CAN(COM_CAN_CS);

void printDirectory(File dir, int numTabs);
void clearDirectory(File dir);

int IO::Initialize() {

  if (CAN.begin(CAN_1000KBPS) != CAN_OK) return ERROR_CAN_INITIALIZATION;
  attachInterrupt(digitalPinToInterrupt(COM_INT), IO::CAN_ISR, FALLING); // start interrupt
  if (!SD.begin(COM_SD_CS)) return ERROR_SD_INITIALIZATION;

  Serial.begin(9600);

  return 0;
}

void IO::CAN_ISR() {
  canReceived = true;
  // check CAN ID
  // use /Powertrain/'External Resources'/PE3_AN400_CAN_Protocol_C.pdf
  // to partially update pass.
}

Input IO::ReadInputs() {
      if (canReceived) {
        
      }
}

void IO::SendOutputs(Output o) {
  
}
