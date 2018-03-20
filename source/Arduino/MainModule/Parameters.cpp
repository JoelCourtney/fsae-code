#include "Parameters.h"
#include "Constants.h"
#include <Arduino.h>

bool Parameters::Initialize() {
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

void Parameters::ReadInputs() {
      TPS1 = analogRead(IN_TPS1);
      TPS2 = analogRead(IN_TPS2);
      APPS1 = analogRead(IN_APPS1);
      APPS2 = analogRead(IN_APPS2);
      BSE1 = analogRead(IN_BSE1);
      BSE2 = analogRead(IN_BSE2);

      paddleUp = digitalRead(IN_PADDLEUP);
      paddleDown = digitalRead(IN_PADDLEDOWN);

}

void Parameters::SendOutputs() {
      analogWrite(OUT_THROTTLE, throttle);
      digitalWrite(OUT_SHIFTUP, shiftUp);
      digitalWrite(OUT_SHIFTDOWN, shiftDown);
      digitalWrite(OUT_CLUTCH, clutch);
      digitalWrite(OUT_BRAKELIGHT, brakeLight);
}

void Parameters::CutThrottle(int enforce) {
      // do the cut throttle thing, then
      if (enforce) {
            {// loop 1 second
                  ReadInputs();
                  if (enforce & ENFORCE_BRAKETHROTTLEDIFF) {
                        if (TPS1 == 0) {
                              return;
                        }
                  }
                  if (enforce & ENFORCE_EXPTPSDIFF) {
                        if (TPS1 == throttle) {
                              return;
                        }
                  }
            }
            CutIgnition();
      }
}

void Parameters::CutIgnition() {
      // do the thing
}
