#include "TMath.h"

void cosmicRays()
{

	TH1::AddDirectory(false); // ROOT object lifeline managment is not needed

	double pi = TMath::Pi(); // 3.141592652589...
	
	//conversion volume description
	double detectorRadius = 0.04; // radius of the detector in cm
	double detectorHeight = 0.2; // height of the detector in cm
	
	
	
	// histograms and functions
	
	TH2F *layer = new TH2F("layer", "Muons",2000, -detectorRadius, detectorRadius, 2000,  -detectorRadius, detectorRadius); // all the muons in the first layer
	TH1F *phiDist = new TH1F("Phi Dist", "Angle Phi Distribution", 4000, 0, 3.5);// angle phi distribution
	TF1 *f_theta = new TF1("f_theta","cos(x)*cos(x)",-0.5*pi,+0.5*pi); // theta function
	TH1F *thetaDist = new TH1F("Theta Dist", "Angle Theta Distribution", 2000, 0, 3.5); // angle theta distribution
	TH2F *angDist = new TH2F("Angular Dist", "Angular Distribution", 300, -1, 1, 300, -1, 1); // angle distribution
	TH2F *bottomEscape = new TH2F("Top", "Muons exiting points as seen from the top", 600, -detectorRadius, detectorRadius, 600, -detectorRadius, detectorRadius);// exit point of muons that enter from the top
	TH2F *topEntry = new TH2F("Top", "Muon entry points as seen from the top ", 600, -detectorRadius, detectorRadius, 600, -detectorRadius, detectorRadius); // muons that enter from the top

	
	TH2F *sideView = new TH2F("Side", "Front View of the Muon entry and exit points", 1000, 0-detectorRadius, detectorRadius, 1000, -detectorHeight, 0); // side view
	

	TH1F *travelDistance = new TH1F("Distance", "Distance travelled by Muons in conversion volume with regard to Energy", 300, 0, 200);
	
	TF1 *verteilungEnergie = new TF1("Energy Verteilung", "71 * 45 * (4.1 + x)^-3.04 * (1+x/854)^-1", 1e-1, 50);
	
	TH1F *impulseDist = new TH1F("Impulse distribution", "Impulse Distribution", 500, 0, 5e4);
	
	
	TRandom2 *rand = new TRandom2(); // random number generator
	
	double spare = 0;
	
	double c = 299792458; // m/s
	
	double particlesStopped = 0;
	
	double particlesInDetector = 0;
	
	double area = pi*detectorRadius * detectorRadius;
	
	double muonsInTopLayer = 0;
	double muonsInMiddle = 0;
	double muonsInBottomLayer = 0;
	
	for (int j = 0; j < 1e5; j++)
	{
		
		
		double schnittpunkte = 0;
		//generate the starting point of the particle
		double x = (rand->Rndm()-0.5)*2*detectorRadius;
		double y = (rand->Rndm()-0.5)*2*detectorRadius;
		
		
		//distance between the starting point and the center
		double r_2d = abs(sqrt(x*x + y*y));
		
	//	cout << r_2d << endl;
		
		//the two angles that are needed
		double theta = f_theta->GetRandom();
		double phi = rand->Rndm()*2.0*pi;
		
		double z = rand->Rndm()*-detectorHeight;
		
		
		
		//Entry and exit points
		if (r_2d <= detectorRadius)
		{	
		
			//generate the projection of muons from the top
			
			TVector3 *p = new TVector3(x, y, z);
			layer->Fill(x, y);
			//sideView->Fill(x, z);
			phiDist->Fill(phi);
			thetaDist->Fill(theta);
			angDist->Fill(theta*cos(phi), theta*sin(phi));
			
			double distanceE;
			
			double impulses[25];
			impulses[0] = 4.704e1;
			impulses[1] = 5.616e1;
			impulses[2] = 6.802e1;
			impulses[3] = 8.509e1;
			impulses[4] = 1.003e2;
			impulses[5] = 1.527e2;
			impulses[6] = 1.764e2;
			impulses[7] = 2.218e2;
			impulses[8] = 2.868e2;
//			impulses[9] = 3.917e2;
			impulses[9] = 4.096e2;
			impulses[10] = 4.945e2;
			impulses[11] = 8.995e2;
			impulses[12] = 1.101e3;
			impulses[13] = 1.502e3;
			impulses[14] = 2.103e3;
			impulses[15] = 3.104e3;
			impulses[16] = 4.104e3;
			impulses[17] = 8.105e3;
			impulses[18] = 1.101e4;
			impulses[19] = 1.411e4;
			impulses[20] = 2.011e4;
			impulses[21] = 3.011e4;
			impulses[22] = 4.011e4;
			impulses[23] = 8.011e4;
			
			double ranges[25];
			ranges[0] = 6.998e-1;
			ranges[1] = 1.279;
			ranges[2] = 2.392;
			ranges[3] = 4.782;
			ranges[4] = 7.696;
			ranges[5] = 2.261e1;
			ranges[6] = 3.124e1;
			ranges[7] = 4.968e1;
			ranges[8] = 7.894e1;
			//ranges[9] = 1.291e2;
			ranges[9] = 1.291e2;
			ranges[10] = 1.796e2;
			ranges[11] = 3.711e2;
			ranges[12] = 4.732e2;
			ranges[13] = 6.611e2;
			ranges[14] = 9.353e2;
			ranges[15] = 1.378e3;
			ranges[16] = 1.810e3;
			ranges[17] = 3.472e3;
			ranges[18] = 4.279e3;
			ranges[19] = 5.862e3;
			ranges[20] = 8.183e3;
			ranges[21] = 1.195e4;
			ranges[22] = 1.563e4;
			ranges[23] = 2.969e4;
			
			double energy = verteilungEnergie->GetRandom() * 1000;
			//energy = 95;
			double impulse = sqrt((energy*energy)-105*105);
			
			impulseDist->Fill(impulse);
			
			//cout << energy << "  " <<  impulse << endl;
			
			for (int l = 0; l <= 23; l++){
				//cout << l << endl;
				if ((impulse >= impulses[l]) && (impulse < impulses[l+1])){
					double bigger = (impulse-impulses[l])/(impulses[l+1]-impulses[l]);
					distanceE = (ranges[l] + ((ranges[l+1]-ranges[l]) * bigger))/100;
					//cout << bigger << endl;
					travelDistance->Fill(distanceE); // unit is metres
					//cout << l << " " << bigger <<  endl;
				}
			}
			
			//cout << energy << "  " << impulse << " " << distanceE/100 << endl;
			
			
			
			// Muon enters and exits the cylinder from the side
					double s1 = (-(x*cos(phi)+y*sin(phi))+sqrt((x*cos(phi)+y*sin(phi))*(x*cos(phi)+y*sin(phi))-(x*x+y*y-detectorRadius*detectorRadius)))/sin(theta);
		    		double s2 = (-(x*cos(phi)+y*sin(phi))-sqrt((x*cos(phi)+y*sin(phi))*(x*cos(phi)+y*sin(phi))-(x*x+y*y-detectorRadius*detectorRadius)))/sin(theta);
		    		double sZAxis = ((-detectorHeight)-z)/cos(theta); // P+m*s
		         	double sXAxis2 = -z/cos(theta);
		         	double sMiddle = ((-0.5*detectorHeight)-z)/cos(theta);
		         		
		    
		    //cout << s1 << " " << s2 << endl;
		    		//cout << s1 << " " << s2 << endl;
		         	TVector3 *entryPoint = new TVector3(x+s1 * sin(theta) * cos(phi), y+s1*sin(theta)*sin(phi), z+s1*cos(theta)); // entry point on the side
		         	TVector3 *exitPoint = new TVector3(x+s2 * sin(theta) * cos(phi), y+s2*sin(theta)*sin(phi), z+s2*cos(theta)); // exit point on the side
		         //	cout << exitPoint->X() << " " << exitPoint->Y() << endl;
		         	double radius1 = sqrt(entryPoint->X() * entryPoint->X() + entryPoint->Y() * entryPoint->Y());
		         	double radius2 = sqrt(exitPoint->X() * exitPoint->X() + exitPoint->Y() * exitPoint->Y());
		         	TVector3 *escapePointZ = new TVector3(x + sZAxis*sin(theta) * cos(phi), y + sZAxis*sin(theta)*sin(phi), -detectorHeight); // escape point on the bottom
		         	//cout << (z+sZAxis*cos(theta)) << endl;
					TVector3 *entryPointX = new TVector3(x+sXAxis2*sin(theta)*cos(phi), y+sXAxis2*sin(theta)*sin(phi), z+sXAxis2*cos(theta)); // entry point on the top
					double entryRadius = abs(sqrt(entryPointX->X()*entryPointX->X() + entryPointX->Y()*entryPointX->Y()));
					if (entryRadius <= detectorRadius){
						muonsInTopLayer++;
					}
					TVector3  *middlePoint = new TVector3(x+sMiddle*sin(theta)*cos(phi), y+sMiddle*sin(theta)*sin(phi), z+sMiddle*cos(theta));
					double middleRadius = abs(sqrt(middlePoint->X()*middlePoint->X()+middlePoint->Y()*middlePoint->Y()));
					if (middleRadius <= detectorRadius){
						muonsInMiddle++;
					}
				    //cout << entryRadius << endl;
					//cout << "X: " << escapePoint->X() << " Y: " << escapePoint->Y() << endl;
					double escapePointRadiusZ = sqrt(escapePointZ->X() * escapePointZ->X() + escapePointZ->Y() * escapePointZ->Y());
					if (escapePointRadiusZ <= detectorRadius){
						muonsInBottomLayer++;
					}
		         	//cout << radius1 << " " << radius2 << endl;
		         	if (entryPoint->Z() < exitPoint->Z()){
		         		TVector3 *help = new TVector3(entryPoint->X(), entryPoint->Y(), entryPoint->Z()); // if entry point is lower than exit point
		         		entryPoint->SetX(exitPoint->X());
		         		entryPoint->SetY(exitPoint->Y());
		         		entryPoint->SetZ(exitPoint->Z());
		         		exitPoint->SetX(help->X());
		         		exitPoint->SetY(help->Y());
		         		exitPoint->SetZ(help->Z());
		         		
		         		
		         	}
		         	// muon entered and exited from the side
		         	if (exitPoint->Z() > -detectorHeight && entryPoint->Z()<0 && exitPoint->Z()<0 && entryPoint->Z() > -detectorHeight){
				     	sideView->Fill(exitPoint->X(), exitPoint->Z());
				     	sideView->Fill(entryPoint->X(), entryPoint->Z());
				     	topEntry->Fill(entryPoint->X(), entryPoint->Y());
				     	schnittpunkte++;
				     	//cout << exitPoint->X() << " " <<  exitPoint->Y() << " " << exitPoint->Z()<<endl;
				     	bottomEscape->Fill(exitPoint->X(), exitPoint->Y());
				     	schnittpunkte++;
				     	double distanceTravelled1 = sqrt((entryPoint->X() - exitPoint->X()) * (entryPoint->X() - exitPoint->X()) + (entryPoint->Y() - exitPoint->Y()) * (entryPoint->Y() - exitPoint->Y()) + (entryPoint->Z() - exitPoint->Z()) * (entryPoint->Z() - exitPoint->Z()));
				     	particlesInDetector++;
				     	//travelDistance->Fill(distanceTravelled1);
				     	if (distanceE<distanceTravelled1){
				     		particlesStopped++;
				     		//cout << distanceE << " " << distanceTravelled1 << " " << energy << " " << impulse << endl;
				     	}
				     	
		         	}
		         	
		         	else{
		         		// muon could enter from the top and exit from the bottom
		         		
		         		
						//	cout << s << endl;
						
						//cout << "r: " <<  abs(sqrt(escapePoint->X() * escapePoint->X() + escapePoint->Y() * escapePoint->Y())) << endl;
						if (escapePointRadiusZ <= detectorRadius && entryRadius <= detectorRadius){//particle entered and exited from the top and bottom
							bottomEscape->Fill(escapePointZ->X(), escapePointZ->Y());
							schnittpunkte++;
							sideView->Fill(escapePointZ->X(), 0);
							topEntry->Fill(entryPointX->X(), entryPointX->Y());
							schnittpunkte++;
							sideView->Fill(entryPointX->X(), -detectorHeight);
							double distanceTravelled2 = sqrt((entryPointX->X() - escapePointZ->X()) * (entryPointX->X() - escapePointZ->X()) + (entryPointX->Y() - escapePointZ->Y()) * (entryPointX->Y() - escapePointZ->Y()) + (entryPointX->Z() - escapePointZ->Z()) * (entryPointX->Z() - escapePointZ->Z()));
							particlesInDetector++;
							if (distanceE<distanceTravelled2){
				     			particlesStopped++;
				     			//cout << distanceE << " " << distanceTravelled2 << " " << energy << " " << impulse << endl;
				     		}
						}
						else if (escapePointRadiusZ <= detectorRadius && escapePointRadiusZ <= detectorRadius){ // particle entered from the side and exited from the bottom
								sideView->Fill(entryPoint->X(), entryPoint->Z());
								sideView->Fill(escapePointZ->X(), -detectorHeight);
								topEntry->Fill(entryPoint->X(), entryPoint->Y());
								schnittpunkte++;
								//cout << radius1 << endl;
								bottomEscape->Fill(escapePointZ->X(), escapePointZ->Y());
								schnittpunkte++;
								double distanceTravelled3 = sqrt((entryPoint->X() - escapePointZ->X()) * (entryPoint->X() - escapePointZ->X()) + (entryPoint->Y() - escapePointZ->Y()) * (entryPoint->Y() - escapePointZ->Y()) + (entryPoint->Z() - escapePointZ->Z()) * (entryPoint->Z() - escapePointZ->Z()));
								//travelDistance->Fill(distanceTravelled3);
								particlesInDetector++;
								if (distanceE < distanceTravelled3){
				     				particlesStopped++;
				     				//cout << distanceE << " " << distanceTravelled3 << " " << energy << " " << impulse << endl;
				     			}
						}
						// Muons exit on the x/y-axis but enters from the top
						else if (entryRadius <= detectorRadius && entryRadius <= detectorRadius){
								topEntry->Fill(entryPointX->X(), entryPointX->Y());
								bottomEscape->Fill(exitPoint->X(), exitPoint->Y());
								sideView->Fill(entryPointX->X(), 0);
								schnittpunkte++;
								sideView->Fill(exitPoint->X(), exitPoint->Z());
								schnittpunkte++;
								double distanceTravelled4 = sqrt((entryPointX->X() - exitPoint->X()) * (entryPointX->X() - exitPoint->X()) + (entryPointX->Y() - exitPoint->Y()) * (entryPointX->Y() - exitPoint->Y()) + (entryPointX->Z() - exitPoint->Z()) * (entryPointX->Z() - exitPoint->Z()));
								//travelDistance->Fill(distanceTravelled4);
								particlesInDetector++;
								if (distanceE < distanceTravelled4){
				     				particlesStopped++;
				     				//cout << distanceE << " " << distanceTravelled4 << " " << energy << " " << impulse << endl;
				     			}
						}
						
						
		         	}
		         	
		  }
		  
	  }
	  cout << "Obere:" << muonsInTopLayer << " Mittlere: " << muonsInMiddle << " Untere: " << muonsInBottomLayer << endl;
	  double rate = (muonsInBottomLayer+muonsInMiddle+muonsInTopLayer)/3;
	  cout << "Rate:" << rate << endl;
	  cout << particlesInDetector << " particles in the detector" << endl;
	  cout << particlesStopped << " were stopped" << endl;
	  cout << "Muons passing through an area of " << area*10000 << "cm^2. That corresponds to " << rate/area/10000 << " 1/cm^2. This corresponds to " << rate/area/10000 << " minutes. That means that the rate is " << particlesInDetector*area*10000/rate/60 << " Hz"<< endl;
	//cout << spare << endl;
	//Drawing everything
	
	
	TCanvas *c1 = new TCanvas("c1", "Muons in the detector", 700, 700);
	layer->GetXaxis()->SetTitle("X-Position of Muon");
	layer->GetYaxis()->SetTitle("Y-Position of Muon");
	layer->Draw("colz");
	TCanvas *c2 = new TCanvas("c2", "Phi", 700, 700);
	phiDist->GetYaxis()->SetRangeUser(0, 200);
	phiDist->Draw();
	TCanvas *c3 = new TCanvas("c3", "Theta", 700, 700);
	thetaDist->Draw();
	TCanvas *c4 = new TCanvas("c4", "Angular Dist", 700, 700);
	angDist->GetXaxis()->SetTitle("#theta * cos(#phi)");
	angDist->GetYaxis()->SetTitle("#theta * sin(#phi)");
	angDist->Draw();
	TCanvas *c5 = new TCanvas("c5", "Top View of Muons exiting", 700, 700);
	bottomEscape->GetXaxis()->SetTitle("x/m");
	bottomEscape->GetYaxis()->SetTitle("y/m");
	bottomEscape->Draw();
	TCanvas * c6 = new TCanvas("c6", "Muons entering from the top wall", 700, 700);
	topEntry->GetXaxis()->SetTitle("x/m");
	topEntry->GetYaxis()->SetTitle("y/m");
	topEntry->Draw();
	TCanvas * c7 = new TCanvas("c7", "Side view of Muons Entering and exiting", 700, 700);
	sideView->GetXaxis()->SetTitle("x/m");
	sideView->GetYaxis()->SetTitle("z/m");
	sideView->Draw();
	TCanvas *c8 = new TCanvas("c8", "Travel distance of Muon with regard to energy", 1400, 700);
	travelDistance->Draw();
	TCanvas *c9 = new TCanvas("Energy", "Energy", 700, 700);
	c9->SetLogx(1);
	c9->SetLogy(1);
	c9->SetTickx();
	c9->SetTicky();
	//verteilungEnergie->GetYaxis()->SetRangeUser(1e-8, 1e2);
	verteilungEnergie->GetXaxis()->SetRangeUser(1e-1, 1e4);
	verteilungEnergie->GetXaxis()->SetTitle("Momentum in MeV/c");
	verteilungEnergie->GetYaxis()->SetTitle("Muon flux in m^-2sec^1sr^-1(GeV/c)^-1");
	verteilungEnergie->Draw();
	TCanvas *c10 = new TCanvas();
	impulseDist->Draw();
	// saving the images:
		
	c1->Print("Projection.png");
	c2->Print("Phi.png");
	c3->Print("Theta.png");
	c4->Print("Angular.png");
	c5->Print("topExit.png");
	c6->Print("topEntry.png");
	c7->Print("sideView.png");
	c8->Print("distanceTravelled.png");
	c9->Print("E.png");


}
