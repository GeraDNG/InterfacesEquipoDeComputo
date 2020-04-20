#define pin_FrontRight 6
#define pin_FrontLeft 9
#define pin_BackRight 10
#define pin_BackLeft 3
#define pin_HighBeam 11
#define pin_LowBeam 5
#define pin_Warning 8

#define BAUDRATE  9600

char InputChar[8] = {'x','x','x','x','x','x','x','x'};
bool Hazard = false;
bool TurnLeft = false;
bool TurnRight = false;
bool HighBeam = false;
bool LowBeam = false;

void setup() {
  Serial.begin(BAUDRATE);
  pinMode(pin_FrontRight, OUTPUT);
  pinMode(pin_FrontLeft, OUTPUT);
  pinMode(pin_BackRight, OUTPUT);
  pinMode(pin_BackLeft, OUTPUT);
  pinMode(pin_HighBeam, OUTPUT);
  pinMode(pin_LowBeam, OUTPUT);
  pinMode(pin_Warning, OUTPUT);
}

void Debug()
{
  Serial.print("Cadena = ");
  Serial.println(InputChar);
}

void Communication()
{
  if(Serial.available() > 0)
  {
    Serial.readBytes(InputChar, 8);
    Debug();
  }
}

void HAZARD()
{
  digitalWrite(pin_FrontRight, HIGH);
  delay(25);
  digitalWrite(pin_BackRight, HIGH);
  digitalWrite(pin_FrontLeft, HIGH);
  delay(25);
  digitalWrite(pin_BackLeft, HIGH);
  delay(500);
  digitalWrite(pin_FrontRight, LOW);
  delay(25);
  digitalWrite(pin_BackRight, LOW);
  digitalWrite(pin_FrontLeft, LOW);
  delay(25);
  digitalWrite(pin_BackLeft, LOW);
  delay(500);
}

void NOHAZARD(){
  digitalWrite(pin_FrontRight, LOW);
  digitalWrite(pin_BackRight, LOW);
  digitalWrite(pin_FrontLeft, LOW);
  digitalWrite(pin_BackLeft, LOW);
  }

void TURNLEFT()
{
  digitalWrite(pin_FrontLeft, HIGH);
  delay(25);
  digitalWrite(pin_BackLeft, HIGH);
  delay(500);
  digitalWrite(pin_FrontLeft, LOW);
  delay(25);
  digitalWrite(pin_BackLeft, LOW);
  delay(500);
}
void NOTURNLEFT(){
  digitalWrite(pin_FrontLeft, LOW);
  digitalWrite(pin_BackLeft, LOW);
  }

void TURNRIGHT()
{
  digitalWrite(pin_FrontRight, HIGH);
  delay(25);
  digitalWrite(pin_BackRight, HIGH);
  delay(500);
  digitalWrite(pin_FrontRight, LOW);
  delay(25);
  digitalWrite(pin_BackRight, LOW);
  delay(500);
}
void NOTURNRIGHT(){
  digitalWrite(pin_FrontRight, LOW);
  digitalWrite(pin_BackRight, LOW);

  }

void HIGHBEAM()
{
  digitalWrite(pin_HighBeam, HIGH);
  digitalWrite(pin_LowBeam, LOW);
}

void NOHIGHBEAM(){
  digitalWrite(pin_HighBeam, LOW);
  }

void LOWBEAM()
{
  digitalWrite(pin_LowBeam, HIGH);
  digitalWrite(pin_HighBeam, LOW);
}

void NOLOWBEAM(){
  digitalWrite(pin_LowBeam, LOW);
  }

void Validations()
  {
    if((InputChar[1] == '0' || InputChar[1] == '1') && InputChar[2] == '0' && InputChar[3] == '0' && InputChar[4] == '0' && InputChar[5] == '0' ){
      digitalWrite(pin_FrontRight, LOW);
      digitalWrite(pin_BackRight, LOW);
      digitalWrite(pin_FrontLeft, LOW);
      digitalWrite(pin_BackLeft, LOW);
      digitalWrite(pin_LowBeam, LOW);
      digitalWrite(pin_HighBeam, LOW);
    }
    if(InputChar[1] == '1'){
        HAZARD();  
      }
    else if (InputChar[1] == '0'){
      NOHAZARD();
      }
    if(InputChar[2] == '1'){
        TURNRIGHT();  
      } 
    else if (InputChar[2] == '0'){
      NOTURNRIGHT();
      }
    if(InputChar[3] == '1'){
        TURNLEFT();  
      } 
    else if (InputChar[3] == '0'){
      NOTURNLEFT();
      }
    if(InputChar[4] == '1'){
        HIGHBEAM();  
      } 
    else if (InputChar[4] == '0'){
      NOHIGHBEAM();
      }
    if(InputChar[5] == '1'){
        LOWBEAM();  
      } 
    else if (InputChar[5] == '0'){
      NOLOWBEAM();
      }
  }

void loop() {
  Communication();
  if(InputChar[0] == '#' && InputChar[7] == 'x'){
    Validations();
    digitalWrite(pin_Warning,LOW);
  }
  else
    digitalWrite(pin_Warning,HIGH);
}
