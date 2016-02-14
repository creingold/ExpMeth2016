/*
Craig Reingold
154 Sm Analysis TGraphError

This code will take clover*ratio.dat files and generate TGraphError plots

*/

#include<iostream>
#include<iomanip>
#include<fstream>

const int peakNum = 8;

using namespace std;
int TGE(){

	ifstream infile("fwhm_anal.dat");
	if ( !infile ){
		exit(1);
	}

	float buff;
	for ( int i = 0 ; i < 6 ; i ++ ){
		infile >> buff;
	}

	TCanvas *c0 = new TCanvas("c0", "Canvas" );

	float bias[8] , dBias[8] , res[8] , dRes[8], mean1[8] , dMean1[8] , std1[8] , dStd1[8];

	mean1[0] = 1181.6;
	mean1[1] = 1195.0;
	mean1[2] = 1201.4;
	mean1[3] = 1205.3;
	mean1[4] = 1207.4;
	mean1[5] = 1207.4;
	mean1[6] = 1209.8;
	mean1[7] = 1209.9;

	dMean1[0] = 0.1983;
	dMean1[1] = 0.1937;
	dMean1[2] = 0.1835;
	dMean1[3] = 0.1555;
	dMean1[4] = 0.1636;
	dMean1[5] = 0.1636;
	dMean1[6] = 0.1575;
	dMean1[7] = 0.1454;
	
	std1[0] = 3.640;
	std1[1] = 3.348;
	std1[2] = 3.145;
	std1[3] = 2.905;
	std1[4] = 2.693;
	std1[5] = 2.693;
	std1[6] = 2.657;
	std1[7] = 2.650;

	dStd1[0] = 0.1954;
	dStd1[1] = 0.1532;
	dStd1[2] = 0.1573;
	dStd1[3] = 0.1372;
	dStd1[4] = 0.1274;
	dStd1[5] = 0.1274;
	dStd1[6] = 0.1579;
	dStd1[7] = 0.1260;

	bias[0] = 10;
	bias[1] = 20;
	bias[2] = 30;
	bias[3] = 40;
	bias[4] = 50;
	bias[5] = 60;
	bias[6] = 70;
	bias[7] = 75;

	for ( int j = 0 ; j < 8 ; j++ ){
		dBias[j] = 0.05;
		res[j] = 2*sqrt(2*log(2)) * std1[j] / mean1[j];
		cout << std1[j] << '\t' << res[j] << endl;

		dRes[j] = res[j]*sqrt( pow ( dStd1[j]/std1[j], 2) + pow ( dMean1[j]/mean1[j] , 2) );

//		res[j] = j;
//		dRes[j] = 0.001;

	}

	TGraphErrors *graph1 = new TGraphErrors( 8 , bias , res, dBias, dRes );
	graph1->SetMarkerStyle(21);

	char title[30];
	sprintf(title , "Resolution v. Bias (V)" );
	graph1->SetTitle(title);
	graph1->Draw("ap");

	infile.close();

	return 0;
}
