//
//  SmoothInterp32.cpp
//  led-er
//
//  Created by Andrew Hughes on 11/28/15.
//  Copyright (c) 2015 Andrew Hughes. All rights reserved.
//

#include "SlowAccInterp32.h"

uint32_t SlowAccInterp32::interp(uint32_t current) {
    return this->slowAcc(current, power);
}

