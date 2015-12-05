//
//  SlowDecInterp32.h
//  led-er
//
//  Created by Andrew Hughes on 11/28/15.
//  Copyright (c) 2015 Andrew Hughes. All rights reserved.
//

#ifndef __led_er__SlowDecInterp32__
#define __led_er__SlowDecInterp32__

#include <stdio.h>
#include "AInterp32.h"

class SlowDecInterp32 : public AInterp32 {
public:
    explicit SlowDecInterp32(uint32_t min, uint32_t max, uint32_t numPoints, int power) : AInterp32(min, max, numPoints, power) {};
    uint32_t interp(uint32_t current);
};

#endif /* defined(__led_er__SlowDecInterp32__) */
