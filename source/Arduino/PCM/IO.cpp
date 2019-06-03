#include "IO.h"
#include "Constants.h"
#include <Arduino.h>
#include <mcp_can.h>

unsigned long IO::lastPaddleUpHigh = 0;
unsigned long IO::lastPaddleDownHigh = 0;
unsigned long IO::lastLog = 0;
char IO::logName[12];
bool IO::canReceived = false;
PassThrough IO::pass;

MCP_CAN CAN(COM_CAN_CS);

void printDirectory(File dir, int numTabs);
void clearDirectory(File dir);

int IO::Initialize() {
  pinMode(IN_RPM, INPUT_PULLUP);
  pinMode(IN_FINAL_DRIVE, INPUT_PULLUP);
  for(int i = 1; i <= 6; i++)
    pinMode(IN_GEAR_INDICATOR + i, INPUT_PULLUP);
  pinMode(IN_CLUTCH_BUTTON, INPUT_PULLUP);

  pinMode(OUT_SHIFTUP_ACTUATOR, OUTPUT);
  pinMode(OUT_SHIFTDOWN_ACTUATOR, OUTPUT);
  pinMode(OUT_CLUTCH_ACTUATOR, OUTPUT);
  pinMode(OUT_THROTTLE, OUTPUT);
  pinMode(OUT_IGNITION_CUT, OUTPUT);
  pinMode(OUT_FUEL_CUT, OUTPUT);
  pinMode(OUT_THROTTLE_CUT, OUTPUT);
  pinMode(OUT_BRAKELIGHT, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(IN_FINAL_DRIVE), PWMMonitoring::finalDrivePulse, RISING);
  attachInterrupt(digitalPinToInterrupt(IN_RPM), PWMMonitoring::RPMPulse, RISING);

//  if (CAN.begin(CAN_1000KBPS) != CAN_OK) return ERROR_CAN_INITIALIZATION;
  attachInterrupt(digitalPinToInterrupt(COM_INT), IO::CAN_ISR, FALLING); // start interrupt
//  if (!SD.begin(COM_SD_CS)) return ERROR_SD_INITIALIZATION;
//
//  unsigned int logNumber = 0;
//  while (logNumber <= 9999) {
//    sprintf(logName, "log%04d.csv", logNumber++);
//    if (!SD.exists(logName)) {
//      break;
//    }
//  }
//  if (logNumber > 9999) return ERROR_LOG_FILE_NAME_SATURATION;
//  File logFile = SD.open(logName, FILE_WRITE);
//  logFile.println("time,ERROR,APPS,TPS,BSE,wheelSpeed,gear,coolantTemp,intakeTemp,ambientTemp,oilTemp,exhaustTemp,oilPressure,O2,MAF,MAP,knock,fuelPressure");
//  logFile.close();

  Serial.begin(115200);
  Serial.println("why");

  return 0;
}

void IO::CAN_ISR() {
  canReceived = true;
  // check CAN ID
  // use /Powertrain/'External Resources'/PE3_AN400_CAN_Protocol_C.pdf
  // to partially update pass.
}

Input IO::ReadInputs() {
      Input in;
      in.TPS1 = analogRead(IN_TPS1);
      in.TPS2 = analogRead(IN_TPS2);
      in.APPS1 = analogRead(IN_APPS1);
      in.APPS2 = analogRead(IN_APPS2);
      in.BSE1 = analogRead(IN_BSE1);
      in.BSE2 = analogRead(IN_BSE2);
      in.clutchButton = !digitalRead(IN_CLUTCH_BUTTON);

      
      if (canReceived) {
        canReceived = false;
        unsigned char buf[16];
        unsigned char len;
        unsigned long id;
        while (CAN_MSGAVAIL == CAN.checkReceive()) 
        {
          CAN.readMsgBufID(&id, &len, buf);
          switch (id) {
            case 0x0b000000: {
              Serial.println("shift received");
              if (buf[0] == 'u') {
                in.paddleUp = true;
              } else if(buf[0] == 'd') {
                in.paddleDown = true;
              }
            }
          }
        }
      }
      if (Serial.available()) {
        String command = Serial.readString();
        if (command.equals("status")) {
          Serial.println("helloo");
        } else if (command.equals("ls")) {
          File root = SD.open("/");
          printDirectory(root, 0);
        } else if (command.indexOf("dump") == 0) {
          String file;
          char buf[17];
          command.toCharArray(buf,17);
          sscanf(buf, "dump %s", file);
          File logFile = SD.open(file);
          while (logFile.available()) {
            Serial.write(logFile.read());
          }
          logFile.close();
        } else if (command.equals("rm *")) {
          File root = SD.open("/");
          clearDirectory(root);
        } else if (command.indexOf("rm") == 0) {
          String file;
          char buf[15];
          command.toCharArray(buf,15);
          sscanf(buf, "dump %s", file);
          SD.remove(file);
        }
      }
      
      if (in.gear == -1) {
        // something about error ERROR_NO_GEAR_DETECTED
      }
      in.finalDrive = PWMMonitoring::finalDrive;
      return in;
}

void IO::SendOutputs(Output o) {
  analogWrite(OUT_THROTTLE, o.throttle);
  digitalWrite(OUT_SHIFTUP_ACTUATOR, o.shiftUp);
  digitalWrite(OUT_SHIFTDOWN_ACTUATOR, o.shiftDown);
  digitalWrite(OUT_CLUTCH_ACTUATOR, o.clutch);

  digitalWrite(OUT_IGNITION_CUT, o.ignitionCut);
  digitalWrite(OUT_FUEL_CUT, o.fuelCut);
  digitalWrite(OUT_THROTTLE_CUT, o.throttleCut);

  digitalWrite(OUT_BRAKELIGHT, o.brakelight);

  if (millis()-lastLog > 250) {
    File logFile = SD.open(logName, FILE_WRITE);
    logFile.println("stuffs");
    logFile.close();
    lastLog = millis();
  }
}

double Input::TPSAve() {
  return (TPS1 + TPS2) / 2;
}

double Input::APPSAve() {
  return (APPS1 + APPS2) / 2;
}

double Input::BSEAve() {
  return (BSE1 + BSE2) / 2;
}

double Input::wsAve() {
  return (TPS1 + TPS2) / 2; // this is a standin. Will average the wheel speed sensors
  // We might not have wheelSpeed at all, so this is just placeholder
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void clearDirectory(File dir) {
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    String name = entry.name();
    entry.close();
    SD.remove(name);
  }
}

void IO::SendCANChar(char c, unsigned long id) {
  CAN.sendMsgBuf(id, 0, 1, &c);
}
