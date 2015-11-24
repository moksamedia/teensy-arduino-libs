
class Interp {
    int min; // min value that sets interpolation range
    int max; // max value that sets interpolation range
    int numPoints; // number of points to map between range
    
  public:
  
    Interp(int min, int max, int numPoints) {
     this->min = min;
     this->max = max;
     this->numPoints = numPoints; 
    }

	void setNumPoints(int nPoints);
	int getNumPoints();
    
    int linear(int current);
    int smooth(int current);
    int smooth2(int current);
    int smooth3(int current);
    int slowAcc2(int current);
    int slowDec2(int current);
    int slowAcc3(int current);
    int slowDec3(int current);
    int slowAcc(int current, int power);
    int slowDec(int current, int power);
    
    int static LERP(int min, int max, int numPoints, int current);
    int static SMOOTH(int min, int max, int numPoints, int current);
    int static SMOOTH2(int min, int max, int numPoints, int current);
    int static SMOOTH3(int min, int max, int numPoints, int current);
    int static SLOWACC(int powwer, int min, int max, int numPoints, int current);
    int static SLOWDEC(int powwer, int min, int max, int numPoints, int current);
};