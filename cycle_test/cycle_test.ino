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
#include "Adafruit_TLC5947.h"
#include <Interp.h>
#include <RGBConverter.h>
#include <SPI.h>



// How many boards do you have chained?
#define NUM_TLC59711 1

#define TLC59711_data   2
#define TLC59711_clock  3

//Adafruit_TLC59711 tlc = Adafruit_TLC59711(  NUM_TLC59711, TLC59711_clock, TLC59711_data);
Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711);
            
#define true 1
#define false 0

#define MAX_16_BITS 65535
#define MAX_20_BITS 262144
#define MAX_24_BITS 16777216
#define MAX_32_BITS 2147483647



int switcher = 0;
int counter = 0;
                                              
void setup() {
  
  Serial.begin(9600);
  
  Serial.println("Dimming test");
  pinMode(10, OUTPUT);
  
  tlc.begin();
  tlc.write();
  
}

void loop() {
  
  run (1000,1);
  run (1000,2);
  run (1000,3);
  run (1000,4);
  run (1000,5);
  run (1000,6);
  run (1000,7);
  run (1000,8);
  run (1000,9);
  run (1000,10);
 
}

void run(int loopLength, int modulo) {
    
  unsigned long start = millis();
  
  int i=0;
  for (i=0;i<loopLength;i++) {
    if (i % modulo == 0) {
      tlc.setLED(0, MAX_16_BIT, MAX_16_BIT, MAX_16_BIT);
      //switcher = false;    
    }
    else {
      tlc.setLED(0, 0, 0, 0);
      //switcher = true;
    }
    tlc.write();
  }
   Serial.println(millis()-start);
}

uint32_t state;

uint16_t sigmaDelta(uint32_t input) {
  
  uint16_t result;
  state += input;
  result = state >> 16;
  state -= result
  
}
