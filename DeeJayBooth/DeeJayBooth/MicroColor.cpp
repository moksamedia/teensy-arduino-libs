#include "MicroColor.h"


MicroColor::MicroColor(uint32_t colorVal) {
    MicroColor::int2Rgb(colorVal, &rgb);
}

MicroColor::MicroColor(byte r, byte g, byte b) {
    rgb.r = r;
    rgb.g = g;
    rgb.b = b;
}

void MicroColor::int2Rgb(uint32_t colorVal, RGB * rgb)  {
    rgb->r = (colorVal >> 16) & 0xFF;  // Extract the RR byte
    rgb->g = (colorVal >> 8) & 0xFF;   // Extract the GG byte
    rgb->b = (colorVal) & 0xFF;
}
