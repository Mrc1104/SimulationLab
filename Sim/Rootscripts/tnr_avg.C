#include <fstream>
using namespace std;

// Calculate average
double mean(const vector<double> &x)
{
	double sum = 0;
	for(auto it = x.begin(); it != x.end(); it++) {
		sum += *it;
	}
	return (sum/x.size());
}
double dev(const vector<double> &x, const double mean)
{
	double sum = 0;
	for(auto it = x.begin(); it != x.end(); it++) {
		sum += (*it-mean)*(*it-mean);
	}
	return TMath::Sqrt( sum/(x.size()-1) );
}

// Open file and compute average and std
// Save to an outfile
void get_stats(string file, ostream& out)
{
	// open file
	ifstream infile(file.c_str());
	// Read in values
	vector<double> x;
	vector<double> y;
	double tmpx, tmpy;
	while(infile >> tmpx >> tmpy){
		x.push_back(tmpx);
		y.push_back(tmpy);
	}
	double avg  = mean(y);
	double err  = dev(y, avg);
	out << x.at(0) << " " << avg << " " << err << endl;

}


void tnr_avg(TString sfiles, TString ssave)
{
	// parse the allfiles (delineated by \n)
	std::string stmp(sfiles.Data());
	std::vector<std::string> vfiles;
	char trash[755]; int ti = 0;
	memset(trash, 0, 255);
	for(int i = 0; i < stmp.size(); i++) {
		if( stmp[i] == '\n' ){
			vfiles.push_back(trash);
			memset(trash, 0, 255);
			ti = 0;
		}
		else
			trash[ti++] = stmp[i];
	}

	// Save file
	ofstream outfile(ssave.Data());
	for(auto it = vfiles.begin(); it != vfiles.end(); it++){
		get_stats(*it, outfile);
	}


}
