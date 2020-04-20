//Variables used corresponding to the pin numbers of the lights
int HIGH_BEAM = 11;
int LOW_BEAM = 5;
int REAR_RIGHT = 3;
int REAR_LEFT = 10;
int FRONT_RIGHT = 9;
int FRONT_LEFT = 6;

//Variable to store the character received by serial
char serial_char;
//Flags used to store the state of the lights
//Initialized on false because at the beginning all the lights are turned off
boolean high = false;
boolean low = false;
boolean left = false;
boolean right = false;
boolean alarm = false;

void setup() {	
  pinMode(HIGH_BEAM , OUTPUT);
  pinMode(LOW_BEAM, OUTPUT);
  pinMode(REAR_RIGHT, OUTPUT);
  pinMode(REAR_LEFT , OUTPUT);
  pinMode(FRONT_RIGHT, OUTPUT);
  pinMode(FRONT_LEFT, OUTPUT);
  Serial.begin(9600);
}



void loop() {
        //Read the value received in the serial
        serial_char = Serial.read();

        //Change the status of the flags depending on the value received via serial
        if(serial_char == 'd') {//Check status of the low beam flag and toggle it
          if(low) {
            low = false;
          }
          else {
            low = true;
            high = false;
          }
        }
        else if(serial_char == 'b') {//Check status of the high beam flag and toggle it
          if(high) {
            high = false;
          }
          else {
             high = true;
             low = false;
          }         
        }
        else if(serial_char == 'a') {//Check status of the right directionals flag and toggle it
          if(right) {
            right = false;
          }
          else {
            right = true;
            left = false;
            alarm = false;
          }
        }
        else if(serial_char == 'c') {//Check status of the left directionals flag and toggle it
          if(left) {
            left = false;
          }
          else {
            left = true;
            right = false;
            alarm = false;
          }
        }
        else if(serial_char == 'e') {//Check status of the alarm flag and toggle it
          if(alarm) {
            alarm = false;
          }
          else {
            alarm = true;
            left = false;
            right = false;
          }
        }
        
        //Turn on the lights that are activated by the flags
        if(high) {
       	  digitalWrite(HIGH_BEAM, HIGH);
        }
        else {
          digitalWrite(HIGH_BEAM, LOW);
        }
        if(low) {
      	  digitalWrite(LOW_BEAM, HIGH);
        }
        else {
       	  digitalWrite(LOW_BEAM, LOW);
        }
        
        if(right) {
          digitalWrite(REAR_RIGHT, HIGH);
          digitalWrite(FRONT_RIGHT, HIGH);
          delay(200);
          digitalWrite(REAR_RIGHT, LOW);
          digitalWrite(FRONT_RIGHT, LOW);
          delay(200);
        }
        if(left) {
          digitalWrite(REAR_LEFT, HIGH);
          digitalWrite(FRONT_LEFT, HIGH);
          delay(200);
          digitalWrite(REAR_LEFT, LOW);
          digitalWrite(FRONT_LEFT, LOW);
          delay(200);
        }
        if(alarm) {
//          digitalWrite(HIGH_BEAM, HIGH);
          digitalWrite(REAR_RIGHT, HIGH);
          digitalWrite(REAR_LEFT, HIGH);
          digitalWrite(FRONT_RIGHT, HIGH);
          digitalWrite(FRONT_LEFT, HIGH);
	  delay(200);
//          digitalWrite(HIGH_BEAM, LOW);
          digitalWrite(REAR_RIGHT, LOW);
          digitalWrite(REAR_LEFT, LOW);
          digitalWrite(FRONT_RIGHT, LOW);
          digitalWrite(FRONT_LEFT, LOW);
	  delay(200);        
        }
        
        
//        delay(1000);
          delay(100);

}

