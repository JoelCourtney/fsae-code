#include <global.h>
#include <Canbus.h>
#include <mcp2515_defs.h>
#include <mcp2515.h>
#include <defaults.h>

#include "Constants.h"
#include "IO.h"

int hold = 900;

void setup() {
  IO::Initialize();
//  lcd.begin(LCD_COLS,LCD_ROWS);
//  delay(100);
}

void loop() {
//  IO.sendOutputs(
//    b.Update(
//      IO.readInputs()
//    )
//  );
  Output o;
  o.RPM = 3510;
  o.seg = hold;
  o.oilPressure = 60;
  o.oilTemp = 120;
  IO::SendOutputs(o);
  delay(1000);
  if (millis() % 100 == 0)
    hold++;
//  delay(1000);
  
//  lcd.setCursor(0,1);
//  lcd.print("hello world");
}
