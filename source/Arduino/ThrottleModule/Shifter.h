// This is gonna be a LOT more complicated than what I have here.

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