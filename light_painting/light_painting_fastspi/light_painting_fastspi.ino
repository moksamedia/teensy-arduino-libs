#include <FastSPI_LED.h>

#define NUM_LEDS 42

// Sometimes chipsets wire in a backwards sort of way
struct CRGB { unsigned char b; unsigned char r; unsigned char g; };
// struct CRGB { unsigned char r; unsigned char g; unsigned char b; };
struct CRGB *leds;

#define PIN 6

int counter = 0;

void setup()
{
  FastSPI_LED.setLeds(NUM_LEDS);
  FastSPI_LED.setChipset(CFastSPI_LED::SPI_WS2811);


  FastSPI_LED.setPin(PIN);
  
  FastSPI_LED.init();
  FastSPI_LED.start();

  leds = (struct CRGB*)FastSPI_LED.getRGBData(); 
}

void loop() { 
  
  
  // Fade in/fade out
  for(int j = 0; j < 3; j++ ) { 
    memset(leds, 0, NUM_LEDS * 3);
    for(int k = 0; k < 80; k++) { 
      for(int i = 0; i < NUM_LEDS; i+=2 ) {
        switch(j) { 
          case 0: leds[i].r = k; break;
          case 1: leds[i].g = k; break;
          case 2: leds[i].b = k; break;
        }
      }
      FastSPI_LED.show();
      delay(50);
    }
    delay(800);
    for(int k = 80; k >= 0; k--) { 
      for(int i = 0; i < NUM_LEDS; i+=2 ) {
        switch(j) { 
          case 0: leds[i].r = k; break;
          case 1: leds[i].g = k; break;
          case 2: leds[i].b = k; break;
        }
      }
      FastSPI_LED.show();
      delay(50);
    }
    delay(800);
  }
}

