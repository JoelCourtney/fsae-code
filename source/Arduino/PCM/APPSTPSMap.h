// This will define a simple table to convert APPS pedal input to TPS output. We can define this function however we want.
// we might automatically generate this file with a matlab script. it be cool.

#ifndef APPSTPSMAP_H
#define APPSTPSMAP_H

#define APPSTPSMAP_SIZE 6

struct APPSTPSMap {
  static double APPSValues[APPSTPSMAP_SIZE];
  static double TPSValues[APPSTPSMAP_SIZE];

  static double Map(double APPS) {
    int i;
    double ratio;
    for (i = 1; i < APPSTPSMAP_SIZE; i++) {
      if (APPSValues[i] > APPS) {
        ratio = (APPS - APPSValues[i - 1]) / (APPSValues[i] - APPSValues[i - 1]);
        break;
      }
    }
    if (i == APPSTPSMAP_SIZE) {
      ratio = (APPS - APPSValues[i - 2]) / (APPSValues[i - 1] - APPSValues[i - 2]);
      i--;
    }
    return TPSValues[i-1] + ratio * (TPSValues[i] - TPSValues[i-1]);
  }
};

double APPSTPSMap::APPSValues[] = {0, 1, 2, 3, 4, 5};
double APPSTPSMap::TPSValues[] = {0, 1, 2, 3, 4, 5};

#endif
