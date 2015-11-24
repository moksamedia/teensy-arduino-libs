//
//  SigmaDelta16.h
//  sigma-delta-tester
//
//  Created by Andrew Hughes on 11/24/15.
//  Copyright (c) 2015 Andrew Hughes. All rights reserved.
//

#ifndef __sigma_delta_tester__SigmaDelta16__
#define __sigma_delta_tester__SigmaDelta16__

#include "Arduino.h"

class SigmaDelta16 {
public:
    SigmaDelta16(uint8_t numExtraBits);
    SigmaDelta16();
    void init(uint8_t numExtraBits);
    uint16_t sigmaDelta(uint32_t input);
    
    /* Maximum value at 16 + extraBits.
     */
    uint32_t maxValue;
    
private:
    /* Holds the running error value used to offset each cycle before truncation
       to 16 bits.
     */
    int32_t state = 0;
    
    /* How many extra bits of precision are we using? So for 18 bits of total
       precision, shiftBits would be 2. 16 + 2 = 18.
     */
    uint8_t extraBits;

};

#endif /* defined(__sigma_delta_tester__SigmaDelta16__) */
