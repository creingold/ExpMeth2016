/*

*/

#include<iostream>
#include<fstream>
#include<iomanip>

#include<TROOT.h>
#include<TFile.h>
#include<TCanvas.h>
#include<TF1.h>
#include<TH1.h>
#include<TLegend.h>
#include<TLatex.h>

using namespace std;

int analysis(){
// Opening the calibrated ROOT file
	TFile *data = new TFile( "MuonSpectrum.root" );
	TCanvas *c0 = new TCanvas("c0", "Muon Spectrum" , 900 , 600 );

	hcal->SetLineColor(14);
	hcal->Draw();

// Defining the fit functions
	TF1 *fit = new TF1( "fit", "expo(0) + gaus(2)" , -0.2 , 10.15 );
	TF1 *gausFit = new TF1 ( "gausFit" , "gaus(0)" , -0.2 , 10.15 );
	TF1 *expoFit = new TF1 ( "expoFit" , "expo(0)" , -0.2 , 10.15 );

// Setting parameters for initial fit
	fit->SetParameters( 6.24 , -0.43 , 29.75 , 7.31 , 2.38 );
	fit->SetLineColor(1);
	fit->SetLineWidth(3);

	hcal->Fit(fit, "R+");

// Defining the two individual functions' parameters
	float expoPar[2] , gausPar[3];
	int parNum = 0;

	for ( int i = 0 ; i < 2 ; i++ ){
		expoPar[i] = fit->GetParameter(i);
	}

	for ( int i = 2 ; i < 5 ; i++ ){
		gausPar[i-2] = fit->GetParameter(i);
	}
	
	expoFit->SetParameters( expoPar[0] , expoPar[1] );
	gausFit->SetParameters( gausPar[0] , gausPar[1] , gausPar[2] );

	expoFit->SetLineColor(12);
	expoFit->SetLineWidth(3);
	expoFit->SetLineStyle(2);

	gausFit->SetLineColor(12);
	gausFit->SetLineWidth(3);
	gausFit->SetLineStyle(2);

	expoFit->Draw("same");
	gausFit->Draw("same");

// Making everything look pretty
	hcal -> SetTitle("Muon Decay Spectrum");
	gStyle->SetTitleFontSize(0.07);

	hcal -> GetXaxis()->SetTitle("Time (\\mu s)");
	hcal -> GetXaxis()->SetTitleSize(0.06);
	hcal -> GetXaxis()->SetTitleOffset(0.7);
	hcal -> GetXaxis()->CenterTitle();

	hcal -> GetYaxis()->SetTitle("Channels");
	hcal -> GetYaxis()->SetTitleSize(0.06);
	hcal -> GetYaxis()->SetTitleOffset(0.7);
	hcal -> GetYaxis()->CenterTitle();

// Using TLatex maybe IDK
	TLatex latex;
	latex.SetTextSize(0.045);
	latex.SetTextAlign(11);

	char texOut[125];
	float tau = -1/expoPar[1];
	float err = fit->GetParError(1);
	float tauError = err/(expoPar[1]*expoPar[1]);
	sprintf( texOut , "#tau = %f #pm %f #mus" , tau ,tauError );

	latex.DrawLatex(1.0,450,texOut);

// Making a legend
	leg = new TLegend( 0.7 , 0.6 , 0.9 , 0.9 );
	leg->SetTextSize(0.04);
	leg->SetHeader("Legend");
	leg->AddEntry( hcal , "Data" , "l" );
	leg->AddEntry( fit , "Full Fit" , "l" );
	leg->AddEntry( expoFit , "Indiv. Fits" , "l" );
	leg->Draw();


	return 0;
}
