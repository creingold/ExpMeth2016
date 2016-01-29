/*
Craig Reingold
01/29/16
Apply Calibration

This code will take in multiple .csv files, and generate one root file with all the histograms from the .csv files stored inside.

This time, with the proper calibration found in fineCal.C

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

int applyCal(){

	TFile *myfile = new TFile("calAlphaHists.root","RECREATE");

	for ( int c = 10 ; c < 80 ; c += 5 ){
		if ( (c % 10 == 0) || (c == 75) ){

			char histPointer[50] , histName[50] , filename[50] , buffer[16];

			sprintf( histPointer , "hist%d" , c );
			sprintf( histName , "%d V Bias" , c );
			sprintf( filename , "%dV_Bias.csv" , c );

			ifstream fIn ( filename );
			if ( !fIn ){
				exit(1);
			}

			TH1F *hist = new TH1F( histPointer , histName , 4096 , 0 , 10999 );

			fIn >> buffer;
			fIn >> buffer;


			int channel , fillValue;
			float energy;

			while ( !fIn.eof() ){
				fIn >> channel;
				fIn >> fillValue;
	
				energy = 42.297 + 2.60141*channel;

				hist->Fill( energy , fillValue );
			}

		}
	}

	ifstream fIn ( "calibrationRun.csv" );
	if ( !fIn ){
		exit(1);
	}

	TH1F *hist = new TH1F( "fullSpec" , "Full Spectrum After Calibration" , 4096 , 0 , 10999 );

	fIn >> buffer;
	fIn >> buffer;


	int channel , fillValue;
	float energy;

	while ( !fIn.eof() ){
		fIn >> channel;
		fIn >> fillValue;
	
		energy = 42.297 + 2.60141*channel;
		hist->Fill( energy , fillValue );
	}
	
	myfile->Write();

	return 0;

}
