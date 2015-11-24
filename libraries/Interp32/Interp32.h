
#include <stdint.h>


class Interp32 {
    uint32_t min; // min value that sets interpolation range
    uint32_t max; // max value that sets interpolation range
    uint32_t numPoints; // number of points to map between range
    
  public:
  
	Interp32(uint32_t min, uint32_t max, uint32_t numPoints);
	
	void setNumPoints(uint32_t nPoints);
	
	uint32_t getNumPoints();
    
    uint32_t linear(uint32_t current);
    uint32_t smooth(uint32_t current);
    uint32_t smooth2(uint32_t current);
    uint32_t smooth3(uint32_t current);
    uint32_t slowAcc2(uint32_t current);
    uint32_t slowDec2(uint32_t current);
    uint32_t slowAcc3(uint32_t current);
    uint32_t slowDec3(uint32_t current);
    uint32_t slowAcc(uint32_t current, int power);
    uint32_t slowDec(uint32_t current, int power);
    
    uint32_t static LERP(uint32_t min, uint32_t max, uint32_t numPoints, uint32_t current);
    uint32_t static SMOOTH(uint32_t min, uint32_t max, uint32_t numPoints, uint32_t current);
    uint32_t static SMOOTH2(uint32_t min, uint32_t max, uint32_t numPoints, uint32_t current);
    uint32_t static SMOOTH3(uint32_t min, uint32_t max, uint32_t numPoints, uint32_t current);
    uint32_t static SLOWACC(int power, uint32_t min, uint32_t max, uint32_t numPoints, uint32_t current);
    uint32_t static SLOWDEC(int power, uint32_t min, uint32_t max, uint32_t numPoints, uint32_t current);
};