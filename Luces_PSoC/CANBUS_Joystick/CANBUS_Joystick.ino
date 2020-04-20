#define BAUDRATE  9600

#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>

void setup() {
  Serial.begin(BAUDRATE);
  Canbus.init(CANSPEED_500);
}

//Variables;
char InputChar[8]   = {'x','x','x','x','x','x','x','x'};
bool Can            = false;

//Método de comunicación:
void Communication()
{
  if(Serial.available() > 0)
  {
    Serial.readBytes(InputChar, 8);
    Can = true;
  }
  else
    Can = false;
}

void Debug()
{
  Serial.print("Cadena = ");
  Serial.println(InputChar);
}

int ConvertionCharToHex(char toConvert)
{
  switch(toConvert)
  {
    case '0':
      return 0x30;
      break;
    case '1':
      return 0x31;
      break;
    case '#':
      return 0x23;
      break;
    case '&':
      return 0x26;
      break;
  }
}

void CAN()
{
  tCAN message;
  message.id = 0x631;         //formatted in HEX
  message.header.rtr = 0;
  message.header.length = 7;  //formatted in DEC
  message.data[0] = ConvertionCharToHex(InputChar[0]);
  message.data[1] = ConvertionCharToHex(InputChar[1]);
  message.data[2] = ConvertionCharToHex(InputChar[2]);
  message.data[3] = ConvertionCharToHex(InputChar[3]);
  message.data[4] = ConvertionCharToHex(InputChar[4]);
  message.data[5] = ConvertionCharToHex(InputChar[5]);
  message.data[6] = ConvertionCharToHex(InputChar[6]);
  mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
  mcp2515_send_message(&message);
}

void loop()
{
  Communication();
  if(Can)
    CAN();
}
