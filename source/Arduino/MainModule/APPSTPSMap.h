// This will define a simple table to convert APPS pedal input to TPS output. We can define this function however we want.
// we might automatically generate this file with a matlab script. it be cool.

#ifndef APPSTPSMAP_H
#define APPSTPSMAP_H

struct APPSTPSMap {
      static double APPSValues[1];
      static double TPSValues[1];
      
      static double Map(double APPS) {
            //loop through APPS array
            //      find first value higher than APPS
            //      break;
            //interpolate!
            return 1;
      }
};

double APPSTPSMap::APPSValues[] = {1};
double APPSTPSMap::TPSValues[] = {1};

#endif
