//
//  AInterp32.h
//  led-er
//
//  Created by Andrew Hughes on 11/28/15.
//  Copyright (c) 2015 Andrew Hughes. All rights reserved.
//

#ifndef __AInterp32__
#define __AInterp32__

#include <stdio.h>
#include "Interp32.h"

class AInterp32 : public Interp32 {
public:
    AInterp32();
    AInterp32(uint32_t min, uint32_t max, uint32_t numPoints, int power);
    void init(uint32_t min, uint32_t max, uint32_t numPoints, int power);
    int power;
    virtual uint32_t interp(uint32_t current) = 0;
};

#endif /* defined(__led_er__AInterp32__) */
