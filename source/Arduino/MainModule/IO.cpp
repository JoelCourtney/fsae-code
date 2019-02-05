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

int IO::Initialize() {
  pinMode(IN_SHIFTUP_PADDLE, INPUT);
  pinMode(IN_SHIFTDOWN_PADDLE, INPUT);
  pinMode(IN_RPM, INPUT);
  for(int i = 0; i < 4; i++)
    pinMode(IN_WHEEL_SPEED + i, INPUT);
  for(int i = 0; i < 6; i++)
    pinMode(IN_GEAR_INDICATOR + i, INPUT);

  pinMode(OUT_SHIFTUP_ACTUATOR, OUTPUT);
  pinMode(OUT_SHIFTDOWN_ACTUATOR, OUTPUT);
  pinMode(OUT_CLUTCH_ACTUATOR, OUTPUT);
  pinMode(OUT_THROTTLE, OUTPUT);
  pinMode(OUT_IGNITION_CUT, OUTPUT);
  pinMode(OUT_FUEL_CUT, OUTPUT);
  pinMode(OUT_THROTTLE_CUT, OUTPUT);
  pinMode(OUT_BRAKELIGHT, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(IN_WHEEL_SPEED), PWMMonitoring::WheelPulse0, RISING);
  attachInterrupt(digitalPinToInterrupt(IN_WHEEL_SPEED+1), PWMMonitoring::WheelPulse1, RISING);
  attachInterrupt(digitalPinToInterrupt(IN_WHEEL_SPEED+2), PWMMonitoring::WheelPulse2, RISING);
  attachInterrupt(digitalPinToInterrupt(IN_WHEEL_SPEED+3), PWMMonitoring::WheelPulse3, RISING);
  attachInterrupt(digitalPinToInterrupt(IN_RPM), PWMMonitoring::RPMPulse, RISING);

  if (CAN.begin(CAN_250KBPS) != CAN_OK) return ERROR_CAN_INITIALIZATION;
  attachInterrupt(digitalPinToInterrupt(COM_INT), IO::CAN_ISR, FALLING); // start interrupt
  if (!SD.begin(COM_SD_CS)) return ERROR_SD_INITIALIZATION;

  unsigned int logNumber = 0;
  while (logNumber <= 9999) {
    sprintf(logName, "log%04d.csv", logNumber++);
    if (!SD.exists(logName)) {
      break;
    }
  }
  if (logNumber > 9999) return ERROR_LOG_FILE_NAME_SATURATION;
  File logFile = SD.open(logName, FILE_WRITE);
  logFile.println("time,ERROR,APPS,TPS,BSE,wheelSpeed,gear,coolantTemp,intakeTemp,ambientTemp,oilTemp,exhaustTemp,oilPressure,O2,MAF,MAP,knock,fuelPressure");
  logFile.close();

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

      bool up = digitalRead(IN_SHIFTUP_PADDLE);
      bool down = digitalRead(IN_SHIFTDOWN_PADDLE);
      in.paddleUp = false;
      in.paddleDown = false;
      if (up) {
        int diff =  millis() - lastPaddleUpHigh;
        lastPaddleUpHigh = millis();
        if (diff > PADDLE_DEAD_TIME) {
          in.paddleUp = true;
        }
      }
      if (down) {
        int diff =  millis() - lastPaddleDownHigh;
        lastPaddleDownHigh = millis();
        if (diff > PADDLE_DEAD_TIME) {
          in.paddleDown = true;
        }
      }
      if (canReceived) {
        
      }
      // NEED TO READ GEAR INDICATOR
      return in;
}

void IO::SendOutputs(Output o) {
      // NEED TO DEAL WITH CUT VARIABLES. THEY ARE CURRENTLY BEING IGNORED
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
}
