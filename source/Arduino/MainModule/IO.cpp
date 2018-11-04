#include "IO.h"
#include "Constants.h"
#include <Arduino.h>

bool IO::Initialize() {

  // This probably needs to be updated for new inputs and outputs

  pinMode(IN_SHIFTUP_PADDLE, INPUT);
  pinMode(IN_SHIFTDOWN_PADDLE, INPUT);
  pinMode(IN_RPM, INPUT);
  for(int i = 0; i < 4; i++)
    pinMode(IN_WHEEL_SPEED + i, INPUT);

  pinMode(OUT_SHIFTUP_ACTUATOR, OUTPUT);
  pinMode(OUT_SHIFTDOWN_ACTUATOR, OUTPUT);
  pinMode(OUT_CLUTCH_ACTUATOR, OUTPUT);
  pinMode(OUT_THROTTLE, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(IN_WHEEL_SPEED), InterruptMonitoring::WheelPulse0, RISING);
  attachInterrupt(digitalPinToInterrupt(IN_WHEEL_SPEED+1), InterruptMonitoring::WheelPulse1, RISING);
  attachInterrupt(digitalPinToInterrupt(IN_WHEEL_SPEED+2), InterruptMonitoring::WheelPulse2, RISING);
  attachInterrupt(digitalPinToInterrupt(IN_WHEEL_SPEED+3), InterruptMonitoring::WheelPulse3, RISING);
  attachInterrupt(digitalPinToInterrupt(IN_RPM), InterruptMonitoring::RPMPulse, RISING);

  return true; // will update this later to return false on failure
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
      return in;
}

void IO::SendOutputs(Output o) {
      // NEED TO DEAL WITH CUT VARIABLES. THEY ARE CURRENTLY BEING IGNORED
      analogWrite(OUT_THROTTLE, o.throttle);
      digitalWrite(OUT_SHIFTUP_ACTUATOR, o.shiftUp);
      digitalWrite(OUT_SHIFTDOWN_ACTUATOR, o.shiftDown);
      digitalWrite(OUT_CLUTCH_ACTUATOR, o.clutch);
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
