//
//  SlowDecInterp32.cpp
//  led-er
//
//  Created by Andrew Hughes on 11/28/15.
//  Copyright (c) 2015 Andrew Hughes. All rights reserved.
//

#include "SlowDecInterp32.h"

uint32_t SlowDecInterp32::interp(uint32_t current) {
    return this->slowDec(current, power);
}

