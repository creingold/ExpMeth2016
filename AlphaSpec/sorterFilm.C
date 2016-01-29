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

int sorterFilm(){

	TFile *myfile = new TFile("alphaInFilm.root","RECREATE");

	ifstream fIn ( "Aluminum4.csv" );
	if ( !fIn ){
		exit(1);
	}

	TH1F *alum4 = new TH1F( "alum4" , "Aluminum Foil, 4 micrometers" , 11000 , 0 , 10999 );

	char buffer[10];
	fIn >> buffer;
	fIn >> buffer;


	int channel , fillValue;
	float energy;

	while ( !fIn.eof() ){
		fIn >> channel;
		fIn >> fillValue;
	
		energy = 42.297 + 2.60141*channel;
		alum4->Fill( energy , fillValue );
	}

	fIn.close();

	ifstream fIn ( "Havar4.6.csv" );
	if ( !fIn ){
		exit(1);
	}

	TH1F *havar4 = new TH1F( "havar4" , "Havar Foil, 4.6 micrometers" , 11000 , 0 , 10999 );

	fIn >> buffer;
	fIn >> buffer;

	int channel , fillValue;
	float energy;

	while ( !fIn.eof() ){
		fIn >> channel;
		fIn >> fillValue;
	
		energy = 42.297 + 2.60141*channel;
		havar4->Fill( energy , fillValue );
	}

	fIn.close();

	ifstream fIn ( "Aluminum7.csv" );
	if ( !fIn ){
		exit(1);
	}

	TH1F *alum7 = new TH1F( "alum7" , "Aluminum Foil, 7 micrometers" , 11000 , 0 , 10999 );

	fIn >> buffer;
	fIn >> buffer;


	int channel , fillValue;
	float energy;

	while ( !fIn.eof() ){
		fIn >> channel;
		fIn >> fillValue;
	
		energy = 42.297 + 2.60141*channel;
		alum7->Fill( energy , fillValue );
	}

	fIn.close();

	ifstream fIn ( "Havar2.3.csv" );
	if ( !fIn ){
		exit(1);
	}

	TH1F *havar2 = new TH1F( "havar2" , "Havar Foil, 2.3 micrometers" , 11000 , 0 , 10999 );

	fIn >> buffer;
	fIn >> buffer;


	int channel , fillValue;
	float energy;

	while ( !fIn.eof() ){
		fIn >> channel;
		fIn >> fillValue;
	
		energy = 42.297 + 2.60141*channel;
		havar2->Fill( energy , fillValue );
	}

	fIn.close();
	
	myfile->Write();

	return 0;

}
