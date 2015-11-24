#include <spi4teensy3.h>

/***************************************************
  This is an example for our Adafruit 12-channel PWM/LED driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/

  These drivers uses SPI to communicate, 2 pins are required to
  interface: Data and Clock. The boards are chainable

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_TLC59711.h"
#include <SPI.h>
#include <Interp32.h>
#include <Interp.h>
#include "arrays.h"


// How many boards do you have chained?
#define NUM_TLC59711 4

#define data   3
#define clock  4

//Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711, clock, data);
Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711);

#define ITERP_STEPS 1000
#define MAX_16_BITS  65535
#define DLT_TIME 5

Interp32 itrp(0, MAX_16_BITS, ITERP_STEPS);

double rW = 1.0;
double gW = 0.55;
double bW = 0.7;
 
//uint8_t green = 69;
//uint8_t blue = 88;

uint8_t green = 79;
uint8_t blue = 98;

void setup() {
   //Serial.begin(9600);
  //Serial.println("TLC59711 test");
  //tlc.setCommandOptions(0,1,1,0,1);
  //setAllPwm(PWM_GLOBAL);
  
  tlc.setGlobalBrightnessRed(127);
  tlc.setGlobalBrightnessGreen(69);
  tlc.setGlobalBrightnessBlue(88);

  tlc.begin();
  tlc.write();
}

void loopx() {
  
  int max = 200;
  int i;
  uint16_t v;
  for (i=0;i<max;i++) {
    v = smooth32767_200[i];
    //Serial.print("i = ");Serial.print(i);Serial.print(", v = ");Serial.println(v);
    setAll(v,v,v);
    delay(10);
  }
}

void loopy() {
  loopUpAndDown();
}

void loop() {
   runCheck();
   green--;
   blue--;
   tlc.setGlobalBrightnessGreen(green);
   tlc.setGlobalBrightnessBlue(blue);
}

void runCheck() {
  
  Serial.print("BCr = ");Serial.println(tlc.getGlobalBrightnessRed());
  Serial.print("BCg = ");Serial.println(tlc.getGlobalBrightnessGreen());
  Serial.print("BCb = ");Serial.println(tlc.getGlobalBrightnessBlue());
    //setAll(round(MAX_16_BITS*rW), round(MAX_16_BITS*gW),round(MAX_16_BITS*bW));
    setAll(MAX_16_BITS, MAX_16_BITS,MAX_16_BITS);
  delay(1000);
}


void allOn() {
  
  uint16_t v = MAX_16_BITS/2;
  
  for (uint16_t i = 0; i < 16; i++) {
    tlc.setLED(i, v, v, v);
    tlc.write();
  }

  delay(3000);

}

void loopx1() {
  //Serial.print("COMMAND_OPTS = ");Serial.println(tlc.COMMAND_OPTIONS, HEX);
  goDownItrp(DLT_TIME);
  goUpItrp(DLT_TIME);
}

void loopUpAndDown() {
 // Serial.print("COMMAND_OPTS = ");Serial.println(tlc.COMMAND_OPTIONS, HEX);
   goDown(MAX_16_BITS,DLT_TIME);
  //goUp(MAX_16_BITS,DLT_TIME);
}


void goUp(int max, int dly) {
  int i;
  for (i = 0; i < max; i += 1) {
    setAll(i, i, i);
    Serial.println(i);
    delay(dly);
  }

}

void goDown(int max, int dly) {
  int i;
  for (i = max; i >= 0; i -= 1) {
    setAll(i, i, i);
    Serial.println(i);
    delay(dly);
  }

}

void goUpItrp(int dly) {
  uint16_t v;
  int i;
  for (i = 0; i < ITERP_STEPS; i++) {
    v = itrp.slowAcc3(i);
    setAll(v, v, v);
    Serial.print(i); Serial.print(", "); Serial.println(v);
    delay(dly);
  }

}

void goDownItrp(int dly) {
  uint16_t v;
  int i;
  for (i = ITERP_STEPS-1; i >= 0; i--) {
    v = itrp.slowAcc3(i);
    setAll(v, v, v);
    Serial.print(i); Serial.print(", "); Serial.println(v);
    delay(dly);
  }

}

void sequencery() {
  
  uint16_t v = MAX_16_BITS/2;
  
  for (uint16_t i = 0; i < 16; i++) {
    setAll(0,0,0);
    tlc.setLED(i, v, v, v);
    tlc.setLED(i+1, v/100, v/100, v/100);
    tlc.write();
    //Serial.print("i = ");Serial.println(i);
    delay(500);
  }
 
}


void orderLedsHelper() {
  
  uint16_t v = MAX_16_BITS/2;
  
  for (uint16_t i = 0; i < 16; i++) {
    setAll(0,0,0);
    tlc.setLED(i, v, v, v);
    tlc.setLED(i+1, v/100, v/100, v/100);
    tlc.write();
    Serial.print("i = ");Serial.println(i);
    delay(5000);
  }
 
}

void setAll(uint16_t r, uint16_t g, uint16_t b) {
  for (uint16_t i = 0; i < 4 * NUM_TLC59711; i++) {
    tlc.setLED(i, r, b, g);
  }
  tlc.write();
}

