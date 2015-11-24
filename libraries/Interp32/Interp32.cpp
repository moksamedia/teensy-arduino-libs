#include <math.h>
#include "interp32.h"

#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))


Interp32::Interp32(uint32_t min, uint32_t max, uint32_t numPoints) {
 this->min = min;
 this->max = max;
 this->numPoints = numPoints; 
}

void Interp32::setNumPoints(uint32_t nPoints) {
	this->numPoints = nPoints;
}

uint32_t Interp32::getNumPoints() {
	return this->numPoints;
}

uint32_t Interp32::LERP(uint32_t min, uint32_t max, uint32_t numPoints, uint32_t current) {
  double v = double(current) / double(numPoints);
  return (max * v) + (min * (1 - v));
}

uint32_t Interp32::SMOOTH(uint32_t min, uint32_t max, uint32_t numPoints, uint32_t current) {
  double v = double(current) / double(numPoints);
  v = SMOOTHSTEP(v);
  return (max * v) + (min * (1 - v));
}

uint32_t Interp32::SMOOTH2(uint32_t min, uint32_t max, uint32_t numPoints, uint32_t current) {
  double v = double(current) / double(numPoints);
  v = SMOOTHSTEP(SMOOTHSTEP(v));
  return (max * v) + (min * (1 - v));
}

uint32_t Interp32::SMOOTH3(uint32_t min, uint32_t max, uint32_t numPoints, uint32_t current) {
  double v = double(current) / double(numPoints);
  v = SMOOTHSTEP(SMOOTHSTEP(SMOOTHSTEP(v)));
  return (max * v) + (min * (1 - v));
}


uint32_t Interp32::SLOWACC(int power, uint32_t min, uint32_t max, uint32_t numPoints, uint32_t current) {
  double v = double(current) / double(numPoints);
  v = pow((double)v,(double)power);
  return (max * v) + (min * (1 - v));
}

uint32_t Interp32::SLOWDEC(int power, uint32_t min, uint32_t max, uint32_t numPoints, uint32_t current) {
  double v = double(current) / double(numPoints);
  v = 1 - pow((double)(1 - v), (double)power);
  return (max * v) + (min * (1 - v));
}

uint32_t Interp32::linear(uint32_t current) {
  return Interp32::LERP(this->min, this->max, this->numPoints, current);
}

uint32_t Interp32::smooth(uint32_t current) {
  return Interp32::SMOOTH(this->min, this->max, this->numPoints, current);
}

uint32_t Interp32::smooth2(uint32_t current) {
  return Interp32::SMOOTH2(this->min, this->max, this->numPoints, current);
}

uint32_t Interp32::smooth3(uint32_t current) {
  return Interp32::SMOOTH3(this->min, this->max, this->numPoints, current);
}

uint32_t Interp32::slowAcc2(uint32_t current) {
  return Interp32::SLOWACC(2, this->min, this->max, this->numPoints, current);
}

uint32_t Interp32::slowDec2(uint32_t current) {
  return Interp32::SLOWDEC(2, this->min, this->max, this->numPoints, current);
}

uint32_t Interp32::slowAcc3(uint32_t current) {
  return Interp32::SLOWACC(3, this->min, this->max, this->numPoints, current);
}

uint32_t Interp32::slowDec3(uint32_t current) {
  return Interp32::SLOWDEC(3, this->min, this->max, this->numPoints, current);
}

uint32_t Interp32::slowAcc(uint32_t current, int power) {
  return Interp32::SLOWACC(power, this->min, this->max, this->numPoints, current);
}

uint32_t Interp32::slowDec(uint32_t current, int power) {
  return Interp32::SLOWDEC(power, this->min, this->max, this->numPoints, current);
}
