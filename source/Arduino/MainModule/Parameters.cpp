#include "Parameters.h"

bool Parameters::Initialize() {
  pinMode(IN_PADDLEUP, INPUT);
  pinMode(IN_PADDEDOWN, INPUT);
  pinMode(IN_RPM, INPUT);
  for(int i = 0; i < 4; i++)
    pinMode(IN_WHEELSPEED + i, INPUT);

  pinMode(OUT_SHIFTUP, OUTPUT);
  pinMode(OUT_SHIFTDOWN, OUTPUT);
  pinMode(OUT_CLUTCH, OUTPUT);
  pinMode(OUT_BRAKELIGHT, OUTPUT);
  pinMode(OUT_THROTTLE, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(IN_RPM), RISING)

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
      for(int i = 0; i < 4; i++) {
        wheelSpeed[i] = digitalRead(IN_WHEELSPEED + i);

        // maybe? probably have to make an interrupt for pwm stuffs.
      }

      RPM is weird. Because PWM.
}

void Parameters::SendOutputs() {
      analogWrite(OUT_THROTTLE);
      digitalWrite(OUT_SHIFTUP);
      digitalWrite(OUT_SHIFTDOWN);
      digitalWrite(OUT_CLUTCH);
      digitalWrite(OUT_BRAKELIGHT);
}

void Parameters::CutThrottle(int enforce) {
      // do the cut throttle thing, then
      if enforce {
            {// loop 1 second
                  ReadInputs();
                  if enforce & ENFORCE_TPSDIFF {
                        if throttle has closed {
                              return;
                        }
                  }
                  if enforce & ENFORCE_BRAKETHROTTLEDIFF {
                        if TPS matches TPSexp {
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

void Parameters::RPMInt() {
      
}