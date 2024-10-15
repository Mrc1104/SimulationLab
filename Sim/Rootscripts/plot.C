#include <vector>
#include <iostream>
#include <fstream>
#include <utility>
using namespace std;

struct tnr_stats
{
	double energy;
	double mean;
	double std;
};

void readin(ifstream &in, vector< tnr_stats > & v)
{
	// Read in Data (expects 2 columnar data)
	double e,m, s;
	while(in >> e >> m >> s)
	{
		v.push_back({e, m, s});
	}

}


void plot(TString sdata, TString ssave, TString name = "TNR")
{
	vector< tnr_stats > stats;
	ifstream finp(sdata);
	readin(finp, stats);

	TGraphErrors *g = new TGraphErrors();
	TCanvas* c = new TCanvas();
	TFile* f = new TFile(ssave, "RECREATE");
	int npoints = 0;
	for(auto it = stats.begin(); it != stats.end(); it++){
		g->AddPoint(it->energy, it->mean);
		g->SetPointError(npoints, 0, it->std);
		npoints++;
	}
	g->SetMarkerStyle(20);
	g->SetTitle(name);
	g->GetYaxis()->SetTitle("TNR");
	g->GetXaxis()->SetTitle("MeV");
	g->Draw("AP");
	TF1* fit;
	TFitResultPtr pfr;
	pair<int,int> rg(0,0);
	double maxTNR; 
	double maxBin;
	if(name.Contains("Proton"))
	{
		cout << "Fitting Protons" << endl;
		fit = new TF1("fit", "gaus(0)",133,137);
		fit->SetParameters(0.09, 130, 2);
		pfr = g->Fit(fit,"RS");
		rg = {133,137};
		maxTNR = fit->GetMaximum(rg.first, rg.second);
		maxBin = fit->GetMaximumX(rg.first, rg.second);
	}
	else if(name.Contains("Ion"))
	{
		cout << "Fitting Ions" << endl;
		//fit = new TF1("fit", "gaus(0)", 3000,3090);
		fit = new TF1("fit", "pol3(0)", 2999,3091);
		pfr = g->Fit(fit,"RS");
		rg = {2999,3091};
		maxTNR = fit->GetMaximum(rg.first, rg.second);
		maxBin = fit->GetMaximumX(rg.first, rg.second);
	}
	else{
		cout << "Fitting Gammas" << endl;
		fit = new TF1("fit", "pol3");
		pfr = g->Fit(fit,"S");
		rg = {80,120};
		maxTNR = fit->GetMaximum(rg.first, rg.second);
		maxBin = fit->GetMaximumX(rg.first, rg.second);
	}
	cout << maxTNR << " " << maxBin << endl;
	TTree* t = new TTree("Data", "Data");
	TBranch* bTNR = t->Branch("MaxTNR", &maxTNR, "TNR/D");
	TBranch* bBin = t->Branch("MaxBin", &maxBin, "Bin/D");
	t->Fill();


	// Save To File
	t->Write("Data");
	g->Write("TNR");
	pfr->Write("Fit");
	c->Write("Plot");
}
