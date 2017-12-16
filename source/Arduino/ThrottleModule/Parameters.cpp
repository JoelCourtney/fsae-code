#include "Parameters.h"

void Parameters::ReadInputs() {
      // read in throttleCut, APPS, shiftUp, shiftDown, wheelspeed, revs
      // at least some will be over CAN. I'll leave that alone for now.
      if shift is requested:
            absolutely make sure that it is a new request;
            otherwise it will read as 100s of requests by the time the driver has lifted up the paddle
            
}

void Parameters::SendOutputs() {
      // send TPSexp, clutch, shifter controls to output pins;
}

