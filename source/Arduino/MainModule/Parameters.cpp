#include "Parameters.h"

void Parameters::ReadInputs() {
      // read in APPS1/2, TPS1/2, TPSexp, and BSE
}

void Parameters::SendOutputs() {
      // send APPSave, TPSave to output pins;
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
