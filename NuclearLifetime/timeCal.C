/*
Craig

Just a quick loop for getting a timing calibration
*/

{
	TFile *timefile = new TFile("TimeCal.root");
	
	TCanvas *c0 = new TCanvas("c0" , "");
	TSpectrum *spec = new TSpectrum(40);
	int found = spec->Search(h , 2 , "" , 0.02 );

	float *locat = spec->GetPositionX();

	float peaks[found];
	const int index[found];

	TMath::Sort( found , locat , index , 0 );
	for ( int i = 0 ; i < found ; i++ ){
		peaks[i] = locat[index[i]];
	}

	float actual[found];
	for ( int j = 0 ; j < found ; j++ ){
		actual[j] = 80*j;
	}

	TGraph *graph = new TGraph( found, peaks, actual );

	TF1 *fit = new TF1( "fit" , "pol1(0)" , 0 , 9000 );

	graph->Fit(fit , "QN0");
/*
	graph->Draw("ap");
	graph->SetMarkerStyle(21);
*/
	cout << endl << "Calibration = " << fit->GetParameter(0) << " + " << fit->GetParameter(1) << " * x" << endl;

}
