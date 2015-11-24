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


#include <Adafruit_TLC59711.h>
#include <SPI.h>

SPISettings SPI_SETTINGS(500000, MSBFIRST, SPI_MODE0); 

Adafruit_TLC59711::Adafruit_TLC59711(uint8_t n, uint8_t c, uint8_t d) {
  numdrivers = n;
  _clk = c;
  _dat = d;
  setGlobalBrightness(127);
  pwmbuffer = (uint16_t *)calloc(2, 12*n);
}

Adafruit_TLC59711::Adafruit_TLC59711(uint8_t n, uint8_t c, uint8_t d, uint8_t brightness) {
  numdrivers = n;
  _clk = c;
  _dat = d;
  setGlobalBrightness(brightness);
  pwmbuffer = (uint16_t *)calloc(2, 12*n);
}

Adafruit_TLC59711::Adafruit_TLC59711(uint8_t n) {
  numdrivers = n;
  _clk = -1;
  _dat = -1;
  setGlobalBrightness(127);
  pwmbuffer = (uint16_t *)calloc(2, 12*n);
}

Adafruit_TLC59711::Adafruit_TLC59711(uint8_t n, uint8_t brightness) {
  numdrivers = n;
  _clk = -1;
  _dat = -1;
  setGlobalBrightness(brightness);
  pwmbuffer = (uint16_t *)calloc(2, 12*n);
}

void Adafruit_TLC59711::setGlobalBrightness(uint8_t brightness) {
   if (brightness > 127) {
      brightness = 127;
   }
   BCr = (uint8_t)floor(brightness * redWeight);
   BCg = (uint8_t)floor(brightness * greenWeight);
   BCb = (uint8_t)floor(brightness * blueWeight);
}

void Adafruit_TLC59711::setGlobalBrightnessRed(uint8_t brightness) {
	if (brightness < 0) brightness = 0;
	if (brightness > 127) brightness = 127;
	BCr = brightness;
}

void Adafruit_TLC59711::setGlobalBrightnessGreen(uint8_t brightness) {
	if (brightness < 0) brightness = 0;
	if (brightness > 127) brightness = 127;
	BCg = brightness;
}

void Adafruit_TLC59711::setGlobalBrightnessBlue(uint8_t brightness) {
	if (brightness < 0) brightness = 0;
	if (brightness > 127) brightness = 127;
	BCb = brightness;
}

uint8_t Adafruit_TLC59711::getGlobalBrightnessBlue() {
	return BCb;
}

uint8_t Adafruit_TLC59711::getGlobalBrightnessRed() {
	return BCr;
}

uint8_t Adafruit_TLC59711::getGlobalBrightnessGreen() {
	return BCg;
}

void Adafruit_TLC59711::setWeights(double r, double b, double g) {
    blueWeight = b;
    greenWeight = g;
    redWeight = r;
}

uint16_t Adafruit_TLC59711::weight(uint16_t color, double weight) {
    return (uint16_t)floor(color*weight);
}

uint16_t Adafruit_TLC59711::weightRed(uint16_t color) {
    return (uint16_t)floor(color*redWeight);
}

uint16_t Adafruit_TLC59711::weightGreen(uint16_t color) {
    return (uint16_t)floor(color*greenWeight);
}

uint16_t Adafruit_TLC59711::weightBlue(uint16_t color) {
    return (uint16_t)floor(color*blueWeight);
}

void Adafruit_TLC59711::spiwriteMSB(uint32_t d) {

  if (_clk >= 0) {
    uint32_t b = 0x80;
    //  b <<= (bits-1);
    for (; b!=0; b>>=1) {
      digitalWrite(_clk, LOW);
      if (d & b)  
	digitalWrite(_dat, HIGH);
      else
	digitalWrite(_dat, LOW);
      digitalWrite(_clk, HIGH);
    }
  } else {
    SPI.transfer(d);
  }
}

/*
	BLANK: 
	Constant-current output enable bit in FC data (0 = output control enabled, 1 = blank).
	When this bit is '0', all constant-current outputs (OUTR0-OUTB3) are controlled by the GS PWM timing 213 BLANK controller. 
	When this bit is '1', all constant-current outputs are forced off. The GS counter is reset to '0',
	and the GS PWM timing controller is initialized. When the IC is powered on, this bit is set to '1'.
	
	DSPRPT:
	Auto display repeat mode enable bit in FC data (0 = disabled, 1 = enabled). When this bit is '0', the auto repeat 
	function is disabled. Each constant-current output is only turned on once, according the GS data after BLANK is 
	set to '0' or after the internal latch pulse is generated with the TMGRST bit set to '1'. When this bit is '1', 
	each output turns on and off according to the GS data every 65536 GS reference clocks.
	
	TMGRST:
	Display timing reset mode enable bit in FC data (0 = disabled, 1 = enabled).
	When this bit is '1', the GS counter is reset to '0' and all constant-current outputs are forced off when
	the internal latch pulse is generated for data latching. This function is the same when BLANK is set to '0'. 
	Therefore, BLANK does not need to be controlled by an external controller when this mode is enabled. When this bit is '0', 
	the GS counter is not reset and no output is forced off even if the internal latch pulse is generated.
	
	EXTGCK:
	GS reference clock select bit in FC data (0 = internal oscillator clock, 1 = SCKI clock). When this bit is '1', 
	PWM timing refers to the SCKI clock. When this bit is '0', PWM timing refers to the internal oscillator clock.
	
	OUTMG:
	GS reference clock edge select bit for OUTXn on-off timing control in FC data (0 = falling edge, 1 = rising edge). 
	When this bit is '1', OUTXn are turned on or off at the rising edge of the selected GS reference clock.
	When this bit is '0', OUTXn are turned on or off at the falling edge of the selected clock.
	
 */

//OUTTMG = 1, EXTGCK = 0, TMGRST = 1, DSPRPT = 1, BLANK = 0 -> 0x16

void Adafruit_TLC59711::setCommandFlag(bool val, int shift) {
	if (val) {
		COMMAND_OPTIONS |= 1 << shift;
	}
	else {
		COMMAND_OPTIONS &= ~(1 << shift);
	}
}

void Adafruit_TLC59711::setBlank(bool val) {
	setCommandFlag(val, 0);
}

void Adafruit_TLC59711::setDisplayRepeat(bool val) {
	setCommandFlag(val, 1);
}

void Adafruit_TLC59711::setTimingReset(bool val) {
	setCommandFlag(val, 2);
}

void Adafruit_TLC59711::setExternalClock(bool val) {
	setCommandFlag(val, 3);
}

void Adafruit_TLC59711::setOutMg(bool val) {
	setCommandFlag(val, 4);
}

uint8_t Adafruit_TLC59711::createCommand(int BLANK, int DSPRT, int TMGRST, int EXTGCK, int OUTMG) 
{
	return BLANK + (DSPRT << 1) + (TMGRST << 2) + (EXTGCK << 3) + (OUTMG << 4);						
}

void Adafruit_TLC59711::setCommandOptions(int BLANK, int DSPRT, int TMGRST, int EXTGCK, int OUTMG) 
{
	COMMAND_OPTIONS = this->createCommand(BLANK,DSPRT,TMGRST,EXTGCK,OUTMG);
}

void Adafruit_TLC59711::write(void) {
  	
  SPI.beginTransaction(SPI_SETTINGS);
	
  uint32_t command;

  // Magic word for write
  command = 0x25;
  command <<= 5;

  //command |= COMMAND_OPTIONS;

  //OUTTMG = 1, EXTGCK = 0, TMGRST = 1, DSPRPT = 0, BLANK = 0 -> 0x16
  command |= 0x16;

  command <<= 7;
  command |= BCg;

  command <<= 7;
  command |= BCb;

  command <<= 7;
  command |= BCr;

  cli();
  for (uint8_t n=0; n<numdrivers; n++) {
    spiwriteMSB(command >> 24);
    spiwriteMSB(command >> 16);
    spiwriteMSB(command >> 8);
    spiwriteMSB(command);

    // 12 channels per TLC59711
    for (int8_t c=11; c >= 0 ; c--) {
      // 16 bits per channel, send MSB first
      spiwriteMSB(pwmbuffer[n*12+c]>>8);
      spiwriteMSB(pwmbuffer[n*12+c]);
    }
  }

  if (_clk >= 0)
    delayMicroseconds(200);
  else
    delayMicroseconds(2);

	SPI.endTransaction();

  sei();

}

void Adafruit_TLC59711::setPWM(uint8_t chan, uint16_t pwm) {
  if (chan > 12*numdrivers) return;
  pwmbuffer[chan] = pwm;  
}

void Adafruit_TLC59711::setLED(uint8_t lednum, uint16_t r, uint16_t g, uint16_t b) {
#ifdef USE_WEIGHTS
    setPWM(lednum*3, weightRed(r));
    setPWM(lednum*3+1, weightGreen(g));
    setPWM(lednum*3+2, weightBlue(b));
#else
    setPWM(lednum*3, r);
    setPWM(lednum*3+1, g);
    setPWM(lednum*3+2, b);
#endif
}

boolean Adafruit_TLC59711::begin() {
  if (!pwmbuffer) return false;

  if (_clk >= 0) {
    pinMode(_clk, OUTPUT);
    pinMode(_dat, OUTPUT);
  } else {
    SPI.begin();
  }
  return true;
}

void Adafruit_TLC59711::setAll(uint16_t r, uint16_t b, uint16_t g) {
    
#ifdef USE_WEIGHTS
    r = weightRed(r);
    g = weightGreen(g);
    b = weightBlue(b);
#endif
    
    int i;
    for(i=0;i<numdrivers;i++) {
        pwmbuffer[0+i*12] = r;
        pwmbuffer[1+i*12] = g;
        pwmbuffer[2+i*12] = b;
        pwmbuffer[3+i*12] = r;
        pwmbuffer[4+i*12] = g;
        pwmbuffer[5+i*12] = b;
        pwmbuffer[6+i*12] = r;
        pwmbuffer[7+i*12] = g;
        pwmbuffer[8+i*12] = b;
        pwmbuffer[9+i*12] = r;
        pwmbuffer[10+i*12] = g;
        pwmbuffer[11+i*12] = b;
    }
    write();
}

void Adafruit_TLC59711::setAll_1Driver(uint16_t r, uint16_t b, uint16_t g) {
    
#ifdef USE_WEIGHTS
    r = weightRed(r);
    g = weightGreen(g);
    b = weightBlue(b);
#endif
    
    pwmbuffer[0] = r;
    pwmbuffer[1] = g;
    pwmbuffer[2] = b;
    pwmbuffer[3] = r;
    pwmbuffer[4] = g;
    pwmbuffer[5] = b;
    pwmbuffer[6] = r;
    pwmbuffer[7] = g;
    pwmbuffer[8] = b;
    pwmbuffer[9] = r;
    pwmbuffer[10] = g;
    pwmbuffer[11] = b;
    write();
}

void Adafruit_TLC59711::setAll_2Drivers(uint16_t r, uint16_t b, uint16_t g) {
    
#ifdef USE_WEIGHTS
    r = weightRed(r);
    g = weightGreen(g);
    b = weightBlue(b);
#endif
    
    pwmbuffer[0] = r;
    pwmbuffer[1] = g;
    pwmbuffer[2] = b;
    pwmbuffer[3] = r;
    pwmbuffer[4] = g;
    pwmbuffer[5] = b;
    pwmbuffer[6] = r;
    pwmbuffer[7] = g;
    pwmbuffer[8] = b;
    pwmbuffer[9] = r;
    pwmbuffer[10] = g;
    pwmbuffer[11] = b;
    
    pwmbuffer[12] = r;
    pwmbuffer[13] = g;
    pwmbuffer[14] = b;
    pwmbuffer[15] = r;
    pwmbuffer[16] = g;
    pwmbuffer[17] = b;
    pwmbuffer[18] = r;
    pwmbuffer[19] = g;
    pwmbuffer[20] = b;
    pwmbuffer[21] = r;
    pwmbuffer[22] = g;
    pwmbuffer[23] = b;
    
    write();
    
}


void Adafruit_TLC59711::setAll_3Drivers(uint16_t r, uint16_t b, uint16_t g) {
    
#ifdef USE_WEIGHTS
    r = weightRed(r);
    g = weightGreen(g);
    b = weightBlue(b);
#endif
    
    pwmbuffer[0] = r;
    pwmbuffer[1] = g;
    pwmbuffer[2] = b;
    pwmbuffer[3] = r;
    pwmbuffer[4] = g;
    pwmbuffer[5] = b;
    pwmbuffer[6] = r;
    pwmbuffer[7] = g;
    pwmbuffer[8] = b;
    pwmbuffer[9] = r;
    pwmbuffer[10] = g;
    pwmbuffer[11] = b;
    
    pwmbuffer[12] = r;
    pwmbuffer[13] = g;
    pwmbuffer[14] = b;
    pwmbuffer[15] = r;
    pwmbuffer[16] = g;
    pwmbuffer[17] = b;
    pwmbuffer[18] = r;
    pwmbuffer[19] = g;
    pwmbuffer[20] = b;
    pwmbuffer[21] = r;
    pwmbuffer[22] = g;
    pwmbuffer[23] = b;
    
    pwmbuffer[24] = r;
    pwmbuffer[25] = g;
    pwmbuffer[26] = b;
    pwmbuffer[27] = r;
    pwmbuffer[28] = g;
    pwmbuffer[29] = b;
    pwmbuffer[30] = r;
    pwmbuffer[31] = g;
    pwmbuffer[32] = b;
    pwmbuffer[33] = r;
    pwmbuffer[34] = g;
    pwmbuffer[35] = b;
    
    write();
    
}

void Adafruit_TLC59711::setAll_4Drivers(uint16_t r, uint16_t b, uint16_t g) {
    
#ifdef USE_WEIGHTS
    r = weightRed(r);
    g = weightGreen(g);
    b = weightBlue(b);
#endif
    
    pwmbuffer[0] = r;
    pwmbuffer[1] = g;
    pwmbuffer[2] = b;
    pwmbuffer[3] = r;
    pwmbuffer[4] = g;
    pwmbuffer[5] = b;
    pwmbuffer[6] = r;
    pwmbuffer[7] = g;
    pwmbuffer[8] = b;
    pwmbuffer[9] = r;
    pwmbuffer[10] = g;
    pwmbuffer[11] = b;
    
    pwmbuffer[12] = r;
    pwmbuffer[13] = g;
    pwmbuffer[14] = b;
    pwmbuffer[15] = r;
    pwmbuffer[16] = g;
    pwmbuffer[17] = b;
    pwmbuffer[18] = r;
    pwmbuffer[19] = g;
    pwmbuffer[20] = b;
    pwmbuffer[21] = r;
    pwmbuffer[22] = g;
    pwmbuffer[23] = b;
    
    pwmbuffer[24] = r;
    pwmbuffer[25] = g;
    pwmbuffer[26] = b;
    pwmbuffer[27] = r;
    pwmbuffer[28] = g;
    pwmbuffer[29] = b;
    pwmbuffer[30] = r;
    pwmbuffer[31] = g;
    pwmbuffer[32] = b;
    pwmbuffer[33] = r;
    pwmbuffer[34] = g;
    pwmbuffer[35] = b;
    
    pwmbuffer[36] = r;
    pwmbuffer[37] = g;
    pwmbuffer[38] = b;
    pwmbuffer[39] = r;
    pwmbuffer[40] = g;
    pwmbuffer[41] = b;
    pwmbuffer[42] = r;
    pwmbuffer[43] = g;
    pwmbuffer[44] = b;
    pwmbuffer[45] = r;
    pwmbuffer[46] = g;
    pwmbuffer[47] = b;
    
    write();
    
}
