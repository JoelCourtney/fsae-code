#include "IO.h"
#include "Constants.h"
#include <Arduino.h>

bool IO::Initialize() {
  pinMode(IN_PADDLEUP, INPUT);
  pinMode(IN_PADDLEDOWN, INPUT);
  pinMode(IN_RPM, INPUT);
  for(int i = 0; i < 4; i++)
    pinMode(IN_WHEELSPEED + i, INPUT);

  pinMode(OUT_SHIFTUP, OUTPUT);
  pinMode(OUT_SHIFTDOWN, OUTPUT);
  pinMode(OUT_CLUTCH, OUTPUT);
  pinMode(OUT_BRAKELIGHT, OUTPUT);
  pinMode(OUT_THROTTLE, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(IN_WHEELSPEED), PWMMonitoring::WheelPulse0, RISING);
  attachInterrupt(digitalPinToInterrupt(IN_WHEELSPEED+1), PWMMonitoring::WheelPulse1, RISING);
  attachInterrupt(digitalPinToInterrupt(IN_WHEELSPEED+2), PWMMonitoring::WheelPulse2, RISING);
  attachInterrupt(digitalPinToInterrupt(IN_WHEELSPEED+3), PWMMonitoring::WheelPulse3, RISING);
  attachInterrupt(digitalPinToInterrupt(IN_RPM), PWMMonitoring::RPMPulse, RISING);

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
      analogWrite(OUT_THROTTLE, o.throttle);
      digitalWrite(OUT_SHIFTUP, o.shiftUp);
      digitalWrite(OUT_SHIFTDOWN, o.shiftDown);
      digitalWrite(OUT_CLUTCH, o.clutch);
      digitalWrite(OUT_BRAKELIGHT, o.brakeLight);
}

void IO::CutThrottle(int enforce) {
      // do the cut throttle thing, then
      if (enforce) {
//            {// loop 1 second
//                  ReadInputs();
//                  if (enforce & ENFORCE_BRAKETHROTTLEDIFF) {
//                        if (TPS1 == 0) {
//                              return;
//                        }
//                  }
//                  if (enforce & ENFORCE_EXPTPSDIFF) {
//                        if (inTPS1 == throttle) {
//                              return;
//                        }
//                  }
//            }
//            CutIgnition();
      }
}

void IO::CutIgnition() {
      // do the thing
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
  return (TPS1 + TPS2) / 2; // no
}
