// This will define a simple table relationship between throttle position and allowable brake position, for plausibility checking
// we might automatically generate this file with a matlab script. it be cool.

#ifndef BRAKETHROTTLEMAP_H
#define BRAKETHROTTLEMAP_H

struct BrakeThrottleMap {
      static double brakeValues[1];
      static double throttleValues[1];
      
      static bool CheckMap(double TPS, double BSE) {
//            loop through brake array
//                  find first value higher than BSE
//                  break;
//            if throttle array at same index < TPS
//                  PANIC;
//                  return false;
//            else
//                  remain calm;
                  return true;
      }
};

double BrakeThrottleMap::brakeValues[] = {1};
double BrakeThrottleMap::throttleValues[] = {1};

#endif
