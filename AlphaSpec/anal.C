#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<stdlib.h>
#include<math.h>

#include<TROOT.h>
#include<TFile.h>
#include<TTree.h>
#include<TH1.h>
#include<TCanvas.h>
#include<TF1.h>
#include<TGraph.h>
#include<TGraphErrors.h>

using namespace std;

int anal(){
	string top;
	
	float mean[8][3]={0};
	float meanerr[8][3]={0};
	float sd[8][3]={0};
	float sderr[8][3]={0};
	
	float FWHM[8][3]={0};
	float FWHMerr[8][3]={0};
	
	float Resolution[8][3]={0};
	float Resolutionerr[8][3]={0};
	
	float Voltage[8] = {10, 20, 30, 40, 50, 60, 70, 75};
	float Voltageerr[8] = {0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05};
	ifstream fIn("fwhm_anal.dat");
	
	if(!fIn){
		cout << "nope" << endl;
		exit(1);
	}
	
	getline(fIn, top);
	
	for (int i=0; i<8; i++){
		for (int j=0; j<3; j++){
			fIn >> mean[i][j];
			fIn >> meanerr[i][j];
			fIn >> sd[i][j];
			fIn >> sderr[i][j];
			
			FWHM[i][j] = 2*sqrt(2*log(2)) * sd[i][j];
			FWHMerr[i][j] = 2*sqrt(2*log(2)) * sderr[i][j];
			
			Resolution[i][j] = FWHM[i][j]/mean[i][j];
			Resolutionerr[i][j] = Resolution[i][j] * sqrt( pow(FWHMerr[i][j]/FWHM[i][j], 2) + pow(meanerr[i][j]/mean[i][j], 2) );
		}
	}
	
	float Resolution1[8] = {0};
	float Resolution2[8] = {0};
	float Resolution3[8] = {0};
	
	float Resolutionerr1[8] = {0};
	float Resolutionerr2[8] = {0};
	float Resolutionerr3[8] = {0};
	
	for (int k=0; k<8; k++){
		Resolution1[k] = Resolution[k][1];
		Resolution2[k] = Resolution[k][2];
		Resolution3[k] = Resolution[k][3];
		
		Resolutionerr1[k] = Resolutionerr[k][1];
		Resolutionerr2[k] = Resolutionerr[k][2];
		Resolutionerr3[k] = Resolutionerr[k][3];
	}
	
	TFile *file = TFile::Open("Resolution.root","RECREATE");
	
	TGraphErrors *peak1 = new TGraphErrors(8, Voltage, Resolution1, Voltageerr, Resolutionerr1);
	TGraphErrors *peak2 = new TGraphErrors(8, Voltage, Resolution2, Voltageerr, Resolutionerr2);
	TGraphErrors *peak3 = new TGraphErrors(8, Voltage, Resolution3, Voltageerr, Resolutionerr3);
	
	TCanvas *c1 = new TCanvas("c1", "Resolution Plots");
	TCanvas *c2 = new TCanvas("c2" , "Resolution Plots");
	TCanvas *c3 = new TCanvas("c3" , "Resolution Plots");
	
	c1->cd();
	peak1->Draw();

	c2->cd();
	peak2->Draw();
	
	c3->cd();
	peak3->Draw();

	c1->Write();
	c2->Write();
	c3->Write();
	
	file->Write();
	file->Close();
	
	return 0;
}
