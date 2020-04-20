/****************************************************************************
CAN Write Demo for the SparkFun CAN Bus Shield. 
Written by Stephen McCoy. 
Original tutorial available here: http://www.instructables.com/id/CAN-Bus-Sniffing-and-Broadcasting-with-Arduino
Used with permission 2016. License CC By SA. 
Distributed as-is; no warranty is given.
*************************************************************************/

#include "Canbus.h"
#include "defaults.h"
#include "global.h"
#include "mcp2515.h"
#include "mcp2515_defs.h"

char serial_char;

//********************************Setup Loop*********************************//

void setup() {
  Serial.begin(9600);
  Serial.println("CAN Write - Testing transmission of CAN Bus messages");
  delay(1000);
  
  if(Canbus.init(CANSPEED_500))  //Initialise MCP2515 CAN controller at the specified speed
    Serial.println("CAN Init ok");
  else
    Serial.println("Can't init CAN");
    
  delay(1000);
}

//********************************Main Loop*********************************//

void send_can_message(char k) {
  tCAN message;
  
  message.id = 0x001; //formatted in HEX
  message.header.rtr = 0;
  message.header.length = 1; //formatted in DEC
  message.data[0] = k;

  //mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
  mcp2515_send_message(&message);      
}

void loop() {
        tCAN message;
        
        serial_char = Serial.read(); 
/*        if(serial_char == 'a') {
            send_can_message('a');
        }
        if(serial_char == 'b') {
            send_can_message('b');
        }
        if(serial_char == 'c') {
            send_can_message('c');
        }
        if(serial_char == 'd') {
            send_can_message('d');
        }
        if(serial_char == 'e') {
            send_can_message('e');
        }        
        */
        send_can_message(serial_char);
        delay(1000);
}
