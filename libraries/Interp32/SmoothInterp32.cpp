//
//  SmoothInterp32.cpp
//  led-er
//
//  Created by Andrew Hughes on 11/28/15.
//  Copyright (c) 2015 Andrew Hughes. All rights reserved.
//

#include "SmoothInterp32.h"

uint32_t SmoothInterp32::interp(uint32_t current) {
    return this->smooth(current, power);
}

