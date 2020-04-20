//Assign variable names to the pins
char Joystick=2, Right=3, Top=4, Left=5, Down=6;
double t1, t2;

bool flag1 = false,
     flag2 = false,
     flag3 = false,
     flag4 = false,
     flag5 = false;

void setup() {
  pinMode(Right,    INPUT_PULLUP);
  pinMode(Top,      INPUT_PULLUP);
  pinMode(Left,     INPUT_PULLUP);
  pinMode(Down,     INPUT_PULLUP);
  pinMode(Joystick, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
    //Check right button status
    if(digitalRead(Right) == HIGH) {
      flag1 = true;
    }
    else if(digitalRead(Right) == LOW && flag1 == true) {
      flag1 = false;
      Serial.write('a');
    }
    //Check top button status
    if(digitalRead(Top) == HIGH) {
      flag2 = true;
    }
    else if(digitalRead(Top) == LOW && flag2 == true)   {
      flag2 = false;
      Serial.write('b');
    }
    //Check down button status
    if(digitalRead(Down) == HIGH) {
      flag3 = true;
    }
    else if(digitalRead(Down) == LOW && flag3 == true) {
      flag3 = false;
      Serial.write('c');
    }
    //Check left button status
    if(digitalRead(Left) == HIGH) {
      flag4 = true;
    }
    else if(digitalRead(Left) == LOW && flag4 == true) {
      flag4 = false;
      Serial.write('d');
    }
    //Check joystick button status
    if(digitalRead(Joystick) == HIGH) {
      flag5 = true;
    }
    else if(digitalRead(Joystick) == LOW && flag5 == true) {
      flag5 = false;
      Serial.write('e');
    }    
    //Wait for 500 ms, then go back to the beginning of 'loop' and repeat.
    delay(100);      
}
