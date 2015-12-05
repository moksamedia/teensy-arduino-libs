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

static inline int32_t signed_saturate_rshift(uint32_t val, int bits, int rshift) __attribute__((always_inline, unused));
static inline int32_t signed_saturate_rshift(uint32_t val, int bits, int rshift)
{
    int32_t out;
    asm volatile("ssat %0, %1, %2, asr %3" : "=r" (out) : "I" (bits), "r" (val), "I" (rshift));
    return out;
}

static inline uint32_t unsigned_saturate_rshift(int32_t val, int bits, int rshift) __attribute__((always_inline, unused));
static inline uint32_t unsigned_saturate_rshift(int32_t val, int bits, int rshift)
{
    uint32_t out;
    asm volatile("usat %0, %1, %2, asr %3" : "=r" (out) : "I" (bits), "r" (val), "I" (rshift));
    return out;
}

#define EXTRA_BITS 2

class SigmaDelta16 {
public:
    SigmaDelta16();
    uint16_t sigmaDelta(uint32_t input);
    
    /* Maximum value at 16 + extraBits. For 18 bits = 262143.
     */
    uint32_t maxValue;
    
    /* How many extra bits of precision are we using? So for 18 bits of total
     precision, shiftBits would be 2. 16 + 2 = 18.
     */
    int extraBits;
    
private:
    /* Holds the running error value used to offset each cycle before truncation
       to 16 bits.
     */
    uint32_t state = 0;

};

#endif /* defined(__sigma_delta_tester__SigmaDelta16__) */
