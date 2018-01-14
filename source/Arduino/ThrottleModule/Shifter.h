// This is gonna be a LOT more complicated than what I have here.

#define NO_THROTTLE 0
#define FULL_THROTTLE 1

class Shifter {
      bool shifting = false;
      int currentGear;
      int targetGear;

      double gearRatios[] = {gear ratios to convert wheelSpeed to revs};
public:
      void ShiftUp();
      void ShiftDown();

      double RevMatchTPS(double, double);
}
