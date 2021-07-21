#include "TMath.h"

void angles()
{
	TCanvas *c1 = new TCanvas();
	TRandom2 *rand = new TRandom2(10);
	
	TF1 *f_theta = new TF1("f_theta", "cos(x)*cos(x)", 0, 0.5*TMath::Pi()); // function
	double muon_theta = f_theta->GetRandom(); 
	double muon_phi = rand->Rndm()*2.0*TMath::Pi();
	
	cout << "theta: " <<  muon_theta << endl; 
	cout << "phi: " <<  muon_phi << endl; 
	f_theta->Draw();
}


//idea:
// declare variable a
// double a = tan(theta);
// create line by creating function f(x) = a*x
// if the line crosses the cylinder, neutrino was detected 
//
