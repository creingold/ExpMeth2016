/*
Craig Reingold
01/19/16
Analysis

This code will take in multiple .csv files, and generate one root file with all the histograms from the .csv files stored inside.

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

int analysis(){

	ofstream outfile("fwhm_anal.dat");
	outfile << "M\t\tS\t\tM\t\tS\t\tM\t\tS" << endl;

	TFile *myfile = new TFile("alphaHists.root");
	TCanvas *c0 = new TCanvas("c0" , "Work Canvas" );

	for ( int c = 10 ; c < 80 ; c += 5 ){
		if ( (c % 10 == 0) || (c == 75) ){

			char histName[10];
			sprintf( histName , "hist%d" , c );

			TH1F *h0 = new TH1F( "h0" , "Work Histogram" , 4096 , 0 , 4095 );
			h0 = ( TH1F* ) myfile->Get( histName );

			TSpectrum *spec = new TSpectrum(3);
			int peaksFound = spec->Search( h0 , 5 , "" , 0.02 );

			float *peakLocations = spec->GetPositionX();

			float peaksSorted[3];
			const int index[3];

			TMath::Sort( peaksFound , peakLocations , index , 0 );
			for ( int i = 0 ; i < peaksFound ; i++ ){
				peaksSorted[i] = peakLocations[index[i]];
			}

			TF1 *singleGauss = new TF1("singleGauss" , "gaus(0)" , (int) peaksSorted[0] - 50 , (int) peaksSorted[0] + 50 );
			TF1 *doubleGauss = new TF1("doubleGauss" , "gaus(0) + gaus(3)" , (int)peaksSorted[1] - 30 , (int) peaksSorted[2] + 30 );


			singleGauss->SetParameters( 50 , peaksSorted[0] , 4 );
			singleGauss->SetParLimits( 2 , 0 , 4 );

			doubleGauss->SetParameters( 10 , peaksSorted[1] , 4 , 50 , peaksSorted[2] , 4 );
			doubleGauss->SetParLimits( 2 , 0 , 5 );
			doubleGauss->SetParLimits( 5 , 0 , 4 );

			h0->Fit(singleGauss);
			h0->GetXaxis()->SetRangeUser( peaksSorted[0] - 100 , peaksSorted[0] + 100 );
	
			char outfilename[50];
			sprintf( outfilename , "singleFit%d.pdf" , c );
			c0->SaveAs(outfilename);

			h0->GetXaxis()->SetRangeUser( peaksSorted[1] - 100 , peaksSorted[2] + 100 );

			h0->Fit(doubleGauss);			

			float singleParam[3] , singleError[3] , doubleParam[6] , doubleError[6];

			for ( int i = 0 ; i < 3 ; i++ ){
				singleParam[i] = singleGauss->GetParameter(i);
				singleError[i] = singleGauss->GetParError(i);
			}

			for ( int i = 0 ; i < 6 ; i++ ){
				doubleParam[i] = doubleGauss->GetParameter(i);
				doubleError[i] = doubleGauss->GetParError(i);
			}

			outfile << setprecision(5) << singleParam[1] << '\t';
			outfile << setprecision(4) << singleError[1] << '\t';
			outfile << setprecision(4) << singleParam[2] << '\t';
			outfile << setprecision(4) << singleError[2] << '\t';

			outfile << setprecision(5) << doubleParam[1] << '\t';
			outfile << setprecision(4) << doubleError[1] << '\t';
			outfile << setprecision(4) << doubleParam[2] << '\t';
			outfile << setprecision(4) << doubleError[2] << '\t';

			outfile << setprecision(5) << doubleParam[4] << '\t';
			outfile << setprecision(4) << doubleError[4] << '\t';
			outfile << setprecision(4) << doubleParam[5] << '\t';
			outfile << setprecision(4) << doubleError[5] << endl;

			h0 -> GetXaxis() -> SetRangeUser( peaksSorted[1] - 100 , peaksSorted[2] + 100 );

			sprintf( outfilename , "doubleFit%d.pdf" , c );
			c0->SaveAs(outfilename);

		}
	}

	outfile.close();

	return 0;
}
