#include <avr/wdt.h>
#include "IO.h"
#include "Brain.h"

Brain b;

void setup() {
  // Initialize everything.
  wdt_disable();
  if (IO::Initialize()) {
    
  }
  while (!b.Initialize()) {};
  wdt_enable(WDTO_500MS);
//  Serial.begin(9600);
}



void loop() {
  // Simple loop. Reads inputs, processes data, sends outputs.
  wdt_reset();
  IO::SendOutputs(
    b.Update(
      IO::ReadInputs()
    )
  );
}

// Effectively the oh shit switch. Watchdog timer failed, something has gone horribly wrong.
ISR(WDT_vect) {
  // cut power to throttle, ignition, fuel, then hang. Must cycle power completely.
  while(true);
}
