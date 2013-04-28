
  
  const int latchPin = 13;
  const int clockPin = 12;
  const int dataPin = 11;
  
  const int inputPin = A2;
  const int relayPin = 6;
  const int vcc = A0;
  const int gnd = A4;
  
  const int UP = 4;
  const int DOWN = 5;
  const int SET_LIMIT = 3;
  const int OK = 2;
  
  int limit = 50;
 
   
  void setup(){
    
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    
    pinMode(vcc, OUTPUT);
    pinMode(gnd, OUTPUT);
    
    pinMode(relayPin, OUTPUT);
    pinMode(inputPin, INPUT);
    
    pinMode(OK, INPUT);
    pinMode(UP, INPUT);
    pinMode(DOWN, INPUT);
    pinMode(SET_LIMIT, INPUT);
    
    digitalWrite(OK, HIGH);
    digitalWrite(UP, HIGH);
    digitalWrite(DOWN, HIGH);
    digitalWrite(SET_LIMIT, HIGH);
    
    digitalWrite(relayPin, LOW);  
    digitalWrite(vcc, HIGH);
    digitalWrite(gnd, LOW);
   
  }
  
  
  void loop(){
    
    int myReading = map(analogRead(inputPin), 0, 1023, 0, 100);
    displayNumber(myReading);
    buttonListener();  
    activateRelay(myReading);
  }
  
  
  void displayNumber(int number){
     
   int numbers[] = { 0B10000000, 0B11110010, 0B01001000, 0B01100000, 0B00110010, 0B00100100, 0B00000100, 0B11110000, 0B00000000,0B00110000 };
  
   int onesPlace = number%10;
   int tensPlace = number/10;
    
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST,numbers[onesPlace]);
   shiftOut(dataPin, clockPin, MSBFIRST,numbers[tensPlace]);
   digitalWrite(latchPin, HIGH);
     
  }
  
  void buttonListener(){
  
    if(debounce(SET_LIMIT)== LOW)
      setLimit();
  
  }
  
  void setLimit() {
   
    do{
     
      if(debounce(UP)== LOW && limit < 99 ) //increment current limit
        limit++;
        
      if(debounce(DOWN)== LOW && limit > 0) //decrement current limit
        limit--;
        
      displayNumber(limit);
        
   }while(debounce(OK) != LOW);
   
    delay(1000);
    
  }
  
  
  void activateRelay(int reading){
  
    boolean value = (reading >= limit)? HIGH : LOW; 
    digitalWrite(relayPin, value); 
  }
  
  
  boolean debounce(int pin){
   
    int debounceDelay = 50; // milliseconds to wait until stable
    boolean state;
    boolean previousState;
    previousState = digitalRead(pin); // store switch state
    
    for(int counter=0; counter < debounceDelay; counter++)
    {
      delay(1); // wait for 1 millisecond
      state = digitalRead(pin); // read the pin
      
      if( state != previousState)
      {
        counter = 0; // reset the counter if the state changes
        previousState = state; // and save the current state
      }
    }
    // here when the switch state has been stable longer than the debounce period
    return state;
  }
