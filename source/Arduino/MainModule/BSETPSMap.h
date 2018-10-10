// This will define a simple table relationship between throttle position and allowable brake position, for plausibility checking
// we might automatically generate this file with a matlab script. it be cool.

#ifndef BSETPSMAP_H
#define BSETPSMAP_H

#define BSETPSMAP_SIZE 6

struct BSETPSMap {
private:
      static double throttleValues[6];

public:
      static bool CheckMap(double TPS, double BSE) {
        double scale = BSE * BSETPSMAP_SIZE;
        int i = floor(scale);
        double thresh = throttleValues[i] + (scale - floor(scale)) * (throttleValues[i+1] - throttleValues[i]);
        return TPS <= thresh;
      }
};

double BSETPSMap::throttleValues[] = {0,1,2,3,4,5};

#endif
