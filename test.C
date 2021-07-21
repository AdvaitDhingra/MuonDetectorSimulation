#include "TMath.h"

void test(){

	double pi = TMath::Pi();

	double phi = 0.5;
	double theta = 0.3;
	
	double x = 2;
	double y = 3;
	
	double detectorRadius = 2;
	
	double s1 = (-(x*cos(phi)+y*sin(phi))+sqrt((x*cos(phi)+y*sin(phi))*(x*cos(phi)+y*sin(phi))-(x*x+y*y-detectorRadius*detectorRadius)))/sin(theta);
	double s2 = sqrt(((-x*x) - (y*y) + detectorRadius*detectorRadius )/((sin(theta)*sin(theta)) * (cos(phi) * cos(phi) + sin(phi) * sin(phi))));
	
	cout << s1 << s2 << endl;
	
}
