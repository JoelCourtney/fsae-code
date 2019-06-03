#include "IO.h"
#include "Brain.h"

Brain b;
int i;

void setup() {
  // Initialize everything.
  
  int res = IO::Initialize();
  if (res == ERROR_CAN_INITIALIZATION) {
    Serial.println("can failed");
  } else if (res == ERROR_SD_INITIALIZATION) {
    Serial.println("sd failed");
  }
  while (!b.Initialize()) {};
  
}

void loop() {
  // Simple loop. Reads inputs, processes data, sends outputs.
  
  IO::SendOutputs(
    b.Update(
      IO::ReadInputs()
    )
  );
}

// Effectively the oh shit switch. Watchdog timer failed, something has gone horribly wrong.
