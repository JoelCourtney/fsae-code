#define CLUTCH_IN false
#define CLUTCH_OUT true

struct Parameters {
public:
      bool throttleCut;
      bool shiftUp;
      bool shiftDown;
      
      double wheelSpeed;
      double revs;
      
      double expTPS;
      bool? double? clutch;
      some mess of shifter outputs;
      
      bool Initialize();
      
      void ReadInputs();
      void SendOutputs();
      
      void RPMInt();
      void wheel1Int();
      void wheel2Int();
      void wheel3Int();
      void wheel4Int();
}