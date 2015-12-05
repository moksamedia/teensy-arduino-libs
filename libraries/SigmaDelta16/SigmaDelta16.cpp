//
//  SigmaDelta16.cpp
//  sigma-delta-tester
//
//  Created by Andrew Hughes on 11/24/15.
//  Copyright (c) 2015 Andrew Hughes. All rights reserved.
//

#include "SigmaDelta16.h"
//#define DEBUG

SigmaDelta16::SigmaDelta16() {
    this->extraBits = EXTRA_BITS;
    this->maxValue = pow(2, 16 + EXTRA_BITS) - 1;
    state = 0;
#ifdef DEBUG
    Serial.print("maxValue = "); Serial.println(this->maxValue);
#endif
}

uint16_t SigmaDelta16::sigmaDelta(uint32_t input) {
    
#ifdef DEBUG
    Serial.println("--------------------------------");
    Serial.print("input = "); Serial.println(this->maxValue);
    Serial.print("state = "); Serial.println(this->maxValue);
#endif
    uint32_t result;
    state += input;
    result = unsigned_saturate_rshift(state, 16, EXTRA_BITS);
    state -= (result << extraBits);
    
#ifdef DEBUG
    Serial.print("result = "); Serial.println(result);
    Serial.print("state = "); Serial.println(state);
#endif
    
    return (uint16_t)result;
}

