#define CLUTCH_IN false
#define CLUTCH_OUT true

struct Parameters {
private:
      
public:
      double APPS;
      bool throttleCut;
      bool shiftUp;
      bool shiftDown;
      
      double wheelSpeed;
      double revs;
      
      double expTPS;
      bool? double? clutch;
      some mess of shifter outputs;
      
      void ReadInputs();
      void SendOutputs();
}