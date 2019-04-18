//#include "Constants.h"

/*
    SPI Pins <=> Arduino Uno  <=> Arduino Mega 2560
    SCK      <=>       13     <=>         52
    MISO     <=>       12     <=>         50
    MOSI     <=>       11     <=>         51
    SS       <=>       10     <=>         53
*/

#include <mcp2515.h>
#include <mcp2515_defs.h>
#include <defaults.h>
#include <Canbus.h>
#include <global.h>

int counter = 0;
unsigned long int last = 0;

//********************************Setup Loop*********************************//

void setup() {
  Serial.begin(9600);
  //  pinMode(10,INPUT);
  //  pinMode(11,INPUT);
  //  pinMode(12,INPUT);
  //  pinMode(13,INPUT);
  Serial.println("Hello. Am Fudge.");

  if (Canbus.init(CANSPEED_500)) //Initialise MCP2515 CAN controller at the specified speed
    Serial.println("CAN Init ok");
  else
    Serial.println("Can't init CAN");
  //
  ////  delay(1000);
  //pinMode(39, OUTPUT);
  //pinMode(41, INPUT_PULLUP);
}


void loop()
{
  tCAN message;
  if (mcp2515_check_message())
  {
    counter++;
    if (mcp2515_get_message(&message))
    {
//              if(message.id == 0x620 and message.data[2] == 0xFF)  //uncomment when you want to filter
//                   {
      
                     Serial.print("ID: ");
                     Serial.print(message.id,HEX);
                     Serial.print(", ");
                     Serial.print("Data: ");
                     for(int i=0;i<message.header.length;i++)
                      {
                        Serial.print((char) message.data[i]);
                        Serial.print(" ");
                      }
                     Serial.println("");
                   //}
    }
  }


  if (millis() - last > 1000) {
    last = millis();
//    Serial.println(counter);
    counter = 0;
  }
}
