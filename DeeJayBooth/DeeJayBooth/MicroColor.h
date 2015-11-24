#ifndef ColorUtils_LocalLibrary_h
#define ColorUtils_LocalLibrary_h

#include "Arduino.h"

struct _RGB {
    byte r;
    byte g;
    byte b;
}; typedef struct _RGB RGB;

struct _HSV {
    double h;
    double s;
    double v;
}; typedef struct _HSV HSV;

struct _HSL {
    double h;
    double s;
    double v;
}; typedef struct _HSL HSL;

class MicroColor {
    
public:
    
    RGB rgb;
    
    MicroColor(uint32_t colorVal);
    MicroColor(byte r, byte g, byte b);
    
    static void int2Rgb(uint32_t colorVal, RGB * rgb);
};

#endif
