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
	TFile *data = new TFile( "spectrum.root" );
	TCanvas *c0 = new TCanvas("c0", "Decay Spectrum" , 900 , 600 );

	hcal->SetLineColor(14);
	hcal->GetXaxis()->SetRangeUser(0,1500);
	hcal->Draw();

// Defining the fit functions
	TF1 *fit = new TF1( "fit", "expo(0) + pol1(2)" , 85 , 1000 );
	TF1 *linFit = new TF1 ( "linFit" , "pol1(0)" , 85 , 1000 );
	TF1 *expoFit = new TF1 ( "expoFit" , "expo(0)" , 85 , 1000 );

// Setting parameters for initial fit
	fit->SetParameters( 9.56 , -0.00732 , 1.689 , 0.00695 );
	fit->SetLineColor(1);
	fit->SetLineWidth(3);

	hcal->Fit(fit, "R+");

// Defining the two individual functions' parameters
	float expoPar[2] , linPar[2];
	int parNum = 0;

	for ( int i = 0 ; i < 2 ; i++ ){
		expoPar[i] = fit->GetParameter(i);
	}

	for ( int i = 2 ; i < 4 ; i++ ){
		linPar[i - 2] = fit->GetParameter(i);
	}
	
	expoFit->SetParameters( expoPar[0] , expoPar[1] );
	linFit->SetParameters( linPar[0] , linPar[1] );

	expoFit->SetLineColor(12);
	expoFit->SetLineWidth(3);
	expoFit->SetLineStyle(2);

	linFit->SetLineColor(12);
	linFit->SetLineWidth(3);
	linFit->SetLineStyle(2);

	expoFit->Draw("same");
	linFit->Draw("same");

// Making everything look pretty
	hcal -> SetTitle("");
	gStyle->SetTitleFontSize(0.001);

	hcal -> GetXaxis()->SetTitle("Time (ns)");
	hcal -> GetXaxis()->SetTitleSize(0.05);
	hcal -> GetXaxis()->SetTitleOffset(0.8);
	hcal -> GetXaxis()->CenterTitle();

	hcal -> GetYaxis()->SetTitle("Counts");
	hcal -> GetYaxis()->SetTitleSize(0.05);
	hcal -> GetYaxis()->SetTitleOffset(0.9);
	hcal -> GetYaxis()->CenterTitle();

// Using TLatex maybe IDK
	TLatex latex;
	latex.SetTextSize(0.045);
	latex.SetTextAlign(11);

	char texOut[125];
	float tau = -log(2)/expoPar[1];
	float err = fit->GetParError(1);
	float tauError = log(2)*err/(expoPar[1]*expoPar[1]);
	sprintf( texOut , "#tau = %.3f #pm %.3f ns" , tau ,tauError );

	latex.DrawLatex(300 , 5000,texOut);

// Making a legend
	leg = new TLegend( 0.7 , 0.6 , 0.9 , 0.9 );
	leg->SetTextSize(0.03);
	leg->SetHeader("Legend");
	leg->AddEntry( hcal , "Data" , "l" );
	leg->AddEntry( fit , "Full Fit" , "l" );
	leg->AddEntry( expoFit , "Indiv. Fits" , "l" );
	leg->Draw();


	return 0;
}
