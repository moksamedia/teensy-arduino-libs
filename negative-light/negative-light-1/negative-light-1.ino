
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
#include <interp32.h>
#include <lib8tion.h>

// How many boards do you have chained?
#define NUM_TLC59711 4

Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711);

#define ITERP_STEPS 100
#define MAX_16_BITS  65534
#define DLT_TIME 1

Interp32 itrp(0, MAX_16_BITS, ITERP_STEPS);

Interp32 itrpSteps(100, 500, 100);


uint16_t PWM_GLOBAL = 0x7F;

void setAllPwm(uint16_t pwm) {
   int i;
  for (i=0;i<16;i++) {
     tlc.setPWM(i, pwm);
  } 
}

void setup() {
  //setAllPwm(PWM_GLOBAL);
  Serial.begin(9600);
  tlc.begin();
  tlc.write();
}

void loopRGB() {
  goUpItrpColorFactor(DLT_TIME, 1.0, 0.0, 0.0);
  goDownItrpColorFactor(DLT_TIME, 1.0, 0.0, 0.0);
  
  goUpItrpColorFactor(DLT_TIME, 0.0, 1.0, 0.0);  
  goDownItrpColorFactor(DLT_TIME, 0.0, 1.0, 0.0);
  
  goUpItrpColorFactor(DLT_TIME, 0.0, 0.0, 1.0);
  goDownItrpColorFactor(DLT_TIME, 0.0, 0.0, 1.0);
}


void loop() {
  uint16_t v = MAX_16_BITS;
  setAll(v, v, v);
}

void loop2 () {
  
  int i;
  
  uint32_t steps;
  
    for (i=0;i<100;i++) {
    
      uint16_t r = random16();
      uint16_t g = random16();
      uint16_t b = random16();
      
      steps = itrpSteps.smooth(i);
      
      Serial.print("steps = "); Serial.println(steps);
      
      itrp.setNumPoints(steps);    
  
      goUpItrpColor(DLT_TIME, r, g, b);
      goDownItrpColor(DLT_TIME, r, g, b);
    
  }
  
  for (i=100;i>=0;i--) {
  
    uint16_t r = random16();
    uint16_t g = random16();
    uint16_t b = random16();
    
    steps = itrpSteps.smooth(i);

     Serial.print("steps = "); Serial.println(steps);

    itrp.setNumPoints(steps);    

    goUpItrpColor(DLT_TIME, r, g, b);
    goDownItrpColor(DLT_TIME, r, g, b);
    
  }

}



void goUpItrpColorFactor(int dly, double rf, double gf, double bf) {
  uint16_t v;
  int i;
  for (i = 0; i < (int)itrp.getNumPoints(); i++) {
    v = itrp.smooth(i);
    setAll(v*rf, v*gf, v*bf);
    //Serial.print(i); Serial.print(", "); Serial.println(v);
    delay(dly);
  }

}

void goDownItrpColorFactor(int dly, double rf, double gf, double bf) {
  uint16_t v;
  int i;
  for (i = (int)itrp.getNumPoints()-1; i >= 0; i--) {
    v = itrp.smooth(i);
    setAll(v*rf, v*gf, v*bf);
    //Serial.print(i); Serial.print(", "); Serial.println(v);
    delay(dly);
  }

}

void goUpItrpColor(int dly, uint16_t r, uint16_t g, uint16_t b) {
  uint16_t v;
  int i;
  for (i = 0; i < (int)itrp.getNumPoints(); i++) {
    v = itrp.smooth(i);
    
    setAll(r*v/MAX_16_BITS, g*v/MAX_16_BITS, b*v/MAX_16_BITS);
    //Serial.print(i); Serial.print(", "); Serial.println(v);
    delay(dly);
  }

}

void goDownItrpColor(int dly, uint16_t r, uint16_t g, uint16_t b) {
  uint16_t v;
  int i;
  for (i = (int)itrp.getNumPoints()-1; i >= 0; i--) {
    v = itrp.smooth(i);
    setAll(r*v/MAX_16_BITS, g*v/MAX_16_BITS, b*v/MAX_16_BITS);
    //Serial.print(i); Serial.print(", "); Serial.println(v);
    delay(dly);
  }

}

void goUpItrp(int dly) {
  uint16_t v;
  int i;
  for (i = 0; i < (int)itrp.getNumPoints(); i++) {
    v = itrp.smooth(i);
    setAll(v, v, v);
    //Serial.print(i); Serial.print(", "); Serial.println(v);
    delay(dly);
  }

}

void goDownItrp(int dly) {
  uint16_t v;
  int i;
  for (i = (int)itrp.getNumPoints()-1; i >= 0; i--) {
    v = itrp.smooth(i);
    setAll(v, v, v);
    //Serial.print(i); Serial.print(", "); Serial.println(v);
    delay(dly);
  }

}

void setAll(uint16_t r, uint16_t g, uint16_t b) {
  for (uint16_t i = 0; i < 4 * NUM_TLC59711; i++) {
    tlc.setLED(i, r, b, g);
    tlc.write();
  }
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
    //Serial.println(i);
    delay(dly);
  }

}
