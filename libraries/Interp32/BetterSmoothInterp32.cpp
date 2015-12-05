//
//  BetterSmoothInterp32.cpp
//  led-er
//
//  Created by Andrew Hughes on 11/28/15.
//  Copyright (c) 2015 Andrew Hughes. All rights reserved.
//

#include "BetterSmoothInterp32.h"

uint32_t BetterSmoothInterp32::interp(uint32_t current) {
    return this->betterSmooth(current, power);
}