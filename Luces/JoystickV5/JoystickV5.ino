int D2 = 2;    //HAZARD
int D3 = 3;    //TURNR
int D6 = 6;    //TURNL
int D4 = 4;    //HIGHB
int D5 = 5;    //LOWB
int D7 = 7;    //COURTESY


  //State flag
  int HAZARD = 0, TURNR = 0, TURNL = 0, HIGHB = 0, LOWB = 0, COURTESY = 0;
  //Previous state for turns
  int PrevTurnR = 0, PrevTurnL = 0, PrevHazard = 0;
  //Mechanical bounce flag
  int D4R = 0, D5R = 0, D2R = 0, D3R = 0, D6R = 0, D7R = 0;
  //String to send
  char CAN[8] = {'0','0','0','0','0','0','0','0'};
  //Change of state
  bool match = true; 
  //Counter for buttons
  int Count2 = 0, Count3 = 0, Count4 = 0, Count5 = 0, Count6 = 0, Count7 = 0, TotalCount = 0, Ciclado = 0;
  //Variable for changes in turn while in hazard
  int HTurn = 0;

void setup() {
  int i;
 for(i = 2; i < 8; i++){
  pinMode(i,INPUT); 
  digitalWrite(i,HIGH);
  }
  Serial.begin(9600); 
}

//Method to convert int to char:
char ConvertIntToChar(int entero){
  switch(entero)
  {
    case 1:
      return '1'; 
      break;
    case 0:
      return '0';
      break;
    default:
      return '?';
      break;
  }
}

//Method to build the matrix to send
void MakeOutput()
{
  CAN[0] = '#';
  CAN[1] = ConvertIntToChar(HAZARD);
  CAN[2] = ConvertIntToChar(TURNR);
  CAN[3] = ConvertIntToChar(TURNL);
  CAN[4] = ConvertIntToChar(HIGHB);
  CAN[5] = ConvertIntToChar(LOWB);
  CAN[6] = ConvertIntToChar(COURTESY);
  CAN[7] = '&';
}

void loop() {
  if(digitalRead(D2) == LOW){
    D2R = 1;
    Count2 = 1;  
  }
   delay(30);
  if(digitalRead(D4) == LOW){
    D4R = 1;  
    Count4 = 1; 
  }
   delay(30);
  if(digitalRead(D5) == LOW){
    D5R = 1; 
    Count5 = 1;  
  }
   delay(30);
  if(digitalRead(D3) == LOW){
    D3R = 1; 
    Count3 = 1;  
  }
  delay(30);
  if(digitalRead(D6) == LOW){
    D6R = 1; 
    Count6 = 1;  
  }
  delay(30);




  if(HAZARD == 0 && TURNR == 0 && TURNL == 0 && HIGHB == 0 && LOWB == 0){
      if(digitalRead(D7) == LOW){
        D7R = 1; 
        Count7 = 1;  
      }
  delay(30);
    if(digitalRead(D7) == HIGH && D7R == 1){
      COURTESY = 1;
      match = false;
      D7R = 0;
      Count7 = 0;
      }
  }
  
if(COURTESY == 0){
  if(digitalRead(D4) == HIGH && D4R == 1){
    LOWB = 0;
    HIGHB = !HIGHB;  
    D4R = 0;
    match = false;
      Count4 = 0;
  }
  if(digitalRead(D5) == HIGH && D5R == 1){
    HIGHB = 0;
    LOWB = !LOWB;  
    D5R = 0;
    match = false;
      Count5 = 0;
  }
  if(digitalRead(D2) == HIGH && D2R == 1){
    TURNR = 0;
    TURNL = 0;
    HAZARD = !HAZARD;
    D2R = 0;
    PrevHazard = 1;
    match = false;
      Count2 = 0;
  }  
    
  if(HAZARD == 0){
    
      if(PrevHazard == 1){
        TURNR = PrevTurnR; 
        TURNL = PrevTurnL; 
      } 

      if(HTurn == 1){
        TURNR = PrevTurnR; 
        TURNL = PrevTurnL; 
      }
        
    if(digitalRead(D3) == HIGH && D3R == 1){
      TURNL = 0;
      TURNR = !TURNR; 
      D3R = 0; 
      match = false;
      Count3 = 0;
    }  
    if(digitalRead(D6) == HIGH && D6R == 1){
      TURNR = 0;
      TURNL = !TURNL;      
      D6R = 0;   
      match = false;
      Count6 = 0;
    }
  
    PrevTurnR = TURNR;
    PrevTurnL = TURNL;
    PrevHazard = 0;
    HTurn = 0;
  }
  else if(HAZARD == 1){
   if(digitalRead(D3) == HIGH && D3R == 1){
      PrevTurnL = 0;
      PrevTurnR = !PrevTurnR; 
      D3R = 0; 
      match = false;
      Count3 = 0;
    }  
    if(digitalRead(D6) == HIGH && D6R == 1){
      PrevTurnR = 0;
      PrevTurnL = !PrevTurnL;      
      D6R = 0;   
      match = false;
      Count6 = 0;
    } 
    HTurn = 1; 
  }


}
  
  TotalCount = Count2 + Count3 + Count4 + Count5 + Count6 + Count7;

  if(TotalCount >= 2){
      CAN[8] = "#000000&";
  }


  MakeOutput();
  if(match == false)
    if(Serial.availableForWrite())
      Serial.write(CAN,8); 
  match = true;
  COURTESY = 0;
}
