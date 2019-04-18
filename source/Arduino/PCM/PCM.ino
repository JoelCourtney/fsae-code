#include <avr/wdt.h>
#include "IO.h"
#include "Brain.h"

Brain b;
int i;

void setup() {
  // Initialize everything.
  wdt_disable();
  int res = IO::Initialize();
  if (res == ERROR_CAN_INITIALIZATION) {
    Serial.println("can failed");
  } else if (res == ERROR_SD_INITIALIZATION) {
    Serial.println("sd failed");
  }
  while (!b.Initialize()) {};
  wdt_enable(WDTO_500MS);
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
  digitalWrite(OUT_IGNITION_CUT, true);
  digitalWrite(OUT_FUEL_CUT, true);
  digitalWrite(OUT_THROTTLE_CUT, true);
  while(true);
}
