#define ENFORCE_TPSDIFF 1
#define ENFORCE_BRAKETHROTTLEDIFF 2

#include <function>

struct Parameters {
      double APPS1;
      double APPS2;
      double APPSave;
      
      double TPS1;
      double TPS2;
      double TPSave;
      double TPSexp;
      
      double BSE;
      
      void ReadInputs();
      void SendOutputs();
      
      void CutThrottle(int);
      void CutIgnition();
}