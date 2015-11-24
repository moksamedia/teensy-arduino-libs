
#include <Oscillator.h>

float Oscillator::getValueFloat(float val) {
	return amplitude * sin( val * periodConstant);
}

int Oscillator::getValueInt(float val) {
	return roundf(amplitude * sin( val * periodConstant));
}
