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
#define NUM_TLC5974 1

// How many boards do you have chained?
#define NUM_TLC59711 1

#define TLC59711_data   2
#define TLC59711_clock  3

Adafruit_TLC59711 bit16 = Adafruit_TLC59711(  NUM_TLC59711, 
                                              TLC59711_clock,
                                              TLC59711_data);
#define TLC5947_clock 5            
#define TLC5947_data 4           
#define TLC5947_latch 6
#define TLC5947_blank 7            

                                              
Adafruit_TLC5947 bit12 = Adafruit_TLC5947(  NUM_TLC5974, 
                                            TLC5947_clock, // clock
                                            TLC5947_data, // data
                                            TLC5947_latch);  // latch
                                              

Interp interp(0,1000,300);

void setup() {
  
  Serial.begin(9600);
  
  Serial.println("Dimming test");
  pinMode(10, OUTPUT);
  
  bit16.begin();
  bit16.write();
  
  bit12.begin();
  //pinMode(TLC5947_blank, OUTPUT);
  //digitalWrite(TLC5947_blank, LOW);
  
}

void loop() {
 
  bit12.setLED(4, 0, 0, 0);
  bit12.write();
      
  uint8_t wait = 100;
  int LED_NUM = 0;
  uint32_t i = 0, v = 0;
  uint16_t max = 300;
  
  Serial.println("16 bit UP");

  for (i=0;i<max;i+=1) {
    v = interp.slowAcc2(i);
      bit16.setLED(LED_NUM, v, v, v);
      bit16.write();
      Serial.print(i);Serial.print(" - ");Serial.println(v);
      delay(wait);
  }
  
  Serial.println("16 bit DN");

  i=max;
  
  for (i=max;i>=1;i-=1) {
    v = interp.slowDec2(i);
    bit16.setLED(LED_NUM, v, v, v);
    bit16.write();
    Serial.print(i);Serial.print(" - ");Serial.println(v);
    delay(wait);
  }
    
    /*
  Serial.println("12 bit UP");

  LED_NUM = 4;
  i=0;
  max = 100;
  
  for (i=0;i<max;i++) {
      bit12.setLED(LED_NUM, i, i, i);
      bit12.write();
      delay(wait);
  }
  
  Serial.println("12 bit DN");

  i=max;
  
  for (i=max;i>0;i--) {
    bit12.setLED(LED_NUM, i, i, i);
    bit12.write();
    delay(wait);
  }
  */
}

