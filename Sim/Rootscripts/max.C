#include <iostream>
#include <fstream>

using namespace std;


void max(TString sdata, TString name, TString save)
{
	ifstream finp(sdata);
	vector<double> ve;
	vector<double> vtnr;
	double tmp1, tmp2;
	while ( finp >> tmp1 >> tmp2 ) 
	{
		ve.push_back(tmp1);
		vtnr.push_back(tmp2);
		cout << tmp1 << " " << tmp2 << endl;
	}

	TGraph* g = new TGraph();
	for(int i = 0; i < ve.size(); i++) {
		g->AddPoint(ve.at(i), vtnr.at(i));
	}
	g->SetMarkerStyle(20);
	g->SetTitle(name);
	g->Draw("AP");

	TFile* fsave = new TFile(save, "UPDATE");
	g->Write(name, TObject::kOverwrite);
	
}
