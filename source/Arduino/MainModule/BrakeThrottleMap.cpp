// we might automatically generate this file with a matlab script. it be cool.

namespace BrakeThrottleMap {
      double brakeValues[] = { STUFF };
      double throttleValues[] = {stuff};
      
      bool CheckMap(double TPS, double BSE) {
            loop through brake array
                  find first value higher than BSE
                  break;
            if throttle array at same index < TPS
                  PANIC;
                  return false;
            else
                  remain calm;
                  return true;
      }
}