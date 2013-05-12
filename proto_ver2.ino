  //Pin connected to ST_CP of 74HC595
  int latchPin = 10;
  //Pin connected to SH_CP of 74HC595
  int clockPin = 9;
  //Pin connected to DS of 74HC595
  int dataPin = 11;
  //Pin connected to output pin of LM35
  int sensor = A5; 

  const int digits[] = 
  {
  0B00111111, //0
  0B00000110, //1
  0B01011011, //2
  0B01001111, //3
  0B01100110, //4
  0B01101101, //5
  0B01111101, //6
  0B00000111, //7
  0B01111111, //8
  0B01101111  //9
  };


  void setup() {
  
    //set pins to output so you can control the shift register
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(sensor, INPUT);
  }


  void loop(){
  
    float val = (analogRead(sensor) / 1024.0) * 500; 
  
    displayNumber(val); 
  }
  

  void displayNumber(float readings){
  
    int num = readings*10;
    
    for(int i=0; i<4; i++){
    
      digitalWrite(latchPin, LOW);
        
      //  shiftOut(dataPin, clockPin, MSBFIRST, (i==3) ? 0B00111001 :   ((i==1)? (0B10000000 | digits[num%10]) : digits[num%10])  );

      shiftOut(dataPin, clockPin, MSBFIRST, (i!=3) ?  ((i==1)? (0B10000000 | digits[num%10]) : digits[num%10])  : 0B00111001 ) ;

      num /= 10;
    
      shiftOut(dataPin, clockPin, MSBFIRST, ~(1 << i));
    
      digitalWrite(latchPin, HIGH);
    
      delay(1);
    }  

  }

