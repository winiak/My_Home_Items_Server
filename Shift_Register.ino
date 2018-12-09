#ifndef DEFS
#include "defs.h"
#endif

int outEnPin = D8;    // PIN 13
int latchPin = D7;    // PIN 12
int dataPin = D6;     // PIN 14
int clockPin = D5;    // PIN 11

int numOfRegisters = 4;
byte* registerState;

void printBits(byte myByte){
 for(byte mask = 0x80; mask; mask >>= 1){
   if(mask  & myByte)
       Serial.print('1');
   else
       Serial.print('0');
 }
}

void print_shift_registers() {
  for (int i = 0; i < numOfRegisters; i++) {
    printBits(registerState[i]);
    Serial.print(" ");
  }
  Serial.println();
}

void test_shift() {
  if (server.argName(0) == "item") {
    Serial.println(server.arg(0));
    int val = server.arg(0).toInt() - 1;
    if (val == 0) {
      Serial.println("Reset all");
      for (unsigned int curPin = 1; curPin <= 16; curPin++) {
        regWrite(curPin, 1);
        delay(10);
      }
    } else {
      Serial.print("Set: "); Serial.println(val);
      regWrite(val, 0);
    }
  }
}

void setup_shift() {
  pinMode(outEnPin, OUTPUT);
  //disable output first (high impedance of Latch
  digitalWrite(outEnPin, HIGH);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
/*
  for (uint8_t i = 0; i < numOfRegisters; i++)
    registerState[i] = 255;

  /*
  for (uint8_t i = 0; i < numOfRegisters * 8; i++) {
    regWrite(i, 1);
    delay(10);
  }
  digitalWrite(outEnPin, LOW);
  */
  registerState = new byte[numOfRegisters];
  for (uint8_t i = 0; i < numOfRegisters; i++)
    registerState[i] = 255;

// reset all outputs to HIGH == relays off
    for (unsigned int curPin = 1; curPin <= numOfRegisters*2; curPin++) {
      regWrite(curPin, 1);
      delay(10);
    }
  
  digitalWrite(outEnPin, LOW);
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
