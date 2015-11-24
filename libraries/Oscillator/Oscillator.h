
#include <math.h>

class Oscillator {
	
	float amplitude;
	float periodConstant;
	
public:
	
	Oscillator(float amplitude, float period) {
		this->amplitude = amplitude;
		this->periodConstant = 2 * M_PI / period;
	}
	
	float getValueFloat(float val);
	int getValueInt(float val);
	
};