/*
int outEnPin = D0;
int latchPin = D1;
int dataPin = D2;
int clockPin = D3;

int numOfRegisters = 2;
byte* registerState;


void setup() {
  pinMode(outEnPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  // deactivate all outputs (make sure relays won't turn on)
  digitalWrite(latchPin, HIGH);
  
  //Initialize array
  registerState = new byte[numOfRegisters];
  for (size_t i = 0; i < numOfRegisters; i++) {
    registerState[i] = 0;
  }

  // reset all outputs to HIGH == relays off
  resetRegisters();
  digitalWrite(latchPin, LOW);
}

void loop() {
  /*
  // put your main code here, to run repeatedly:
  for (unsigned int curPin = 1; curPin <= 16; curPin++) {
     regWrite(curPin, 1);
     delay(1000);
  }
  for (unsigned int curPin = 1; curPin <= 16; curPin++) {
     regWrite(curPin, 0);
     delay(1000);
  }
  *//*
}

void resetRegisters() {
  for (int i = 0; i < numOfRegisters; i++) {
    byte* states = &registerState[i];
    shiftOut(dataPin, clockPin, MSBFIRST, *states);
  }
}

void regWrite(int pin, bool state){
  //Determines register
  int reg = pin / 8;
  //Determines pin for actual register
  int actualPin = pin - (8 * reg);

  //Begin session
  digitalWrite(latchPin, LOW);

  for (int i = 0; i < numOfRegisters; i++){
    //Get actual states for register
    byte* states = &registerState[i];

    //Update state
    if (i == reg){
      bitWrite(*states, actualPin, state);
    }

    //Write
    shiftOut(dataPin, clockPin, MSBFIRST, *states);
  }

  //End session
  digitalWrite(latchPin, HIGH);
}
 */
