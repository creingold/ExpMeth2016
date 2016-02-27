/*
Craig Reingold
2/26/16
Calibrator

It does exactly what is says it will do
*/

#include<iostream>
#include<iomanip>
#include<fstream>

#include<TROOT.h>
#include<TFile.h>
#include<TCanvas.h>
#include<TF1.h>
#include<TGraph.h>

int calibrator(){
	ifstream infile("calibration.dat");
	if ( !infile ){
		sys.exit(1);
	}

	char buffer[14];
	infile >> buffer >> buffer >> buffer >> buffer;

	float chan[18] , uncChan[18] , energy[18] , uncEne[18];
	for( int i = 0 ; i < 18 ; i++ ){
		infile >> buffer >> buffer >> chan[i] >> uncChan[i] >> energy[i];
		uncEne[i] = 0.005;
		cout << chan[i] << '\t' << uncChan[i] << '\t' << energy[i] << endl;
	}


// Placeholder until we have energies
/*
	float energy[18] , uncEne[18];
	for ( int i = 0 ; i < 18 ; i++ ){
		energy[i] = 10;
		uncEne[i] = 1;
	}
*/
// Back to real analysis

	TGraphErrors *graph = new TGraphErrors( 18 , chan, energy , uncChan , uncEne );
	TF1 *calLine = new TF1("calLine" , "pol1(0)" , 1 , 2050 );

//	graph->Draw();

	graph->Fit( calLine , "QN0" );

	cout << setprecision(4) << endl << "Calibration = (" << calLine->GetParameter(0) << " +/- " << calLine->GetParError(0) << ") + (" << calLine->GetParameter(1) << " +/- " << calLine->GetParError(1) << ") * chan" << endl;

	return 0;
}
