#include "MicroColor.h"


MicroColor::MicroColor(uint32_t colorVal) {
    MicroColor::separateColors(colorVal, &rgb);
}

void MicroColor::separateColors(uint32_t colorVal, RGB * rgb)  {
    rgb->r = (colorVal >> 16) & 0xFF;  // Extract the RR byte
    rgb->g = (colorVal >> 8) & 0xFF;   // Extract the GG byte
    rgb->b = (colorVal) & 0xFF;
}
