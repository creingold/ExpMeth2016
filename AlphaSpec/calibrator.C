/*
Craig Reingold
01/19/16
Calibrator

This code will take in a calibration csv file, and perform calibration on the doublet peak in 241Am.
All histograms and graphs will be saved in the ROOT file opened in the beginning.

*/

#include<iostream>
#include<fstream>
#include<iomanip>

#include<TROOT.h>
#include<TFile.h>
#include<TTree.h>
#include<TH1.h>
#include<TCanvas.h>
#include<TF1.h>
#include<TGraph.h>

using namespace std;

int calibrator(){

	TFile *myfile = new TFile("alphaCalibration.root","RECREATE");

	TCanvas *c0 = new TCanvas("c0" , "Calibration Canvas" );
	TCanvas *c1 = new TCanvas("c1" , "TGraph Canvas" );

	c0->cd();

	char histPointer[50] , histName[50] , filename[50] , buffer[16];

	sprintf( histPointer , "calHis" );
	sprintf( histName , "Calibration Histogram" );
	sprintf( filename , "calibrationRun.csv" );

	ifstream fIn ( filename );
	if ( !fIn ){
		exit(1);
	}

	TH1F *hist = new TH1F( histPointer , histName , 4096 , 0 , 4095 );

	fIn >> buffer;
	fIn >> buffer;

	int channel , fillValue;

	while ( !fIn.eof() ){
		fIn >> channel;
		fIn >> fillValue;

//		cout << channel << '\t' << fillValue << endl;

		hist->Fill( channel , fillValue );
	}

// The fitting procedure
	hist->GetXaxis()->SetRangeUser(2000 , 2150);
	hist->Draw();

	TF1 *doubleGaus = new TF1("doubleGaus" , "gaus(0) + gaus(3)" , 2000 , 2150 );
	doubleGaus->SetParameters( 25.7 , 2076.29 , 4.37 , 185.3 , 2092.5 , 2.74 );

	hist->Fit(doubleGaus);

	float param[6] , dParam[6];
	for ( int i = 0 ; i < 6 ; i++ ){
		param[i] = doubleGaus->GetParameter(i);
		dParam[i] = doubleGaus->GetParError(i);
	}

// Making a TGraphs

	c1->cd();
	float mean[2] , std[2] , ene[2] , dEne[2];

	mean[0] = param[1];
	mean[1] = param[4];

	std[0] = param[2];
	std[1] = param[5];

	ene[0] = 5443; 
	ene[1] = 5486;

	dEne[0] = 0.5 ;
	dEne[1] = 0.5 ;

	TGraphErrors *graph = new TGraphErrors( 2 , mean , ene , std, dEne );
	graph->SetMarkerStyle(21);
	graph->SetTitle("Energy v. Channel");
	
	graph->Draw("ap");
// The other fit

	TF1 *linFit = new TF1("linFit" , "pol1" );
	graph->Fit(linFit);

	cout << endl << "Calibration = " << linFit->GetParameter(0) << " + " << linFit->GetParameter(1) << "* [chan] " << endl;

	fIn.close();

	c0->Write();
	c1->Write();
	myfile->Write();

	return 0;

}
