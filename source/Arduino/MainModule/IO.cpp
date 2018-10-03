#include "IO.h"
#include "Constants.h"
#include <Arduino.h>

bool IO::Initialize() {

  // This probably needs to be updated for new inputs and outputs

  pinMode(IN_PADDLEUP, INPUT);
  pinMode(IN_PADDLEDOWN, INPUT);
  pinMode(IN_RPM, INPUT);
  for(int i = 0; i < 4; i++)
    pinMode(IN_WHEELSPEED + i, INPUT);

  pinMode(OUT_SHIFTUP, OUTPUT);
  pinMode(OUT_SHIFTDOWN, OUTPUT);
  pinMode(OUT_CLUTCH, OUTPUT);
  pinMode(OUT_THROTTLE, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(IN_WHEELSPEED), InterruptMonitoring::WheelPulse0, RISING);
  attachInterrupt(digitalPinToInterrupt(IN_WHEELSPEED+1), InterruptMonitoring::WheelPulse1, RISING);
  attachInterrupt(digitalPinToInterrupt(IN_WHEELSPEED+2), InterruptMonitoring::WheelPulse2, RISING);
  attachInterrupt(digitalPinToInterrupt(IN_WHEELSPEED+3), InterruptMonitoring::WheelPulse3, RISING);
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

      in.paddleUp = digitalRead(IN_PADDLEUP);
      in.paddleDown = digitalRead(IN_PADDLEDOWN);
      return in;
}

void IO::SendOutputs(Output o) {
      // NEED TO DEAL WITH CUT VARIABLES. THEY ARE CURRENTLY BEING IGNORED
      analogWrite(OUT_THROTTLE, o.throttle);
      digitalWrite(OUT_SHIFTUP, o.shiftUp);
      digitalWrite(OUT_SHIFTDOWN, o.shiftDown);
      digitalWrite(OUT_CLUTCH, o.clutch);
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
