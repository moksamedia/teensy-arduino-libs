//
//  AInterp32.cpp
//  led-er
//
//  Created by Andrew Hughes on 11/28/15.
//  Copyright (c) 2015 Andrew Hughes. All rights reserved.
//

#include "AInterp32.h"

AInterp32::AInterp32() {}

AInterp32::AInterp32(uint32_t min, uint32_t max, uint32_t numPoints, int power)
: Interp32(min, max, numPoints) {
    this->power = power;
}

void AInterp32::init(uint32_t min, uint32_t max, uint32_t numPoints, int power) {
    Interp32::init(min,max,numPoints);
    this->power = power;
}
