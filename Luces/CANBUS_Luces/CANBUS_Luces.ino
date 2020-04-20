#define BAUDRATE  9600

#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>

char Output[8] = {'x','x','x','x','x','x','x','x'};

void setup() {
  Serial.begin(BAUDRATE);
  Canbus.init(CANSPEED_500);
}

char ConvertionHexToChar(int toConvert)
{
  switch(toConvert)
  {
    case 0x30:
      return '0';
      break;
    case 0x31:
      return '1';
      break;
    case 0x26:
      return '&';
      break;
    case 0x23:
      return '#'; 
      break;
  }
}

void ReadCAN()
{
  tCAN message;
  if (mcp2515_check_message())                                //Check for available message (recibing from CANBUS Joystick)
  {
    if (mcp2515_get_message(&message))                        //Read the message
    {
      for(int i=0;i<message.header.length;i++) 
      { 
          Output[i] = ConvertionHexToChar(message.data[i]);   //Saving the convertion from HEX to Char in Array "Output" the message
      }
    }
    Serial.write(Output,8);                                   //Write in Serial the message in Char
  }
}

void loop()
{
  ReadCAN();
}
