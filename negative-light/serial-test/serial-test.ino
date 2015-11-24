#include <SPI.h>
#include "Adafruit_TLC59711.h"

/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

 This example code is in the public domain.
 */
byte byteRead;
byte high;
byte low;

uint16_t max = 0xFFFF;

#define NUM_TLC59711 4

Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  tlc.begin();
  tlc.write();
  setAll(max,max,max);
}

// the loop routine runs over and over again forever:
void loop() {
  
  uint16_t r = 0, g = 0, b = 0;
  
  if (Serial.available()) {
      /* read the most recent byte */
      byteRead = Serial.read();
      /*ECHO the value that was read, back to the serial port. */
      Serial.write(byteRead);
      
      if (byteRead = 'r') {
        high = Serial.read();
        low = Serial.read();        
        r = high << 2 + low;
      }
      else if (byteRead = 'g') {
        high = Serial.read();
        low = Serial.read();
        g = high << 2 + low;  
      }
      else if (byteRead = 'b') {
        high = Serial.read();
        low = Serial.read();        
        b = high << 2 + low;
      }
    }
    
}

void setAll(uint16_t r, uint16_t g, uint16_t b) {
  for (uint16_t i = 0; i < 4 * NUM_TLC59711; i++) {
    tlc.setLED(i, r, b, g);
  }
  tlc.write();
}
