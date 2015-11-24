#include <Interp.h>
#include <interp32.h>
#include "Adafruit_TLC59711.h"
#include <stdint.h>
#include <math.h>

//#include <RGBConverter.h>
#include <SPI.h>


// How many boards do you have chained?
#define NUM_TLC59711 1


Adafruit_TLC59711 tlc = Adafruit_TLC59711(1);
            
#define true 1
#define false 0

#define MAX_16_BITS 65535
#define MAX_20_BITS 262144
#define MAX_24_BITS 16777216
#define MAX_32_BITS 2147483647
uint32_t state = 0;
#define SHIFT_BITS 8
uint32_t MAX_VALUE = pow(2, SHIFT_BITS+16);

int switcher = 0;
int counter = 0;
                                              
void setup() {
  
  Serial.begin(9600);
  
  Serial.println("Dimming test");
  pinMode(10, OUTPUT);
  
  //pinMode(PIN_B2, INPUT_PULLUP);
  //pinMode(PIN_B3, INPUT_PULLUP);

  pinMode(PIN_D0,INPUT_PULLUP);
  pinMode(PIN_D1, OUTPUT); 

  //tlc.setGlobalBrightness(50);
  tlc.begin();
  tlc.write();
  
}


void loop2() {

  setAllLeds(0);
  delay(100);
  setAllLeds(MAX_16_BITS);
  delay(100);  
  setAllLeds(0);
  delay(100);
  setAllLeds(MAX_16_BITS/2);
  delay(100);  
  setAllLeds(0);
  delay(100);
  
  int i=0;
  for (i=0;i<MAX_VALUE;i++) {
    run(5, (uint32_t)i);
  }
  
  setAllLeds(0);
  delay(100);
  setAllLeds(MAX_16_BITS);
  delay(100);  
  setAllLeds(0);
  delay(100);
  setAllLeds(MAX_16_BITS/2);
  delay(100);  
  setAllLeds(0);
  delay(100);
  
  for (i=0;i<=MAX_VALUE;i++) {
    run(5, (uint32_t) MAX_VALUE - i);
  }
  
  setAllLeds(0);
  delay(100);
  
}

void flash(uint32_t v1, uint32_t v2) {
  setAllLeds(0);
  delay(100);
  setAllLeds(v1>>SHIFT_BITS);
  delay(500);  
  setAllLeds(v2>>SHIFT_BITS);
  delay(500);  
  setAllLeds(0);
  delay(100); 
}

Interp32 itrp((uint32_t)0,(uint32_t)MAX_24_BITS,(uint32_t)5000);
Interp itrp16(0,MAX_16_BITS,5000);


void loop() {

  interp(500,0,2000);
 // interpDown(500,2000,0);

  
  //interp(1,10,0,MAX_24_BITS/10);
  //while(1);
}

void setAllLeds(uint16_t v) {
  
    uint16_t r = round(0.6 * v);
    uint16_t g = round(0.5 * v);
    uint16_t b = round(1.0 * v);
  
     tlc.setLED(0, r, g, b);
      tlc.setLED(1, r, g, b);
      tlc.setLED(2, r, g, b);
      tlc.setLED(3, r, g, b);
/*
    tlc.setLED(0, v, v, v);
    tlc.setLED(1, v, v, v);
    tlc.setLED(2, v, v, v);
    tlc.setLED(3, v, v, v); 
 */   
    tlc.write();
}

void interp16(uint16_t value1, uint16_t value2) {
  
  uint16_t currentValue = 0;

  for(currentValue=value1; currentValue <= value2; currentValue++) {
      setAllLeds(itrp16.smooth(currentValue));
      //delay(5);
  }
  
   //Serial.print(currentValue);Serial.print(", ");Serial.println(value2);

 
}

void interp(int loopLength, uint32_t value1, uint32_t value2) {
  
  uint32_t currentValue = 0;

  for(currentValue=value1; currentValue <= value2; currentValue++) {
      Serial.print(currentValue);Serial.print(", ");Serial.print(value1);Serial.print(", ");Serial.println(value2);
      run(loopLength, currentValue);
  }

   //Serial.print(currentValue);Serial.print(", ");Serial.println(value2); 
}

void interpDown(int loopLength, uint32_t value1, uint32_t value2) {
  
  uint32_t currentValue = 0;

  for(currentValue=value1; currentValue > value2; currentValue--) {
     Serial.print(currentValue);Serial.print(", ");Serial.print(value1);Serial.print(", ");Serial.println(value2);
      run(loopLength, currentValue);
  }

   //Serial.print(currentValue);Serial.print(", ");Serial.println(value2); 
}

void run(int loopLength, uint32_t value) {
    
  unsigned long start = millis();
  uint16_t result = 0;
  uint16_t truncValue = value >> SHIFT_BITS;
  //Serial.print("value=");Serial.print(value);Serial.print(", "); Serial.print("truncValue=");Serial.println(truncValue);
  int i=0;
  for (i=0;i<loopLength;i++) {
    result = sigmaDelta(value);
    //Serial.print("value=");Serial.print(value);Serial.print(", ");Serial.print("result=");Serial.println(result);
    tlc.setLED(0, result, result, result);    
    tlc.setLED(1, result, result, result);
    tlc.setLED(2, result, result, result);
    tlc.setLED(3, result, result, result);
    tlc.write();
    //delay(10);
  }
  //Serial.println(millis()-start);
}

uint16_t sigmaDeltaDebug(uint32_t input) {
  
  Serial.print("State = "); Serial.println(state);
  Serial.print("Input = "); Serial.println(input);

  uint32_t result;
  state += input;
  
  Serial.print("State + Input = "); Serial.println(state);
  
  result = state >> SHIFT_BITS;
  
  Serial.print("Result = "); Serial.println(result);
  
  state -= (result << SHIFT_BITS);
  
  Serial.print("State - Result = "); Serial.println(state);

  return (uint16_t)result;
}

uint16_t sigmaDelta(uint32_t input) {
  
  uint32_t result;
  state += input;
  result = state >> SHIFT_BITS;
  //Serial.print("Result = "); Serial.println(result);
  state -= (result << SHIFT_BITS);
  
  return (uint16_t)result;
}
