
elapsedMicros microsElapsed;

#define MAX_18_BITS 262143

static inline uint32_t unsigned_saturate(int32_t val, int bits) __attribute__((always_inline, unused));
static inline uint32_t unsigned_saturate(int32_t val, int bits)
{
    uint32_t out;
    asm volatile("usat %0, %1, %2" : "=r" (out) : "I" (bits), "r" (val));
    return out;
}


uint32_t saturate(int32_t value) {
    
    if (value > MAX_18_BITS) {
        value = MAX_18_BITS;
    }
    else if (value < 0) {
        value = 0;
    }
    return value;
    
}

void setup() {
    Serial.begin(9600);
}

void loop() {
  
    // TEST REGULAR C FUNCTION "SATURATE"
    
    uint32_t result = 131071;
    
    microsElapsed = 0;
    
    int j;
    for (j=0;j<100000;j++) {
        result = saturate(result + random(0,8000));
        result = saturate(result - random(0,8000));
    }
    
    Serial.println(microsElapsed);
    
    // TEST INLINE STATIC USAT
    
    result = 131071;
    microsElapsed = 0;

    int i;
    for (i=0;i<100000;i++) {
        result = unsigned_saturate(result + random(0,8000), 18);
        result = unsigned_saturate(result - random(0,8000), 18);
    }

    Serial.println(microsElapsed);
    
    delay(5000);
}
