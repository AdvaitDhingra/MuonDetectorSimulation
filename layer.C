#include "TMath.h"

void layer()
{

	double pi = TMath::Pi();
	double detectorRadius = 0.5;
	double detectorHeight = 10;
	
	TH2F *layer = new TH2F("layer", "Muon detection",400, -2*detectorRadius, 2*detectorRadius, 400,  -2*detectorRadius, 2*detectorRadius);
	TH1F *phiDist = new TH1F("Phi Dist", "Angle Phi Distribution", 4000, 0, 3.5);
	TF1 *f_theta = new TF1("f_theta","cos(x)*cos(x)",-0.5*pi,+0.5*pi);
	TH1F *thetaDist = new TH1F("Theta Dist", "Angle Theta Distribution", 2000, 0, 3.5);
	TH2F *angDist = new TH2F("Angular Dist", "Angular Distribution", 300, -1, 1, 300, -1, 1);
	TH2F *topIn = new TH2F("Top In", "Top Enter", 300, -2*detectorRadius, 2*detectorRadius, 300, -2*detectorRadius, 2*detectorRadius);
	TH2F *topOut = new TH2F("Top Out", "Top Out", 300, -2*detectorRadius, 2*detectorRadius, 300, -2*detectorRadius, 2*detectorRadius);
	TH2F *btmPoint = new TH2F("Bottom Point", "Bottom Point", 300, -2*detectorRadius, 2*detectorRadius, 300, -2*detectorRadius, 2*detectorRadius);
	
	TRandom2 *rand = new TRandom2(0);
	
	double mouonIOTopX[1000];
	double mouonIOTopY[1000];
	
	
	
	for (int i = 0; i < 1e6; i++)
	{
		double x = (rand->Rndm()-0.5)*2*detectorRadius;
		double y = (rand->Rndm()-0.5)*2*detectorRadius;
		
		double r = abs(sqrt(x*x + y*y));
		
		if (r <= detectorRadius){
			double z = rand->Rndm()*detectorHeight;
			TVector3 p;
			p.SetX(x);
			p.SetY(y);
			p.SetZ(z);
			layer->Fill(x, y, z);
			double phi = acos(x/r);
			phiDist->Fill(phi);
			double theta = f_theta->GetRandom();
			thetaDist->Fill(theta);
			angDist->Fill(theta*cos(phi), theta*sin(phi));
			TVector3 a;
			a.SetX(tan(phi));
			a.SetY(0.5*pi-tan(phi));
			a.SetZ(tan(theta));
			if (z <= 0.1){
				topIn->Fill(x, y);
				TVector3 *sm;
				sm->SetX(a.X() * detectorHeight);
				sm->SetY(a.Y() * detectorHeight);
				sm->SetZ(a.Z() * detectorHeight);
				TVector3 minimum;
				minimum.SetX(p.X() + sm->X());
				minimum.SetY(p.Y() + sm->Y());
				minimum.SetZ(p.Z() + sm->Z());
				btmPoint->Fill(minimum.X(), minimum.Y());
			}	
			
			
		}
		
		
	}
	
	TCanvas *c1 = new TCanvas("c1", "Muons", 700, 700);
	layer->GetXaxis()->SetTitle("X-Position of Muon");
	layer->GetYaxis()->SetTitle("Y-Position of Muon");
	layer->Draw("colz");
	TCanvas *c2 = new TCanvas("c2", "Phi", 700, 700);
	phiDist->GetYaxis()->SetRangeUser(0, 1000);
	phiDist->Draw();
	TCanvas *c3 = new TCanvas("c3", "Theta", 700, 700);
	thetaDist->Draw();
	TCanvas *c4 = new TCanvas("c4", "Angular Dist", 700, 700);
	angDist->Draw();
	TCanvas *c5 = new TCanvas("c5", "Enter and Exit Top", 700, 700);
	topOut->SetFillColor(kBlack);
	topIn->SetFillColor(kGreen);
	btmPoint->SetFillColor(kRed);
	topIn->Add(topOut);
	topIn->Add(btmPoint);
	topIn->Draw("AP");
	
	c1->Print("layer.png");
	c2->Print("Phi.png");
	c3->Print("Theta.png");
	c4->Print("AngularDist.png");

}
