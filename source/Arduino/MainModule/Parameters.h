// #include <function> maybe

struct Parameters {

  // STILL MISSING C-16 on the ECU.

// inputs
      double TPS1, TPS2;
      double APPS1, APPS2;
      double BSE1, BSE2;
      bool paddleUp, paddleDown;
      pwm_double wheelSpeed[4];
      pwm_double RPM;

// outputs
      double throttle;
      bool shiftUp, shiftDown;
      bool clutch;
      bool brakeLight;

      bool Initialize();

      void ReadInputs();
      void SendOutputs();

      void CutThrottle(int);
      void CutIgnition();
}
