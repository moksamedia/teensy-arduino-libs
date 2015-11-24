#include <Oscillator.h>
#include <Interp.h>
#include <RGBConverter.h>

float brightness = 0.3;

/*  OctoWS2811 Rainbow.ino - Rainbow Shifting Test
 http://www.pjrc.com/teensy/td_libs_OctoWS2811.html
 Copyright (c) 2013 Paul Stoffregen, PJRC.COM, LLC
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 
 Required Connections
 --------------------
 pin 2:  LED Strip #1    OctoWS2811 drives 8 LED Strips.
 pin 14: LED strip #2    All 8 are the same length.
 pin 7:  LED strip #3
 pin 8:  LED strip #4    A 100 ohm resistor should used
 pin 6:  LED strip #5    between each Teensy pin and the
 pin 20: LED strip #6    wire to the LED strip, to minimize
 pin 21: LED strip #7    high frequency ringining & noise.
 pin 5:  LED strip #8
 pin 15 & 16 - Connect together, but do not use
 pin 4 - Do not use
 pin 3 - Do not use as PWM.  Normal use is ok.
 pin 1 - Output indicating CPU usage, monitor with an oscilloscope,
 logic analyzer or even an LED (brighter = CPU busier)
 
 https://github.com/ratkins/RGBConverter
 
 */

#include <OctoWS2811.h>


unsigned int House[8][35] = {
  0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,
  1,0,0,0,1, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,
  1,0,0,0,1, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,
  1,0,0,0,1, 0,0, 0,1,1,1,0, 0,0, 1,0,0,0,1, 0,0, 0,1,1,1,1, 0,0, 0,1,1,1,0, 0,0,
  1,1,1,1,1, 0,0, 1,0,0,0,1, 0,0, 1,0,0,0,1, 0,0, 1,0,0,0,0, 0,0, 1,0,0,0,1, 0,0,
  1,0,0,0,1, 0,0, 1,0,0,0,1, 0,0, 1,0,0,0,1, 0,0, 0,1,1,1,0, 0,0, 1,1,1,1,1, 0,0,
  1,0,0,0,1, 0,0, 1,0,0,0,1, 0,0, 1,0,0,0,1, 0,0, 0,0,0,0,1, 0,0, 1,0,0,0,0, 0,0, 
  1,0,0,0,1, 0,0, 0,1,1,1,0, 0,0, 0,1,1,1,1, 0,0, 1,1,1,1,0, 0,0, 0,1,1,1,1, 0,0 
};

unsigned int Music[8][35] = {
  0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,
  1,0,0,0,1, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,
  1,1,0,1,1, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,1,0,0, 0,0, 0,0,0,0,0, 0,0,
  1,0,1,0,1, 0,0, 1,0,0,0,1, 0,0, 0,1,1,1,1, 0,0, 1,1,1,0,0, 0,0, 0,1,1,1,1, 0,0,
  1,0,0,0,1, 0,0, 1,0,0,0,1, 0,0, 1,0,0,0,0, 0,0, 0,0,1,0,0, 0,0, 1,0,0,0,0, 0,0,
  1,0,0,0,1, 0,0, 1,0,0,0,1, 0,0, 0,1,1,1,0, 0,0, 0,0,1,0,0, 0,0, 1,0,0,0,0, 0,0,
  1,0,0,0,1, 0,0, 1,0,0,0,1, 0,0, 0,0,0,0,1, 0,0, 0,0,1,0,0, 0,0, 1,0,0,0,0, 0,0, 
  1,0,0,0,1, 0,0, 0,1,1,1,1, 0,0, 1,1,1,1,0, 0,0, 1,1,1,1,1, 0,0, 0,1,1,1,1, 0,0 
};

unsigned int HouseMusic[8][72] = {
  0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,
  1,0,0,0,1, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,0,0, 1,0,0,0,1, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,
  1,0,0,0,1, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,0,0, 1,1,0,1,1, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,1,0,0, 0,0, 0,0,0,0,0, 0,0,
  1,0,0,0,1, 0,0, 0,1,1,1,0, 0,0, 1,0,0,0,1, 0,0, 0,1,1,1,1, 0,0, 0,1,1,1,0, 0,0,0,0, 1,0,1,0,1, 0,0, 1,0,0,0,1, 0,0, 0,1,1,1,1, 0,0, 1,1,1,0,0, 0,0, 0,1,1,1,1, 0,0,
  1,1,1,1,1, 0,0, 1,0,0,0,1, 0,0, 1,0,0,0,1, 0,0, 1,0,0,0,0, 0,0, 1,0,0,0,1, 0,0,0,0, 1,0,0,0,1, 0,0, 1,0,0,0,1, 0,0, 1,0,0,0,0, 0,0, 0,0,1,0,0, 0,0, 1,0,0,0,0, 0,0,
  1,0,0,0,1, 0,0, 1,0,0,0,1, 0,0, 1,0,0,0,1, 0,0, 0,1,1,1,0, 0,0, 1,1,1,1,1, 0,0,0,0, 1,0,0,0,1, 0,0, 1,0,0,0,1, 0,0, 0,1,1,1,0, 0,0, 0,0,1,0,0, 0,0, 1,0,0,0,0, 0,0,
  1,0,0,0,1, 0,0, 1,0,0,0,1, 0,0, 1,0,0,0,1, 0,0, 0,0,0,0,1, 0,0, 1,0,0,0,0, 0,0,0,0, 1,0,0,0,1, 0,0, 1,0,0,0,1, 0,0, 0,0,0,0,1, 0,0, 0,0,1,0,0, 0,0, 1,0,0,0,0, 0,0,
  1,0,0,0,1, 0,0, 0,1,1,1,0, 0,0, 0,1,1,1,1, 0,0, 1,1,1,1,0, 0,0, 0,1,1,1,1, 0,0,0,0, 1,0,0,0,1, 0,0, 0,1,1,1,1, 0,0, 1,1,1,1,0, 0,0, 1,1,1,1,1, 0,0, 0,1,1,1,1, 0,0
};

unsigned int House_Small[8][26] = {
  0, 0,0,0,0, 0, 0,0,0,0, 0, 0,0,0,0, 0, 0,0,0,0, 0, 0,0,0,0, 0,
  0, 1,0,0,1, 0, 0,0,0,0, 0, 0,0,0,0, 0, 0,0,0,0, 0, 0,0,0,0, 0,
  0, 1,0,0,1, 0, 0,0,0,0, 0, 0,0,0,0, 0, 0,0,0,0, 0, 0,0,0,0, 0,
  0, 1,0,0,1, 0, 0,1,1,0, 0, 1,0,0,1, 0, 0,1,1,1, 0, 0,1,1,0, 0,
  0, 1,1,1,1, 0, 1,0,0,1, 0, 1,0,0,1, 0, 1,0,0,0, 0, 1,0,0,1, 0,
  0, 1,0,0,1, 0, 1,0,0,1, 0, 1,0,0,1, 0, 0,1,1,0, 0, 1,1,1,1, 0,
  0, 1,0,0,1, 0, 1,0,0,1, 0, 1,0,0,1, 0, 0,0,0,1, 0, 1,0,0,0, 0,
  0, 1,0,0,1, 0, 0,1,1,0, 0, 0,1,1,1, 0, 1,1,1,0, 0, 0,1,1,1, 0
};

unsigned int Music_Small[8][26] = {
  0, 0,0,0,0,0, 0, 0,0,0,0, 0, 0,0,0,0, 0, 0,0,0, 0, 0,0,0,0, 0,
  0, 1,0,0,0,1, 0, 0,0,0,0, 0, 0,0,0,0, 0, 0,1,0, 0, 0,0,0,0, 0,
  0, 1,1,0,1,1, 0, 0,0,0,0, 0, 0,0,0,0, 0, 0,0,0, 0, 0,0,0,0, 0,
  0, 1,0,1,0,1, 0, 1,0,0,1, 0, 0,1,1,1, 0, 1,1,0, 0, 0,1,1,1, 0,
  0, 1,0,0,0,1, 0, 1,0,0,1, 0, 1,0,0,0, 0, 0,1,0, 0, 1,0,0,0, 0,
  0, 1,0,0,0,1, 0, 1,0,0,1, 0, 0,1,1,0, 0, 0,1,0, 0, 1,0,0,0, 0,
  0, 1,0,0,0,1, 0, 1,0,0,1, 0, 0,0,0,1, 0, 0,1,0, 0, 1,0,0,0, 0,
  0, 1,0,0,0,1, 0, 0,1,1,1, 0, 1,1,1,0, 0, 1,1,1, 0, 0,1,1,1, 0
};

unsigned int Blue_Small[8][26] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,0,0,0,
  0,0,0,0,1,1,1,0,0,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,
  0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,1,1,1,1,0,0,0,0,
  0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,
  0,0,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,0,0
};

unsigned int Bar_Small_Size = 26;
unsigned int Bar_Small[8][26] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,1,0,0,1,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,0,
  0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,
  0,0,0,0,0,0,1,0,0,1,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,1,0,1,0,0,0,0,0,0,0,0
};

unsigned int BlueBar_Size = 49;
unsigned int BlueBar[8][49] = {
  0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0,
  1,1,1,1,0, 0,0, 1,1,1,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0, 1,1,1,1,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0,
  1,0,0,0,1, 0,0, 0,0,1,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0, 0,0, 1,0,0,0,1, 0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0,
  1,0,0,0,1, 0,0, 0,0,1,0,0, 0,0, 1,0,0,0,1, 0,0, 0,1,1,1,0, 0,0, 0,0, 1,0,0,0,1, 0,0, 0,1,1,1,0, 0,0, 1,1,1,1,0,
  1,1,1,1,0, 0,0, 0,0,1,0,0, 0,0, 1,0,0,0,1, 0,0, 1,0,0,0,1, 0,0, 0,0, 1,1,1,1,0, 0,0, 0,0,0,0,1, 0,0, 1,0,0,0,1,
  1,0,0,0,1, 0,0, 0,0,1,0,0, 0,0, 1,0,0,0,1, 0,0, 1,1,1,1,1, 0,0, 0,0, 1,0,0,0,1, 0,0, 0,1,1,1,1, 0,0, 1,0,0,0,0,
  1,0,0,0,1, 0,0, 0,0,1,0,0, 0,0, 1,0,0,0,1, 0,0, 1,0,0,0,0, 0,0, 0,0, 1,0,0,0,1, 0,0, 1,0,0,0,1, 0,0, 1,0,0,0,0,
  1,1,1,1,0, 0,0, 1,1,1,1,1, 0,0, 0,1,1,1,1, 0,0, 0,1,1,1,1, 0,0, 0,0, 1,1,1,1,0, 0,0, 0,1,1,1,0, 1,0, 1,0,0,0,0
};



const int ledsPerStrip = 66;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

int rainbowColors[180];


void setup() {
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
  for (int i=0; i<180; i++) {
    int hue = i * 2;
    int saturation = 80;
    int lightness = 10;
    // pre-compute the 180 rainbow colors
    rainbowColors[i] = makeColor(hue, saturation, lightness);
  }
  digitalWrite(1, LOW);
  leds.begin();
  Serial.begin(9600);  
}

byte colorWheel = 0;

void incColorWheel() {

  colorWheel++;

  if (colorWheel >= 255) {
    colorWheel = 0; 
  }

}

void loop() {

  int num;
  int MAX = 10;
    
  num = random_in_range(0,14);
  
  switch(num) {
  
    case 0:
    case 12:
    case 13:
      randomBlueBar();
      break;

    case 1:
      randomHouseMusicInterp();
      break;
      
    case 2:
      colorShiftingScroller();
      break;
      
    case 3:
      colorShiftingFlasher();
      break;
      
    case 4:
      nightRider(50);
      break;

    case 5:
      rainbowAnim();
      break;
      
    case 6:
      smoothBlinky(); 
      break;
      
    case 7:
      blueBarAnim1();
      break;
      
    case 8:
      randomLoop();
      break;
      
    case 9:
      randomHouseMusic();
      break;

    case 10:
      blueBarAnim2();
      break;
      
    case 11:
      flashAnim(); 
      break;
    default:
      randomBlueBar();
      break;
  }
  
}

void flashAnim() {
  flash(50000, 50, color(125,125,125), color(0,0,0));
  flash(50000, 50, color(0,0,125), color(0,0,0));
  flash(50000, 50, color(125,0,0), color(0,0,0));
  flash(50000, 50, color(125,0,125), color(0,0,0));
  flash(50000, 50, color(0,0,125), color(0,0,0));
  flash(50000, 50, color(125,125,125), color(0,0,0));
  flash(50000, 50, color(0,0,125), color(0,0,0));
  flash(50000, 50, color(125,0,0), color(0,0,0));
  flash(50000, 50, color(125,0,125), color(0,0,0));
  flash(50000, 50, color(0,0,125), color(0,0,0)); 
}

void rainbowAnim() {
   rainbow(0, 2500);
  rainbow(1, 2500);
  rainbow(2, 1250);
  rainbow(3, 1250);
  rainbow(5, 650);
  rainbow(7, 650);
  rainbow(10, 650);
  rainbow(10, 650);
  rainbow(10, 325);
  rainbow(10, 325);
  rainbow(10, 325);
  rainbow(10, 325);
  rainbow(12, 250);
  rainbow(14, 250);
  rainbow(16, 200);
  rainbow(18, 150);
  rainbow(20, 150);
  rainbow(20, 100);
  rainbow(20, 100);
  rainbow(20, 100);
  rainbow(20, 100);
  rainbow(20, 100);
  rainbow(20, 100);
  rainbow(20, 50);
  rainbow(20, 50);
  rainbow(20, 50);
  rainbow(20, 50);
  rainbow(20, 50);
  rainbow(20, 50);
  rainbow(20, 50);
  rainbow(20, 50);
  rainbow(20, 50); 
}

void colorShiftingScroller() {

  Interp * interp = new Interp(0,359,500);
  Interp * interp2 = new Interp(2000,80000,500);
  int i;
  for (i=0;i<500;i++) {
    flashOffset(interp2->smooth2(i), i, 2, makeColor(interp->linear(i), 80, 30), color(0,0,0));
  }
  for (;i>=0;i--) {
    flashOffset(interp2->smooth2(i), i, 2, makeColor(interp->linear(i), 80, 30), color(0,0,0));
  }

  delete interp, interp2;
}

void colorShiftingFlasher() {

  Interp * interp = new Interp(0,359,500);
  int i;
  for (i=0;i<500;i++) {
    flashOffset(80000, i, 5, makeColor(interp->linear(i), 80, 30), color(0,0,0));
  }

  delete interp;
}


void flashOffset(int delay, int offset, int spacing, unsigned int onColor, unsigned int offColor) {
  int y, x;
  // Iterate over the rows
  for (y=0;y<8;y++) {

    // Iterate through the columns
    for (x=0;x<ledsPerStrip;x++) {

      if ( (x + offset) % spacing == 0 ) {
        leds.setPixel(x + y*ledsPerStrip, onColor);
      }
      else {
        leds.setPixel(x + y*ledsPerStrip, offColor);
      }
    }
  } 

  leds.show();
  delayMicroseconds(delay);

  // Iterate over the rows
  for (y=0;y<8;y++) {

    // Iterate through the columns
    for (x=0;x<ledsPerStrip;x++) {

      if ( (x + offset) % spacing == 0 ) {
        leds.setPixel(x + y*ledsPerStrip, offColor);
      }
      else {
        leds.setPixel(x + y*ledsPerStrip, onColor);
      }
    }
  } 

  leds.show();
  delayMicroseconds(delay);
}

void randomLoop() {

  int cycleMax = 500;
  int offset;

  for (int j=0;j<3;j++) {

    for (int c = 0; c < cycleMax; c++) {
      offset = random_in_range(0, ledsPerStrip*8);
      leds.setPixel(offset, randomColor());
      leds.show();
      delayMicroseconds(50000);
    }

    turnAllOff();

  }
}

void smoothBlinky() {

  int j,i,hue,brightness,color;

  turnAllOff();
  leds.show();

  Interp * interp = new Interp(0,30,175);

  for (j=0;j<60;j++) {
    
    hue = Interp::SMOOTH(0,359,60,j);
    
    for (i=0;i<175;i++) {
      brightness =interp->smooth(i);
      color = makeColor(hue,70,brightness);
      setAllPixels(color);
      leds.show();
    }

    j++;
    //hue = smooth(0,359,60,j);
    for (;i>=0;i--) {
      brightness =interp->smooth(i);
      color = makeColor(hue,70,brightness);
      setAllPixels(color);
      leds.show(); 
    }

  }

  delete interp;

}


void fadeInOut() {

  int i,v;

  turnAllOff();
  leds.show();

  Interp * interp = new Interp(0,175,175);

  for (i=0;i<175;i++) {
    v = interp->smooth(i);
    setAllPixels(color(v,v,v));
    leds.show();
  }
  for (;i>=0;i--) {
    v = interp->smooth(i);
    setAllPixels(color(v,v,v));
    leds.show(); 
  }

  delete interp;

}

int randomColor() {
  return color(random_in_range(0,255),random_in_range(0,255),random_in_range(0,255));
}

void randomBlueBar() {

  int offset;

  int cycleMax = 50;

  for (int j=0;j<3;j++) {

    for (int c = 0; c < cycleMax; c++) {

      offset = random_in_range(0, ledsPerStrip-26);
      if ( c >= cycleMax - 15) {
        offset = random_in_range(10, 30);
      }
      if ( c >= cycleMax - 5) {
        offset = random_in_range(18, 22);
      }
      if ( c == cycleMax - 1) offset = 20;

      drawArrayForTime(&Blue_Small[0][0], 26, offset, color(0,0,125), color(0,0,0), 250000/cycleMax*c);

      offset = random_in_range(0, ledsPerStrip-26);
      if ( c >= cycleMax - 15) {
        offset = random_in_range(10, 30);
      }
      if ( c >= cycleMax - 5) {
        offset = random_in_range(18, 22);
      }
      if ( c == cycleMax -1) offset = 20;
      drawArrayForTime(&Bar_Small[0][0], 26, offset, color(0,0,125), color(0,0,0), 250000/cycleMax*c);

    }

  }

}

void randomHouseMusic() {

  int offset;

  int cycleMax = 50;

  Interp * interp = new Interp(0,359,cycleMax);

  for (int j=0;j<3;j++) {

    for (int c = 0; c < cycleMax; c++) {

      offset = random_in_range(0, ledsPerStrip-26);
      if ( c >= cycleMax - 15) {
        offset = random_in_range(10, 30);
      }
      if ( c >= cycleMax - 5) {
        offset = random_in_range(18, 22);
      }
      if ( c == cycleMax - 1) offset = 20;

      drawArrayForTime(&House_Small[0][0], 26, offset, makeColor(random_in_range(0,359),80,30), color(0,0,0), 250000/cycleMax*c);

      offset = random_in_range(0, ledsPerStrip-26);
      if ( c >= cycleMax - 15) {
        offset = random_in_range(10, 30);
      }
      if ( c >= cycleMax - 5) {
        offset = random_in_range(18, 22);
      }
      if ( c == cycleMax -1) offset = 20;
      drawArrayForTime(&Music_Small[0][0], 26, offset, makeColor(random_in_range(0,359),80,30), color(0,0,0), 250000/cycleMax*c);

      flash(makeColor(random_in_range(0,359),80,30), 250000/cycleMax*c);

    }

  }

  delete interp;

}


void randomHouseMusicInterp() {

  int offset;

  int cycleMax = 50;

  Interp * interp = new Interp(0,359,cycleMax);

  for (int j=0;j<3;j++) {

    for (int c = 0; c < cycleMax; c++) {

      offset = random_in_range(0, ledsPerStrip-26);
      if ( c >= cycleMax - 15) {
        offset = random_in_range(10, 30);
      }
      if ( c >= cycleMax - 5) {
        offset = random_in_range(18, 22);
      }
      if ( c == cycleMax - 1) offset = 20;

      drawArrayForTime(&House_Small[0][0], 26, offset, makeColor(interp->smooth(c),80,30), color(0,0,0), 250000/cycleMax*c);

      offset = random_in_range(0, ledsPerStrip-26);
      if ( c >= cycleMax - 15) {
        offset = random_in_range(10, 30);
      }
      if ( c >= cycleMax - 5) {
        offset = random_in_range(18, 22);
      }
      if ( c == cycleMax -1) offset = 20;
      drawArrayForTime(&Music_Small[0][0], 26, offset, makeColor(interp->smooth(c),80,30), color(0,0,0), 250000/cycleMax*c);

      flash(makeColor(interp->smooth(c),80,30), 250000/cycleMax*c);

    }

  }

  delete interp;

}

int color(uint8_t red, uint8_t green, uint8_t blue) {

  red = red * brightness;
  green = green * brightness;
  blue = blue * brightness;

  return (red << 16) | (green << 8) | blue;
}

void nightRider(unsigned int count) {

  for (int i=0;i<count;i++) {
    nightRider_helper(); 
  }

}

void turnAllOff() {
  for (int i=0;i<ledsPerStrip;i++) {
    setPixelsAllRows(i,color(0,0,0));
  }
}

void setAllPixels(int color) {
  for (int i=0;i<ledsPerStrip;i++) {
    setPixelsAllRows(i,color);
  }
}

void nightRider_helper() {

  int i = 0;
  int pos = 0;

  Interp * interp = new Interp(0,ledsPerStrip,ledsPerStrip);

  for (i=0;i<ledsPerStrip;i++) {

    turnAllOff();

    unsigned int color = Wheel(colorWheel);

    Serial.print(colorWheel);

    pos = i;

    setPixelsAllRows(pos, color);
    setPixelsAllRows(pos+1, color);
    setPixelsAllRows(pos-1, color);

    setPixelsAllRows(ledsPerStrip - pos, color);
    setPixelsAllRows(ledsPerStrip - pos+1, color);
    setPixelsAllRows(ledsPerStrip - pos-1, color);

    leds.show();
    delayMicroseconds(8000);
    incColorWheel();

  }

  for (;i>=0;i--) {

    turnAllOff();

    unsigned int color = Wheel(colorWheel);

    pos = i;

    setPixelsAllRows(pos, color);
    setPixelsAllRows(pos+1, color);
    setPixelsAllRows(pos-1, color);

    setPixelsAllRows(ledsPerStrip - pos, color);
    setPixelsAllRows(ledsPerStrip - pos+1, color);
    setPixelsAllRows(ledsPerStrip - pos-1, color);

    leds.show(); 
    delayMicroseconds(8000);
    incColorWheel();
  }

  delete interp;

}

void setPixelsAllRows(unsigned int offset, unsigned int color) {

  if (offset < 0 || offset >= ledsPerStrip) {
    return; 
  }

  for (int i=0;i<8;i++) {
    leds.setPixel(offset + i*ledsPerStrip, color);
  }
}


void flash(int delay, int repititions, unsigned int onColor, unsigned int offColor) {

  int x, y;

  for (int i = 0; i < repititions; i++) {

    // Iterate over the rows
    for (y=0;y<8;y++) {

      // Iterate through the columns
      for (x=0;x<ledsPerStrip;x++) {

        if ( (x + i) % 5 == 0 ) {
          leds.setPixel(x + y*ledsPerStrip, onColor);
        }
        else {
          leds.setPixel(x + y*ledsPerStrip, offColor);
        }
      }
    } 

    leds.show();
    delayMicroseconds(delay);

    // Iterate over the rows
    for (y=0;y<8;y++) {

      // Iterate through the columns
      for (x=0;x<ledsPerStrip;x++) {

        if ( (x + i) % 5 == 0 ) {
          leds.setPixel(x + y*ledsPerStrip, offColor);
        }
        else {
          leds.setPixel(x + y*ledsPerStrip, onColor);
        }
      }
    } 

    leds.show();
    delayMicroseconds(delay);
  }
}


/*
int interp(int min, int max, int val) {
 float ival = (max - min) / (val - min);
 float y = pow(ival, 2);
 return round(y * (max-min) + min);
 }
 */


void drawHouse(unsigned int delay, int col) {
  drawArrayForTime(&House_Small[0][0], 26, 20, col, color(0,0,0), delay);
}

void drawMusic(unsigned int delay, int col) {
  drawArrayForTime(&Music_Small[0][0], 26, 20, col, color(0,0,0), delay);
}

void blueBarAnim1() {  

  for (int i = 0; i < 15; i++) {

    flash(color(255,255,255), 100);
    scrollTextRL(&BlueBar[0][0], 49, 200);
    flash(color(255,255,255), 100);
    scrollTextLR(&BlueBar[0][0], 49, 200);
    drawBlue(500000);
    flash(color(255,255,255), 100);
    scrollTextRL(&BlueBar[0][0], 49, 200);
    flash(color(255,255,255), 100);
    scrollTextLR(&BlueBar[0][0], 49, 200);
    drawBar(500000);
    flash(color(255,255,255), 100);
  }
}

void quickStrobe() {
  int flashColor = color(100,100,175);
  flash(flashColor, 10000);
  flash(color(0,0,0), 50000);
  flash(flashColor, 10000);
  flash(color(0,0,0), 50000);
  flash(flashColor, 10000);
  flash(color(0,0,0), 50000);
  flash(flashColor, 10000);
  flash(color(0,0,0), 50000);
  flash(flashColor, 10000); 
  turnAllOff();
}

void blueBarAnim2() {  


  for (int i = 0; i < 15; i++) {

    quickStrobe();
    drawBlue(500000);   
    quickStrobe();
    drawBar(500000);
  }
}

void flash(int color, unsigned int delay) {
  setAll(color);
  leds.show();
  delayMicroseconds(delay); 
}

void setAll(int color) {
  for (int i=0;i<8;i++) {
    for (int j=0;j<ledsPerStrip;j++) {
      leds.setPixel(j + i*ledsPerStrip, color);
    }
  } 
}

void drawBlueBar(unsigned int delay) {
  drawBlue(delay);
  drawBar(delay);
}

void drawBlue(unsigned int delay) {
  drawArrayForTime(&Blue_Small[0][0], 26, 20, color(0,0,125), color(0,0,0), delay);
}

void drawBar(unsigned int delay) {
  drawArrayForTime(&Bar_Small[0][0], 26, 20, color(0,0,125), color(0,0,0), delay);
}

void scrollTextRL(unsigned int * array, int arraySize, unsigned int delay) {
  int offset;

  /*
   *  Start with left edge of text at far right edge, just off, of
   *  LED board. We decrement this offset until all of the text
   *  has been shown.
   */

  for (offset = ledsPerStrip ; offset > -arraySize ; offset--) {

    drawArray(array, arraySize, offset, color(0,0,125), color(0,0,0));   

    leds.show();
    delayMicroseconds(delay);
  }

}

void scrollTextLR(unsigned int * array, int arraySize, unsigned int delay) {
  int offset;

  /*
   *  Start with left edge of text at far right edge, just off, of
   *  LED board. We decrement this offset until all of the text
   *  has been shown.
   */

  for (offset = -arraySize ; offset < ledsPerStrip ; offset++) {

    drawArray(array, arraySize, offset, color(0,0,125), color(0,0,0));   

    leds.show();
    delayMicroseconds(delay);
  }

}

void drawArrayForTime(unsigned int * array, int arraySize, int offset, unsigned int onColor, unsigned int offColor, unsigned int delay) {
  drawArray(array, arraySize, offset, onColor, offColor);
  leds.show();
  delayMicroseconds(delay);
}

void drawArray(unsigned int * array, int arraySize, int offset, unsigned int onColor, unsigned int offColor) {

  int x, y, val;

  // Iterate over the rows
  for (y=0;y<8;y++) {

    // Iterate through the columns
    for (x=0;x<ledsPerStrip;x++) {

      val = offsetArray(x,y,offset,array,arraySize);

      if ( val == 1 ) {
        leds.setPixel(x + y*ledsPerStrip, onColor);
      }
      else {
        leds.setPixel(x + y*ledsPerStrip, offColor);
      }
    }
  }
}

int offsetArray(int x, int y, int offset, unsigned int * array, int arraySize) {
  if (x < offset) {
    return 0;
  }
  else if (x >= offset + arraySize) {
    return 0;
  }
  else {
    return *(array + y * arraySize + x - offset); 
  }
}

// phaseShift is the shift between each row.  phaseShift=0
// causes all rows to show the same colors moving together.
// phaseShift=180 causes each row to be the opposite colors
// as the previous.  
//
// cycleTime is the number of milliseconds to shift through
// the entire 360 degrees of the color wheel:
// Red -> Orange -> Yellow -> Green -> Blue -> Violet -> Red
//
void rainbow(int phaseShift, int cycleTime)
{
  int color, x, y, offset, wait;

  wait = cycleTime * 1000 / ledsPerStrip;
  for (color=0; color < 180; color++) {
    digitalWrite(1, HIGH);
    for (x=0; x < ledsPerStrip; x++) {
      for (y=0; y < 8; y++) {
        int index = (color + x + y*phaseShift/2) % 180;
        leds.setPixel(x + y*ledsPerStrip, rainbowColors[index]);
      }
    }
    leds.show();
    digitalWrite(1, LOW);
    delayMicroseconds(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.


unsigned int Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

/* Would like a semi-open interval [min, max) */
int random_in_range (unsigned int min, unsigned int max)
{
  int base_random = rand(); /* in [0, RAND_MAX] */
  if (RAND_MAX == base_random) return random_in_range(min, max);
  /* now guaranteed to be in [0, RAND_MAX) */
  int range       = max - min,
  remainder   = RAND_MAX % range,
  bucket      = RAND_MAX / range;
  /* There are range buckets, plus one smaller interval
   within remainder of RAND_MAX */
  if (base_random < RAND_MAX - remainder) {
    return min + base_random/bucket;
  } 
  else {
    return random_in_range (min, max);
  }
}



