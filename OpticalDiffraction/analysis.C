/*

*/

#include<iostream>
#include<fstream>
#include<iomanip>

#include<string>

#include<TROOT.h>
#include<TFile.h>
#include<TCanvas.h>
#include<TF1.h>
#include<TH1.h>
#include<TLegend.h>
#include<TLatex.h>

#include<TVirtualFFT.h>

using namespace std;

int analysis(){
	string filename;
	cout << "Please input the filename/path:\t";
	cin >> filename;
	
	TCanvas *c1 = new TCanvas("c", "Fast Fourier Transform", 1600, 600);
	c1->Divide(2,1);
	c1->cd(1);
	
	int period_position = filename.find(".");
	
	string rawfile = filename.substr(0, period_position);
	string rootfilename = rawfile.append(".root");
	
	TFile *outFile = TFile::Open(rootfilename.c_str(), "RECREATE");
	TTree *tree = new TTree("tree", "csv to root tree");
	
	ifstream fIn(filename.c_str());
	
	if (!fIn){
		cout << filename.c_str() << " could not be opened!" << endl;
		exit(1);
	}
	
	float time, pos;
	int count;
	
	TH1F *h = new TH1F("h", "h", 2401, 0, 150);
	h->SetStats(kFALSE);
	h->SetTitle(/*(rawfile.substr(0, period_position)).c_str()*/"Interferogram");
	
	h->GetXaxis()->SetTitle("Position (mm)");
	h->GetXaxis()->CenterTitle();
	
	h->GetYaxis()->SetTitle("Relative Intensity");
	h->GetYaxis()->CenterTitle();
	
	tree->Branch("Position (mm)", &pos, "pos/F");
	tree->Branch("Counts", &count, "count/I");
	
	while(fIn){
		fIn >> time;
		fIn >> count;
		pos = 0.25*time;
		h->Fill(pos, count);
		tree->Fill();
	}
	float max = h->GetMaximum();
	h->Scale(1/max);
	h->Draw();
	c1->cd(2);

// Compute the transform and look at the magnitude of the output
//	TCanvas *c1 = new TCanvas("c1" , "Fast Fourier Transform" , 900 , 600 );

	TH1 *hm = 0;
	TVirtualFFT::SetTransform(0);
	hm = h->FFT(hm, "MAG");
	hm -> SetTitle("Fourier Transform");
	hm -> SetStats(kFALSE);

	hm->GetXaxis()->SetTitle("wavenumber (1/mm)");
	hm->GetXaxis()->CenterTitle();

	hm->GetYaxis()->SetTitle("Magnitude");
	hm->GetYaxis()->CenterTitle();

	hm->GetXaxis()->SetLimits(0, 16*2*3.14159265359);
	hm->GetXaxis()->SetRangeUser(0, 16*3.14159265359);
	hm -> Draw();

/*
// Defining the fit functions
	TF1 *fit = new TF1( "fit", "[0]*(sin([1]*(x-[2]))*sin([1]*(x-[2]))/([1]*[1]*(x - [2])*(x - [2])))" , 0 , 700 );
//	TF1 *linFit = new TF1 ( "linFit" , "pol1(0)" , 85 , 1000 );
//	TF1 *expoFit = new TF1 ( "expoFit" , "expo(0)" , 85 , 1000 );

// Setting parameters for initial fit
	fit->SetParameters( 1000000000000 , 1000 , 300 );
	fit->SetLineColor(1);
	fit->SetLineWidth(3);

	h->Fit(fit, "R+");

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
*/
// Making everything look pretty
//	hcal -> SetTitle("");
//	gStyle->SetTitleFontSize(0.001);

//	hcal -> GetXaxis()->SetTitle("Time (ns)");
	h -> GetXaxis()->SetTitleSize(0.05);
	h -> GetXaxis()->SetTitleOffset(0.8);
	h -> GetXaxis()->SetLabelSize(0.04);

//	hcal -> GetYaxis()->SetTitle("Counts");
	h -> GetYaxis()->SetTitleSize(0.05);
	h -> GetYaxis()->SetTitleOffset(0.9);
	h -> GetYaxis()->SetLabelSize(0.04);

	hm-> GetXaxis()->SetTitleSize(0.05);
	hm-> GetXaxis()->SetTitleOffset(0.8);
	hm-> GetXaxis()->SetLabelSize(0.04);

	hm-> GetYaxis()->SetTitleSize(0.05);
	hm-> GetYaxis()->SetTitleOffset(0.9);
	hm-> GetYaxis()->SetLabelSize(0.04);

// Using TLatex maybe IDK
	c1->cd(1);

	TLatex latex;
	latex.SetTextSize(0.045);
	latex.SetTextAlign(11);

	char texOut[125];
//	float tau = -log(2)/expoPar[1];
//	float err = fit->GetParError(1);
//	float tauError = log(2)*err/(expoPar[1]*expoPar[1]);
	char aValue[32];

	cout << "What is your 'a' value?" << endl;
	cin >> aValue;

//Comment out for single slit
	char dValue[5];
	cout << "What is your 'd' value?" << endl;
	cin >> dValue;

	sprintf( texOut , "#splitline{a = %s #mum}{d = %s #mum}" , aValue, dValue );

	latex.DrawLatex(100 , 0.6 ,texOut);
/*
// Making a legend
	leg = new TLegend( 0.7 , 0.6 , 0.9 , 0.9 );
	leg->SetTextSize(0.03);
	leg->SetHeader("Legend");
	leg->AddEntry( hcal , "Data" , "l" );
	leg->AddEntry( fit , "Full Fit" , "l" );
	leg->AddEntry( expoFit , "Indiv. Fits" , "l" );
	leg->Draw();
*/

	outFile -> Write();

	return 0;
}
