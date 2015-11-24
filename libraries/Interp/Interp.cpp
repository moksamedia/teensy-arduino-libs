
#include <math.h>
#include "interp.h"

/*
 *	http://sol.gfxile.net/interpolation/index.html
 *  http://www.gizma.com/easing/#cub3
 */

//#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))

float SMOOTHSTEP(float x) {
	double result = x * x * (3 - 2 * x);
	return float(result);
}

int Interp::LERP(int min, int max, int numPoints, int current) {
  float v = (float)current / (float)numPoints;
  return (max * v) + (min * (1 - v));
}

void Interp::setNumPoints(int nPoints) {
	this->numPoints = nPoints;
}

int Interp::getNumPoints() {
	return this->numPoints;
}

int Interp::SMOOTH(int min, int max, int numPoints, int current) {
  float v = (float)current / (float)numPoints;
  v = SMOOTHSTEP(v);
  return (max * v) + (min * (1 - v));
}

int Interp::SMOOTH2(int min, int max, int numPoints, int current) {
  float v = (float)current / (float)numPoints;
  v = SMOOTHSTEP(v);
  v = SMOOTHSTEP(v);
  return (max * v) + (min * (1 - v));
}

int Interp::SMOOTH3(int min, int max, int numPoints, int current) {
  float v = (float)current / (float)numPoints;
  v = SMOOTHSTEP(v);
  v = SMOOTHSTEP(v);
  v = SMOOTHSTEP(v);
  return (max * v) + (min * (1 - v));
}

int Interp::SLOWACC(int power, int min, int max, int numPoints, int current) {
  float v = (float)current / (float)numPoints;
  v = pow((double)v,(double)power);
  return (max * v) + (min * (1 - v));
}

int Interp::SLOWDEC(int power, int min, int max, int numPoints, int current) {
  float v = (float)current / (float)numPoints;
  v = 1 - pow((double)(1 - v), (double)power);
  return (max * v) + (min * (1 - v));
}

int Interp::linear(int current) {
  return LERP(this->min, this->max, this->numPoints, current);
}

int Interp::smooth(int current) {
  return SMOOTH(this->min, this->max, this->numPoints, current);
}

int Interp::smooth2(int current) {
  return SMOOTH2(this->min, this->max, this->numPoints, current);
}

int Interp::smooth3(int current) {
  return SMOOTH3(this->min, this->max, this->numPoints, current);
}

int Interp::slowAcc2(int current) {
  return SLOWACC(2, this->min, this->max, this->numPoints, current);
}

int Interp::slowDec2(int current) {
  return SLOWDEC(2, this->min, this->max, this->numPoints, current);
}

int Interp::slowAcc3(int current) {
  return SLOWACC(3, this->min, this->max, this->numPoints, current);
}

int Interp::slowDec3(int current) {
  return SLOWDEC(3, this->min, this->max, this->numPoints, current);
}

int Interp::slowAcc(int current, int power) {
  return SLOWACC(power, this->min, this->max, this->numPoints, current);
}

int Interp::slowDec(int current, int power) {
  return SLOWDEC(power, this->min, this->max, this->numPoints, current);
}

/*
int SMOOTH(int min, int max, int numPoints, int current) {
  float v = (float)current / (float)numPoints;
  v = SMOOTHSTEP(v);
  return (max * v) + (min * (1 - v));
}

int SLOWACC2(int min, int max, int numPoints, int current) {
  float v = (float)current / (float)numPoints;
  v = v * v;
  return (max * v) + (min * (1 - v));
}

int SLOWDEC2(int min, int max, int numPoints, int current) {
  float v = (float)current / (float)numPoints;
  v = v = 1 - (1 - v) * (1 - v);
  return (max * v) + (min * (1 - v));
}

int SLOWACC3(int min, int max, int numPoints, int current) {
  float v = (float)current / (float)numPoints;
  v = v * v * v;
  return (max * v) + (min * (1 - v));
}

int SLOWDEC3(int min, int max, int numPoints, int current) {
  float v = (float)current / (float)numPoints;
  v = v = 1 - (1 - v) * (1 - v) * (1 - v);
  return (max * v) + (min * (1 - v));
}

int SLOWACC2(int min, int max, int numPoints, int current) {
  float v = (float)current / (float)numPoints;
  v = pow(v,power);
  return (max * v) + (min * (1 - v));
}

int slowDecc(int power, int min, int max, int numPoints, int current) {
  float v = (float)current / (float)numPoints;
  v = v = 1 - pow((1 - v), power);
  return (max * v) + (min * (1 - v));
}
*/