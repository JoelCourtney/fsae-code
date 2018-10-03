#include "IO.h"
#include "Brain.h"

IO io;
Brain b;

void setup() {
  // Initialize everything.
  while (!io.Initialize()) {};
  while (!b.Initialize()) {};
//  Serial.begin(9600);
}



void loop() {
  // Simple loop. Reads inputs, processes data, sends outputs.
  io.SendOutputs(
    b.Update(
      io.ReadInputs()
    )
  );
}
