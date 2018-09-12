#include "IO.h"
#include "Brain.h"

IO io;
Brain b;

void setup() {
  while (!io.Initialize()) {};
  while (!b.Initialize()) {};
  Serial.begin(9600);
}



void loop() {
  io.SendOutputs(
    b.Update(
      io.ReadInputs()
    )
  );
}
