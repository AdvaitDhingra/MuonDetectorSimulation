void energy()
{
	TCanvas *c1 = new TCanvas("Energy", "Energy", 600, 600);
	
	TF1 *verteilung = new TF1("Energy Verteilung", "71 * 45 * (4.1 + x)^-3.04 * (1+x/854)^-1", 1e-1, 1e4);
	
	
	
	
	
	
	c1->SetLogx(1);
	c1->SetLogy(1);
	c1->SetTickx();
	c1->SetTicky();
	verteilung->GetYaxis()->SetRangeUser(1e-8, 1e2);
	verteilung->GetXaxis()->SetRangeUser(1e-1, 1e4);
	verteilung->Draw();
}
