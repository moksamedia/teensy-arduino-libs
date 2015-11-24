/***************************************************
 This is a library for our Adafruit 24-channel PWM/LED driver
 
 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/products/1455
 
 These drivers uses SPI to communicate, 3 pins are required to
 interface: Data, Clock and Latch. The boards are chainable
 
 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!
 
 Written by Limor Fried/Ladyada for Adafruit Industries.
 BSD license, all text above must be included in any redistribution
 ****************************************************/

#ifndef _ADAFRUIT_TLC59711_H
#define _ADAFRUIT_TLC59711_H

#include <Arduino.h>

//#define USE_WEIGHTS

class Adafruit_TLC59711 {
public:
    Adafruit_TLC59711(uint8_t n, uint8_t c, uint8_t d);
    Adafruit_TLC59711(uint8_t n);
    Adafruit_TLC59711(uint8_t n, uint8_t c, uint8_t d, uint8_t brightness);
    Adafruit_TLC59711(uint8_t n, uint8_t brightness);
    
    uint8_t COMMAND_OPTIONS = 0x16;
    
    boolean begin(void);
    
    void setPWM(uint8_t chan, uint16_t pwm);
    void setLED(uint8_t lednum, uint16_t r, uint16_t g, uint16_t b);
    void write(void);
    void spiwriteMSB(uint32_t d);
    void setGlobalBrightness(uint8_t globalBrightness);
	void setGlobalBrightnessBlue(uint8_t brightness);
	void setGlobalBrightnessRed(uint8_t brightness);
	void setGlobalBrightnessGreen(uint8_t brightness);
	uint8_t getGlobalBrightnessBlue();
	uint8_t getGlobalBrightnessRed();
	uint8_t getGlobalBrightnessGreen();

    void setBlank(bool val);
    void setDisplayRepeat(bool val);
    void setTimingReset(bool val);
    void setExternalClock(bool val);
    void setOutMg(bool val);
    uint8_t createCommand(int BLANK, int DSPRT, int TMGRST, int EXTGCK, int OUTMG);
    void setCommandOptions(int BLANK, int DSPRT, int TMGRST, int EXTGCK, int OUTMG);
    
    void setAll(uint16_t r, uint16_t g, uint16_t b);
    void setAll_1Driver(uint16_t r, uint16_t g, uint16_t b);
    void setAll_2Drivers(uint16_t r, uint16_t g, uint16_t b);
    void setAll_3Drivers(uint16_t r, uint16_t g, uint16_t b);
    void setAll_4Drivers(uint16_t r, uint16_t g, uint16_t b);
    void setWeights(double r, double g, double b);
    
private:
    uint16_t *pwmbuffer;
    
    uint8_t BCr = 127;
    uint8_t BCg = 127; //70;
    uint8_t BCb = 127; //89;
    
    double redWeight = 1.0;
    double blueWeight = 1.0;
    double greenWeight = 1.0;
    
    int8_t numdrivers, _clk, _dat;
    
    void setCommandFlag(bool val, int shift);
    
    uint16_t weight(uint16_t color, double weight);
    uint16_t weightRed(uint16_t color);
    uint16_t weightGreen(uint16_t color);
    uint16_t weightBlue(uint16_t color);
    
};


#endif
